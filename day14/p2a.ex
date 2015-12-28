#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent14p2 do
  def calculate do
    big_list = File.stream!("input") |>
    Enum.map(fn(x) -> Regex.scan(~r"^([a-zA-Z]+) can fly ([0-9]+) km/s for ([0-9]+) seconds, but then must rest for ([0-9]+) seconds.", x) |> hd |> tl end) |>
    Enum.map(fn([ _, speed, dur, rest]) -> 
        [String.to_integer(speed), String.to_integer(dur), String.to_integer(rest), "moving", 0, 0] 
    end) |>
    Stream.map( fn(x) -> race(x) end) |> Enum.to_list

    distances = List.zip( big_list) |> 
    Stream.map(fn(x) -> Tuple.to_list(x) end ) |>
    Stream.map(fn(x) -> Enum.max(x) end) |>
    Enum.to_list
   
    List.zip([List.zip(big_list), distances]) |> 
    List.delete_at(0) |>
    Enum.reduce([0,0,0,0,0,0,0,0,0], fn(x,acc) -> award_points(x,acc) end) |>
    Enum.with_index |>
    Enum.max_by( fn(x) -> elem(x,0) end ) |>
    elem(0) 
  end

  def award_points(x,acc) do
    { dists, winning_dist } = x
    Tuple.to_list(dists) |>
    Enum.with_index |>
    Enum.reduce( {acc, winning_dist}, fn(z,a) -> { a_p(z,a), elem(a,1)} end ) |>
    elem(0)
  end

  def a_p(z,a) do
    {acc, win } = a
    if(elem(z,0) == win) do
      List.update_at(acc,elem(z,1), &(&1 + 1))
    else
      acc
    end
  end
  def race(x) do
    Stream.iterate(x, fn(z) -> move_reindeer(z) end) |> 
    Stream.map(fn(z) -> List.last(z) end) |> 
    Enum.take(2503)
  end

  def move_reindeer(x) do
    [ speed, dur, rest, status, cur_dur, dist] = x
    if( status == "moving") do
      if(cur_dur == dur) do
        # switch to resting
        [ speed, dur, rest, "resting", 1, dist ]
      else
        # move along
        [speed, dur, rest, status, cur_dur + 1, dist + speed]
      end
    else
      if( cur_dur == rest ) do
        [speed, dur, rest, "moving", 1, dist + speed ]
      else
        [speed, dur, rest, status, cur_dur + 1, dist ]
      end
    end
  end
end

IO.puts "Winning points: " <> Integer.to_string(Advent14p2.calculate)
