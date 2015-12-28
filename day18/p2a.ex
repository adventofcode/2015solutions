#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent18p2 do
  def calculate do
    state = File.stream!("input") |>
    Stream.map(fn(x) -> String.strip(x) end) |>
    Enum.join

    side = trunc :math.sqrt(String.length(state)) 

    1..100 |>
    Enum.reduce(state, fn(x,state) -> cycle(x,state, side) end) |>
    String.split("") |>
    Enum.filter(fn(x) -> x == "#" end)|>
    Enum.count
  end

  def cycle(x,state, side) do
    IO.puts("Starting cycle: #{x}")
    Stream.map(0..side-1, fn(x) -> Enum.map(0..side-1, fn(y) ->
      cond do
        x == 0 and y == 0 -> Task.async(fn() -> "#" end)
        x == side-1 and y == 0 -> Task.async(fn() -> "#" end)
        x == 0 and y == side-1 -> Task.async(fn() -> "#" end)
        x == side-1 and y == side-1 -> Task.async(fn() -> "#" end)
        true -> Task.async(fn() -> brute(state,x,y,side) end)
      end
    end) end) |>
    Stream.map(fn(w) -> Enum.map(w,fn(z) -> Task.await(z,5000000) end) end) |>
    Enum.join
  end

  def brute(state,x,y,side) do
    ind = index(x,y,side)
    cur = String.slice(state, ind..ind)

    neighbors = [top_row(state, x,y,side,ind), middle_row(state,x,y,side,ind), bottom_row(state,x,y,side,ind)]
    count = String.split(Enum.join(neighbors), "") |>
    Enum.filter(fn(x) -> x == "#" end) |>
    Enum.count
   
    cond do
      cur == "#" and count < 2 -> "."
      cur == "#" and count > 3 -> "."
      cur == "#" -> "#"
      cur == "." and count == 3 -> "#"
      cur == "." -> "."
    end
  end

  def index(x,y,side), do: x*side + y

  def top_row(state,x,y,side,ind) do
    cond do
      x == 0 -> ""
      y == 0 -> String.slice(state, ind-side..ind-side+1)
      y == side-1 -> String.slice(state, ind-side-1..ind-side)
      true -> String.slice(state, ind-side-1..ind-side+1)
    end
  end
  def middle_row(state,_,y,side,ind) do
    cond do
      y == 0 -> String.slice(state, ind+1..ind+1)
      y == side-1 -> String.slice(state, ind-1..ind-1)
      true -> String.slice(state, ind-1..ind-1) <> String.slice(state, ind+1..ind+1)
    end
  end
  def bottom_row(state,x,y,side,ind) do
    cond do
      x == side-1 -> ""
      y == 0 -> String.slice(state, ind+side..ind+side+1)
      y == side-1 -> String.slice(state, ind+side-1..ind+side)
      true -> String.slice(state, ind+side-1..ind+side+1)
    end
  end
end

IO.puts "Lights on: " <> Integer.to_string(Advent18p2.calculate)
