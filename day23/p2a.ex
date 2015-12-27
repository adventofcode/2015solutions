#!/usr/bin/env elixir

# By: Steven Critchfield
# https://github.com/critch

defmodule Advent23p2 do
  require Integer

  def calculate do
    prog = File.stream!("input") |>
    Stream.map(fn(x) -> String.strip(x) end ) |>
    Enum.map(fn(x) -> String.split(x, " ") end) 

    Stream.cycle([1]) |> # dummy source to keep rest running
    Stream.transform([ prog, 1, 0, 0 ], fn(_,acc) -> do_work(acc) end) |>
    Enum.to_list |>
    Enum.fetch!(-1)
  end

  def do_work(state) do
    [prog, _, _, i] = state
    inst = Enum.fetch!(prog,i) 
    ev = dw( Enum.fetch!(inst,0), inst, state)
    [_,_,b,i] = ev
    if i > Enum.count(prog)-1 do
      {:halt, state}
    else
      if( i < 1) do
        {:halt, state}
      else 
        { [b], ev}
      end
    end
  end

  def dw("hlf", inst, state) do 
    [_, reg] = inst
    [prog,a,b,i] = state
    if reg == "a" do 
      [ prog, trunc(a/2), b, i+1]
    else
      [prog, a, trunc(b/2), i+1]
    end
  end
  def dw("tpl", inst, state) do
    [_, reg] = inst
    [prog, a,b,i] = state
    if reg == "a" do 
      [prog, a*3, b, i+1]
    else
      [prog, a, b*3, i+1]
    end
  end
  def dw("inc", inst, state) do
    [_,reg] = inst
    [prog,a,b,i] = state
    if reg == "a" do 
      [prog, a+1, b, i+1]
    else 
      [prog, a, b+1, i+1]
    end
  end
  def dw("jmp", inst, state) do
    [_, dist ] = inst
    [prog,a,b,i] = state
    [prog, a, b, i+String.to_integer(dist)]
  end
  def dw("jie", inst, state) do
    [_,reg, dist] = inst
    dist = String.to_integer(dist)
    [prog,a,b,i] = state
    if reg == "a," do 
      check = a
    else 
      check = b
    end
    if Integer.is_even(check) do
      [prog, a, b, i+dist]
    else
      [prog, a, b, i+1]
    end
  end
  def dw("jio", inst, state) do
    [_,reg, dist] = inst
    dist = String.to_integer(dist)
    [prog,a,b,i] = state
    if reg == "a," do
      check = a
    else 
      check = b
    end
    if check == 1 do 
      [prog, a, b, i+dist]
    else 
      [prog, a, b, i+1]
    end
  end
end

IO.puts "At end of program, Register b=" <> Integer.to_string(Advent23p2.calculate)
