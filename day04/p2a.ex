#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent4p2 do
  def calculate do
    puzzleinput = File.stream!("input") |> 
    Stream.map(fn(x) -> String.strip x end) |> 
    Enum.fetch!(-1)

    check(puzzleinput,1, ~r/^000000/)
  end

  def check( input,key,reg) do
    out = md5(input <> Integer.to_string(key))
    unless String.match?(out,reg) do
      key = check(input, key+1, reg)
    end 
    key
  end

  def md5(data) do
    :erlang.md5(data) |>
    Base.encode16(case: :lower)
  end
end

IO.puts "First successful key: " <> Integer.to_string(Advent4p2.calculate)
