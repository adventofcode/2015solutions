#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent1p1 do
  def calculate do
    File.stream!("input", [], 1) |>
    Stream.transform([0,0],fn(x,acc) -> loc(x,acc) end) |>
    Enum.fetch!(-1)
  end

  def loc(x, [floor, position]) when x == "(" do
    {[floor+1], [floor+1, position+1] }
  end
  def loc(x, [floor, position]) when x == ")"do
    {[floor-1], [floor-1, position+1] }
  end
  def loc(_, [floor, position]) do
    {[floor], [floor, position]}
  end
end

IO.puts "Floor to go to: " <> Integer.to_string(Advent1p1.calculate)
