#!/usr/bin/env elixir

# by: steven critchfield
# https://github.com/critch

defmodule Advent12p1 do
  def calculate do
    {:ok, acc } =  File.read("input") 
    Regex.scan(~r/([\-0-9]+)/, acc) |>
    Stream.map(fn x -> String.to_integer(hd(x)) end) |>
    Enum.sum
  end
end

IO.puts "Sum of all numbers: " <> Integer.to_string(Advent12p1.calculate)
