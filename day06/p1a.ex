#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent6p1 do
  def calculate do
    File.stream!("input") |>
    Stream.map(fn(x) -> Regex.named_captures(~r/(?<com>.+) (?<sx>[0-9]+),(?<sy>[0-9]+) through (?<ex>[0-9]+),(?<ey>[0-9]+)/, x) end) |>
    Enum.reduce(HashDict.new, fn(x,state) -> 
        light(state, Map.get(x,"com"), [
          String.to_integer(Map.get(x, "sx")), String.to_integer(Map.get(x, "sy")), 
          String.to_integer(Map.get(x, "ex")), String.to_integer(Map.get(x, "ey"))
        ] ) 
    end) |>
    HashDict.keys |>
    Enum.count
  end

  def light(state, "turn off", [sx,sy, ex,ey]) do
    Enum.reduce(sx..ex, state, fn(x, acc) -> 
        Enum.reduce(sy..ey, acc, fn(y, acc) ->
          HashDict.delete(acc, [x,y])
        end)
    end)
  end
  def light(state, "turn on", [sx,sy, ex,ey]) do
    Enum.reduce(sx..ex, state, fn(x, acc) ->
        Enum.reduce(sy..ey, acc, fn(y, acc) ->
          HashDict.put_new(acc,[x,y], 1)
        end)
    end)
  end
  def light(state, "toggle", [sx,sy, ex,ey]) do
    Enum.reduce(sx..ex, state, fn(x,acc) ->
        Enum.reduce(sy..ey, acc, fn(y,acc) ->
          if HashDict.has_key?(acc, [x,y]), 
            do: HashDict.delete(acc, [x,y]),
            else: HashDict.put(acc, [x,y], 1)
        end )
    end)
  end
end

IO.puts "Lights on: " <> Integer.to_string(Advent6p1.calculate)
