#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent18p1 do
  def calculate do
    state = File.stream!("input") |>
    Stream.map(fn(x) -> String.strip(x) end) |>
    Enum.join

    side = trunc :math.sqrt(String.length(state)) 

    1..100 |>
    Enum.reduce(state, fn(x,state) -> cycle_brute(x,state, side) end) |>
    String.split("") |>
    Enum.filter(fn(x) -> x == "#" end)|>
    Enum.count
  end

  def display(state, side) do
    disp = for x<- 0..side-1 do
      start = x*side
      String.slice(state, start..start+side-1)
    end |>
    Enum.join("\n")
    IO.puts disp
    disp
  end

  def cycle_brute(x,state, side) do
    IO.puts("Starting cycle: #{x}")
    for x <- 0..side-1, y <- 0..side-1 do
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
    end |>
    Enum.join
  end

  def cycle_earlyout(x,state,side) do
    IO.puts("Starting cycle: #{x}")
    for x <- 0..side-1, y <- 0..side-1 do
      ind = index(x,y,side)
      cur = String.slice(state, ind..ind)

      Stream.transform(-1..1, %{count: 0, state: state, cur: cur, ind: ind, side: side,x: x,y: y, neighbors: ""},
          fn(x,acc) -> ct(x,acc) end
      ) |>
      Enum.fetch(-1)
    end |>
    Enum.join 
  end

  def ct(x,acc) do
    # here because we didn't break, so go ahead and get next line
    cur = Map.get(acc,:cur)
    neighbors = Map.get(acc,:neighbors) <> cond do
      x == -1 -> top_row(Map.get(acc,:state), Map.get(acc,:x), Map.get(acc,:y), Map.get(acc,:side), Map.get(acc,:ind))
      x == 0 -> middle_row(Map.get(acc,:state), Map.get(acc,:x), Map.get(acc,:y), Map.get(acc,:side), Map.get(acc,:ind))
      x == 1 -> bottom_row(Map.get(acc,:state), Map.get(acc,:x), Map.get(acc,:y), Map.get(acc,:side), Map.get(acc,:ind))
    end 

    count = String.split(neighbors,"") |>
    Enum.filter(fn(x) -> x == "#" end) |>
    Enum.count
   
    acc = Map.put(acc,:neighbors, neighbors)
    acc = Map.put(acc,:count, count)

    cond do
      cur == "#" and count > 3 -> {:halt, "."}
      x == 1 and cur == "#" and count < 2 -> {:halt, "."}
      x == 1 and cur == "#" -> {:halt, "#"}
      x == 1 and cur == "." and count == 3 -> {:halt, "#"}
      x == 1 -> {:halt, "."}
      true -> { [], acc }
    end
  end

  def index(x,y,side), do: x*side + y

  def top_row(state,x,y,side,ind) do
    cond do
      x == 0 -> "..."
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
      x == side-1 -> "..."
      y == 0 -> String.slice(state, ind+side..ind+side+1)
      y == side-1 -> String.slice(state, ind+side-1..ind+side)
      true -> String.slice(state, ind+side-1..ind+side+1)
    end
  end
end

IO.puts "Lights on: " <> Integer.to_string(Advent18p1.calculate)
