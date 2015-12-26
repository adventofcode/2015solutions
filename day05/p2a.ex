#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent5p2 do
  def calculate do
    File.stream!("input") |>
    Stream.map(fn(x)-> String.strip(x) end) |>
    # xyx example
    Stream.filter(fn(x) -> String.match?(x, ~r/(\S)\S\1/)  end) |>
    # two letter repeated structure
    Stream.filter(fn(x) -> String.match?(x, ~r/(\S\S).*\1/) end) |>
    Enum.map(fn(x) -> x end) |>
    Enum.count
  end
end

IO.puts "Nice String count: " <> Integer.to_string(Advent5p2.calculate)
