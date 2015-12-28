#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent3p2 do
  def calculate do
    File.stream!("input",[],1) |>
    Stream.scan([1, [0,0],[0,0]] , fn(x,acc) -> m(x,acc) end ) |>
    Stream.concat([[1, [0,0],[0,0]]]) |>
    Stream.flat_map(fn([_,s,r]) -> [s,r] end) |>
    Stream.uniq |>
    Enum.count
  end

  def m(y,[1, s,r]), do: [2,move(y,s),r]
  def m(y,[2, s,r]), do: [1,s,move(y,r)]
  def move("<", [x,y]), do: [x+1,y]
  def move(">", [x,y]), do: [x-1,y]
  def move("^", [x,y]), do: [x,y+1]
  def move("v", [x,y]), do: [x,y-1]
  def move(_,acc), do: acc
end

IO.puts "Houses visited: " <> Integer.to_string(Advent3p2.calculate)
