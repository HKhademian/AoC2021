#!/usr/bin/env -S python3

def decodeSegments(segments):
  LEN = dict((l,list(it for it in segments if len(it)==l)) for l in range(8))
  NUM = list(None for _ in range(10))
  SEG = dict((chr(ord('a')+i), None) for i in range(7))

  NUM[1] = LEN[2].pop()
  NUM[7] = LEN[3].pop()
  NUM[4] = LEN[4].pop()
  NUM[8] = LEN[7].pop()

  SEG['a'] = (NUM[7]-NUM[1]).pop()

  NUM[3] = next(segs for segs in LEN[5] if len(segs-NUM[1])==3)
  LEN[5].remove(NUM[3])

  SEG['d'] = (NUM[3]-NUM[4]).pop()

  NUM[9] = next(segs for segs in LEN[6] if len(segs-NUM[3])==1)
  LEN[6].remove(NUM[9])

  SEG['f'] = (NUM[9]-NUM[3]).pop()
  SEG['e'] = (NUM[8]-NUM[9]).pop()

  NUM[6] = next(segs for segs in LEN[6] if len(NUM[1]-segs)==1)
  LEN[6].remove(NUM[6])

  NUM[0] = LEN[6].pop()

  SEG['b'] = (NUM[1]-NUM[6]).pop()

  NUM[5] = next(segs for segs in LEN[5] if len(segs-set([SEG['b']]))==len(segs))
  LEN[5].remove(NUM[5])

  NUM[2] = LEN[5].pop()

  SEG['c'] = (NUM[1]-set([SEG['b']])).pop()
  SEG['g'] = (NUM[8]-NUM[0]).pop()

  return SEG,NUM

def decodeNumbers(segments, numbers):
  SEG,NUM = decodeSegments(segments)

  return NUM, SEG, [next(i for i in range(10) if NUM[i]==num) for num in numbers]


with open('./input.txt') as file:
  inputs = list(file)

part1 = 0
part2 = 0

for inp in inputs:
  inp = inp[:-1]
  parts = inp.split(" | ")
  segments = list(set(it) for it in parts[0].split(" "))
  numbers = list(set(it) for it in parts[1].split(" "))
  NUM, SEG, nums = decodeNumbers(segments, numbers)

  ans1 = sum(1 for n in nums if n in [1,4,7,8])
  ans2 = int(''.join([str(n) for n in nums]))

  part1 += ans1
  part2 += ans2

  #print(inp)
  #print(NUM)
  #print(SEG)
  #print(nums)
  #print("ANS1:", ans1)
  #print("ANS2:", ans2)
  #print()

print("Part1: ", part1)
print("Part2: ", part2)