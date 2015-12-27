#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent8p1 do
  def calculate do
    [ wc, lwc] = File.stream!("input") |>
    Stream.map(fn(x)-> String.strip(x) end) |>
    Enum.reduce( [0,0], fn(x, acc) -> tweak(x,acc) end)
    IO.inspect([wc,lwc])
    wc - lwc
  end

  def tweak(x, acc) do
    strlen = byte_size(x)
    str = Regex.replace(~r/(\\\"|\\x[0-9a-f][0-9a-f]|\\\\)/, x, "!") 
    smaller = str |>String.length |> - 2
    [strlen + Enum.at(acc,0), Enum.at(acc,1) + smaller ]
  end
end

IO.puts "Difference in strings is: " <> Integer.to_string(Advent8p1.calculate)
