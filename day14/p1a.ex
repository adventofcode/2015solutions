#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent14p1 do
  def calculate do
    File.stream!("input") |>
    Enum.map(fn(x) -> Regex.scan(~r"^([a-zA-Z]+) can fly ([0-9]+) km/s for ([0-9]+) seconds, but then must rest for ([0-9]+) seconds.", x) |> hd |> tl end) |>
    Enum.map(fn([ name, speed, dur, rest]) -> 
        [name, String.to_integer(speed), String.to_integer(dur), String.to_integer(rest), "moving", 0, 0] 
    end) |>
    Enum.map(fn(x) -> 
        Stream.iterate(x, fn(x) -> move_reindeer(x) end) |>
        Enum.take(2503) |>
        Enum.fetch!(-1) |>
        Enum.fetch!(-1) 
    end) |>
    Enum.max
  end

  def move_reindeer(x) do
    [ name, speed, dur, rest, status, cur_dur, dist] = x
    if( status == "moving") do
      if(cur_dur == dur) do
        # switch to resting
        [ name, speed, dur, rest, "resting", 1, dist ]
      else
        # move along
        [ name, speed, dur, rest, status, cur_dur + 1, dist + speed]
      end
    else
      if( cur_dur == rest ) do
        [ name, speed, dur, rest, "moving", 1, dist + speed ]
      else
        [ name, speed, dur, rest, status, cur_dur + 1, dist ]
      end
    end
  end
end

IO.puts "Winning distance: " <> Integer.to_string(Advent14p1.calculate)
