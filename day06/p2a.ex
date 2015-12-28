#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent6p2 do
  def calculate do
    File.stream!("input") |>
    Stream.map(fn(x) -> Regex.named_captures(~r/(?<com>.+) (?<sx>[0-9]+),(?<sy>[0-9]+) through (?<ex>[0-9]+),(?<ey>[0-9]+)/, x) end) |>
    Enum.reduce(HashDict.new, fn(x,state) -> 
        light(state, Map.get(x,"com"), [
          String.to_integer(Map.get(x, "sx")), String.to_integer(Map.get(x, "sy")), 
          String.to_integer(Map.get(x, "ex")), String.to_integer(Map.get(x, "ey"))
        ] ) 
    end) |>
    HashDict.values |>
    Enum.sum
  end

  def light(state, "turn off", [sx,sy, ex,ey]) do
    Enum.reduce(sx..ex, state, fn(x, acc) -> 
        Enum.reduce(sy..ey, acc, fn(y, acc) ->
          elem(HashDict.get_and_update(acc, [x,y], fn(a) -> {a, change_by(a,-1)} end), 1)
        end)
    end)
  end
  def light(state, "turn on", [sx,sy, ex,ey]) do
    Enum.reduce(sx..ex, state, fn(x, acc) ->
        Enum.reduce(sy..ey, acc, fn(y, acc) ->
          elem(HashDict.get_and_update(acc, [x,y], fn(a) -> {a, change_by(a,1)} end), 1)
        end)
    end)
  end
  def light(state, "toggle", [sx,sy, ex,ey]) do
    Enum.reduce(sx..ex, state, fn(x,acc) ->
        Enum.reduce(sy..ey, acc, fn(y,acc) ->
          elem(HashDict.get_and_update(acc, [x,y], fn(a) -> {a, change_by(a, 2) } end), 1)
        end)
    end)
  end
  def change_by(a,val) do
    if a == nil, do: a = 0
    a = a + val
    if a < 0, do: a = 0
    a
  end
end

IO.puts "Total brightness: " <> Integer.to_string(Advent6p2.calculate)
