#!/usr/bin/env -S dart

import 'dart:io';

const starts = '([{<';
const ends   = ')]}>';
const scores = [3, 57, 1197, 25137];

int findIllegalScore(String line) {
  final stack = <String>[];

  for(var i=0; i<line.length; i++) {
    final ch = line[i];
    final ind = ends.indexOf(ch);
    if(ind<0) {
      stack.add(ch);
    } else {
      final top = stack.removeLast();
      if(top != starts[ind]) {
        return scores[ind];
      }
    }
  }

  var completeScore = 0;
  for(var i=stack.length-1; i>=0; i--) {
    final ch = stack.removeAt(i);
    final ind = starts.indexOf(ch);
    completeScore = completeScore*5 + (ind+1);
  }

  return -completeScore;
}

void main() {
  var part1 = 0;
  var part2 = <int>[];

  File('./sample.txt').readAsLinesSync().forEach((line) {
    var score = findIllegalScore(line);
    if(score > 0) {
      part1 += score;
      // print(score);
    } else {
      part2.add(-score);
    }
  });

  part2.sort();
  final part2Score = part2[(part2.length/2).floor()];

  print("Part1: $part1");
  print("Part2: ${part2Score}");
}