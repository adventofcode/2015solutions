#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent2p2 do
  def calculate do
    File.stream!("input") |>
    Stream.map(fn(x) -> String.strip(x) end) |>
    Stream.map(fn(x) -> split_str(x) end) |>
    Stream.map(fn(x) -> ribbon(x) end ) |>
    Enum.sum
  end

  def split_str(x) do
    String.split(x, "x") |>
    Enum.map(fn(c) -> String.to_integer(c) end)
  end

  def ribbon(c) do
    area = Enum.reduce(c, fn(x,acc) -> acc*x end) 
    around = (Enum.sum(c) - Enum.max(c) )*2
    area+around
  end
end

IO.puts "Total size: " <> Integer.to_string(Advent2p2.calculate)
