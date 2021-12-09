#!/usr/bin/env -S python3

from functools import reduce

def printMap(map):
  for row in map:
    for cell in row:
      print(cell, end='')
    print()

with open('./input.txt') as f:
  map = list(list(int(ch) for ch in row[:-1]) for row in list(f))

X = len(map[0])
Y = len(map)

lows = [ (x,y)
  for y in range(Y)
  for x in range(X)
  if (
    (x==0   or map[y][x]<map[y][x-1]) and
    (x==X-1 or map[y][x]<map[y][x+1]) and
    (y==0   or map[y][x]<map[y-1][x]) and
    (y==Y-1 or map[y][x]<map[y+1][x])
  )
]

basins = []
for low in lows:
  bmap = [[1 if (x,y)==low else 0 for x in range(X)] for y in range(Y)]
  changed = True
  while changed:
    changed = False
    for x in range(X):
      for y in range(Y):
        if (map[y][x]!=9 and (not bmap[y][x]) and (
          (x>0   and bmap[y][x-1]) or
          (x<X-1 and bmap[y][x+1]) or
          (y>0   and bmap[y-1][x]) or
          (y<Y-1 and bmap[y+1][x])
        )):
          changed = True
          bmap[y][x] = 1
  bsize = sum(1 for x in range(X) for y in range(Y) if bmap[y][x])
  basins.append(bsize)
  #print(low)
  #print(bsize)
  #printMap(bmap)
  #print()

# print(lows)
# print(basins)
basins.sort()
# print(basins)

part1 = sum([ 1+map[y][x] for (x,y) in lows ])
part2 = reduce(lambda a,b:a*b, basins[-3:])

print("Part1:", part1)
print("Part2:", part2)
