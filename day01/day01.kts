#!/usr/bin/env -S kotlinc -script 

import java.io.File

fun processIncrease(depths: List<Int>): Int {
    return depths.fold(Pair(0, depths[0])) { (incr, lastDepth), depth ->
        if (depth > lastDepth) Pair(incr + 1, depth)
        else Pair(incr, depth)
    }.first
}

fun slidingWindow(depths: List<Int>): List<Int> {
    var x1: Int? = null
    var x2: Int? = null
    return depths.mapNotNull {
        val sum = if (x1 == null || x2 == null) null else x1!! + x2!! + it
        x1 = x2
        x2 = it
        sum
    }
}

fun main() {
    val depths = File("./input.txt").readLines().map { it.toInt() }
    val depthSum = slidingWindow(depths)
    println(processIncrease(depths))
    println(processIncrease(depthSum))
}
