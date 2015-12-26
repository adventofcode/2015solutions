#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent1p2 do
  def calculate do
    File.stream!("input", [], 1) |>
    Stream.transform([0,0],fn(x,acc) -> loc(x,acc) end) |>
    Enum.fetch!(-1) 
  end

  def loc(_, [-1, position]) do
    { :halt, [-1, position ] }
  end
  def loc("(", [floor, position]) do
    { [position+1], [floor+1, position+1] }
  end
  def loc(")", [floor, position]) do
    { [position+1], [floor-1, position+1] }
  end
end

IO.puts "Position: " <> Integer.to_string(Advent1p2.calculate)
