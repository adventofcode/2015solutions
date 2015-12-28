#!/usr/bin/env elixir

# by: steven critchfield
# https://github.com/critch

defmodule Advent10p2 do
  def calculate do
    x = File.stream!("input") |> Enum.map(fn(x) -> String.strip(x) end) |> Enum.fetch!(-1)
    iter = 50

    String.length(look_and_say(x,iter))
  end

  def look_and_say(x,0) do
    x
  end
  def look_and_say(x,iter) do
    # recursion
    z = l_s(x)
    look_and_say(z,iter - 1)
  end
  def l_s(x) do
    val = String.codepoints(x) |>
    Enum.reduce({"",0,""}, fn(z, acc) -> l_s_r(z,acc) end) 

    # flush final value
    l_s_r(" ", val) |>
    elem(2)
  end
  def l_s_r(z,acc) do
    cond do
      elem(acc,0) == "" -> { z, 1, "" }
      elem(acc,0) == z -> { z, elem(acc,1) + 1, elem(acc,2) }
      true -> { z, 1, elem(acc,2) <> Integer.to_string(elem(acc,1)) <> elem(acc,0) }
    end
  end
end

IO.puts "String length: " <> Integer.to_string(Advent10p2.calculate)
