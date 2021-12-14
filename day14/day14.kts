#!/usr/bin/env -S kotlinc -script

import java.io.*

fun step(temp: Map<Pair<Char,Char>, Long>, formulas: Map<Pair<Char,Char>, Char>): MutableMap<Pair<Char,Char>,Long> {
  val result = mutableMapOf<Pair<Char,Char>, Long>()
  formulas.entries.forEach { formula ->
    val A = formula.key.first
    val B = formula.key.second
    val C = formula.value
    val v = temp.get(A to B) ?: return@forEach
    result.set(A to C, (result.get(A to C)?:0)+v )
    result.set(C to B, (result.get(C to B)?:0)+v )
  }
  return result
}

fun parseInput(path: String): Pair<String, Map<Pair<Char,Char>, Char>> {
  val lines = File(path).readText().split("\n")
  val temp = lines[0]
  val formulas = lines.drop(2).dropLast(1).map {
    (it[0] to it[1]) to it[6]
  }.toMap()
  return (temp to formulas)
}

// read data
val (temp, formulas) = parseInput("./input.txt")

// count pairs in temp
val pairs = mutableMapOf<Pair<Char, Char>, Long>()
(1 until temp.length).forEach { i->
  val key = temp[i-1] to temp[i]
  pairs.set(key, (pairs.get(key)?:0L) + 1L)
}

// println(temp)
// println(formulas)
// println(pairs.entries.filter{ it.value>0})

// do steps
var data = pairs
(1..40).forEach { step -> 
  println("Step $step")
  data = step(data, formulas)
}

// count least/most common chars
val counts = ('A'..'Z').map { A -> 
  ('A'..'Z').sumOf { B-> data.get(A to B)?:0 } + (
    if(temp[temp.length-1]==A) 1L else 0L
  )
}.filter{it>0}
val min = counts.minOrNull() ?: -1L
val max = counts.maxOrNull() ?: -1L
val diff = max - min
println(min)
println(max)
println(diff)
