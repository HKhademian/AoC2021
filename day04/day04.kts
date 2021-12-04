#!/usr/bin/env -S kotlinc -script 

import java.io.BufferedReader
import java.io.File

class Board(val ROWS: Int = 5, val COLS: Int = 5) {
  private val cells = Array(ROWS*COLS) { Pair(0, false)}
  private var lastCall = 0
  private var win = false

  override fun toString(): String {
    val buf = StringBuffer()
    (0 until ROWS).forEach { row ->
      (0 until COLS).forEach { col ->
        if(cells[row * COLS + col].second)
          buf.append('*')
        buf.append(cells[row * COLS + col].first)
        buf.append('\t')
      }
      buf.appendLine()
    }
    return buf.toString()
  }

  fun read(reader: BufferedReader) {
    win = false
    lastCall = 0
    reader.readLine()
    (0 until ROWS).forEach { row ->
      val data = reader.readLine().split(" ")
        .filter { it.isNotEmpty() }
        .map { it.toInt() }
      (0 until COLS).forEach { col ->
        cells[row * COLS + col] = Pair(data[col], false)
      }
    }
  }

  fun callNum(num: Int) {
    (0 until ROWS).forEach { row ->
      (0 until COLS).forEach { col ->
        if(cells[row*COLS+col].first==num) {
          cells[row*COLS+col] = Pair(num, true)
          lastCall = num
        }
      }
    }
  }

  fun isWin(): Boolean {
    if(win) return win
    (0 until ROWS).forEach { row ->
      win = true
      (0 until COLS).forEach { col ->
        win = win and cells[row*COLS+col].second
      }
      if(win) return true
    }
    (0 until COLS).forEach { col ->
      win = true
      (0 until ROWS).forEach { row ->
        win = win and cells[row*COLS+col].second
      }
      if(win) return true
    }
    win = false
    return false
  }

  fun getScore(): Int {
    val sum = cells.filter { !it.second }.map { it.first }.sum()
    return sum*lastCall
  }

}

val data = "./input.txt" to 100
// val data = "./sample.txt" to 100

val reader = File(data.first).bufferedReader()
val boards = mutableListOf<Board>()

val calls = reader.readLine().split(",").map { it.toInt() }

(1..data.second).forEach {
  val board = Board(5,5)
  board.read(reader)
  boards.add(board)

  // println(board)
  // println()
}

// println(calls)

var lastNewWin = -1
var lastNewWinScore = 0

calls.forEach { num ->
  boards.forEachIndexed { index, board ->
    val pastWin = board.isWin()
    board.callNum(num)
    val newWin = board.isWin()
    if(pastWin != newWin) {
      lastNewWin = index
      lastNewWinScore = board.getScore()
      print("New Win: ")
      print(index)
      print("\ton call: ")
      print(num)
      print("\twith score: ")
      print(lastNewWinScore)
      println()
    }
  }
}

println("LAST WIN")
println(lastNewWin)
println(lastNewWinScore)
System.exit(1)
