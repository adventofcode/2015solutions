#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent5p1 do
  def calculate do
    File.stream!("input") |>
    Stream.map(fn(x)-> String.strip(x) end) |>
    Stream.filter(fn(x) -> bad_combo?(x) end) |>
    Stream.filter(fn(x) -> three_vowels(x) end) |>
    Stream.filter(fn(x) -> doubles(x) end) |>
    Enum.count
  end

  def bad_combo?(x), do: !String.contains?(x,["ab","cd","pq","xy"]) 
  def doubles(x), do: Regex.match?(~r/([a-z])\1/, x)
  def is_a_vowel(x), do: Regex.match?(~r/(a|e|i|o|u)/, x)
  def three_or_more?(x), do: x>2

  def three_vowels(x) do
    String.codepoints(x) |>
    Stream.filter(fn(x)-> is_a_vowel(x) end) |>
    Enum.count |>
    three_or_more?
  end

end

IO.puts "Nice String count: " <> Integer.to_string(Advent5p1.calculate)
