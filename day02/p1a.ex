#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent2p1 do
  def calculate do
    File.stream!("input") |>
    Stream.map(fn(x) -> String.strip(x) end) |>
    Stream.map(fn(x) -> split_str(x) end) |>
    Stream.map(fn(x) -> area(x) end) |>
    Enum.sum
  end

  def split_str(x) do
    String.split(x, "x") |>
    Enum.map(fn(c) -> String.to_integer(c) end)
  end

  def area(u) do
    [x,y,z] = u
    size = [x*y, y*z, x*z];

    [Enum.min(size)] ++ Enum.map(size, fn(x) -> x*2 end) |>
    Enum.sum
  end
end

IO.puts "Total Size: " <> Integer.to_string(Advent2p1.calculate)
