#!/usr/bin/env -S kotlinc -script

import java.io.File

val data = File("./input.txt")
  .readText()
  .replace("\n", "")
  .split(",")
  .map { it.toInt() }

val count = data.size
val min_pos = data.minOrNull() ?: -1
val max_pos = data.maxOrNull() ?: -1

val answer = (min_pos..max_pos)
  .asSequence()
  .map { target ->
    target to data.sumOf {
      val dist = Math.abs(target-it)
      dist * (dist+1) / 2
    }
  }
  .minByOrNull { it.second }

println(answer)
