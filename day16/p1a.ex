#!/usr/bin/env elixir

# by: steven critchfield
# https://github.com/critch

defmodule Advent16p1 do
  def calculate do
    valid = %{ 
      "children" => 3, 
      "cats" => 7, 
      "samoyeds" => 2, 
      "pomeranians" => 3, 
      "akitas" => 0, 
      "vizslas" => 0, 
      "goldfish" => 5, 
      "trees" => 3, 
      "cars" => 2, 
      "perfumes" => 1
    }
    File.stream!("input") |>
    Stream.map(fn(x) -> Regex.named_captures(
          ~r/Sue (?<num>[0-9]+): (?<i1>[a-z]+): (?<v1>[0-9]+), (?<i2>[a-z]+): (?<v2>[0-9]+), (?<i3>[a-z]+): (?<v3>[0-9]+)/, 
          x)
    end) |>
    Stream.filter(fn(x) -> check(x,1,valid) end) |>
    Stream.filter(fn(x) -> check(x,2,valid) end) |> 
    Stream.filter(fn(x) -> check(x,3,valid) end) |>
    Enum.fetch!(-1) |>
    Map.fetch!("num")
  end


  def check(x,i,valid) do
    item = Map.fetch!(x,"i"<>Integer.to_string(i))
    val = Map.fetch!(x,"v"<>Integer.to_string(i)) |> String.to_integer
    Map.fetch!(valid, item) == val 
  end
end

IO.puts "Matched Sue: " <> Advent16p1.calculate
