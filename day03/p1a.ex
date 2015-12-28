#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent3p1 do
  def calculate do
    File.stream!("input",[],1) |>
    Stream.scan([0,0] , fn(x,y) -> move(x,y) end ) |>
    Stream.concat([[0,0]]) |>
    Stream.uniq |>
    Enum.count
  end

  def move("<", [x,y]), do: [x+1,y]
  def move(">", [x,y]), do: [x-1,y]
  def move("^", [x,y]), do: [x,y+1]
  def move("v", [x,y]), do: [x,y-1]
  def move(_,acc), do: acc
end

IO.puts "Houses visited: " <> Integer.to_string(Advent3p1.calculate)
