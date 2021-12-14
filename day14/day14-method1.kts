#!/usr/bin/env -S kotlinc -script

import java.io.*

fun step(temp: String, formulas: List<Pair<String, String>>): String {
  val buf = StringBuffer()
  buf.append(temp[0])
  (1 until temp.length).forEach { i->
    val A = temp[i-1]
    val B = temp[i]
    val C = formulas.find {it.first[0]==A && it.first[1]==B} ?.second ?: ""
    buf.append(C)
    buf.append(B)
  }
  return buf.toString()
}

fun parseInput(path: String): Pair<String, List<Pair<String, String>>> {
  val lines = File(path).readText().split("\n")
  val temp = lines[0]
  val formulas = lines.drop(2).dropLast(1).map {
    (it[0]+""+it[1]) to it[6].toString()
  }
  return (temp to formulas)
}

val (temp, formulas) = parseInput("./input.txt")

// println(temp)
// println(formulas)

var t = temp
(1..10).forEach {step->
  t = step(t, formulas)
  println("Step $step :")
  val counts = ('A'..'Z')
    .map { (t.length - t.replace(it+"","").length).toInt() }
    .filter{it>0}
  val min = counts.minOrNull()?:-1
  val max = counts.maxOrNull()?:-1
  // println(counts)
  println("Min: $min   Max: $max  Diff: ${max-min}")
  // println(t)
  println()
}
