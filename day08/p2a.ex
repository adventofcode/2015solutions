#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent8p2 do
  def calculate do
    [ wc, hwc] = File.stream!("input") |>
    Stream.map(fn(x)-> String.strip(x) end) |>
    Enum.reduce( [0,0], fn(x, acc) -> tweak(x,acc) end)
    IO.inspect([wc,hwc])
    hwc - wc 
  end

  def tweak(x, acc) do
    strlen = byte_size(x)
    str = Regex.replace(~r/(\\x[0-9a-f][0-9a-f]|\\\"|\\\\)/, x, fn(z) -> lookup(z) end)
    [strlen + Enum.at(acc,0), byte_size(str) + 4 + Enum.at(acc,1)]
  end
  def lookup(z) do
    cond do
      "\\\"" == z -> "!!!!"
      "\\\\" == z -> "!!!!"
      true -> "!!!!!"
    end
  end
end

IO.puts "Difference in strings is: " <> Integer.to_string(Advent8p2.calculate)
