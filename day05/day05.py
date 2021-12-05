#!/usr/bin/env -S python3

field = [[0 for _ in range(1000)] for _ in range(1000)]

with open('./input.txt') as file:
  lines = list(file)

sign = lambda v: (v>0)-(v<0)

toPoint = lambda p: tuple(int(v) for v in p.split(','))

def printField():
  for row in field:
    for cell in row:
      print(cell, end='')
    print()

def drawLine(p1: (int, int), p2: (int, int)):
  dx, dy = p2[0]-p1[0] , p2[1]-p1[1]
  n = max(abs(dx), abs(dy))
  dx, dy = sign(dx), sign(dy)
  for i in range(n+1):
    x = p1[0] + dx*i
    y = p1[1] + dy*i
    field[y][x] += 1

def countIntersections():
  return sum([sum(1 for i in row if i>1) for row in field])

lines = [ line[:-1].split(' -> ') for line in lines ]
lines = [ (toPoint(p1),toPoint(p2)) for [p1,p2] in lines ]

for (p1,p2) in lines:
  # if p1[0] == p2[0] or p1[1]==p2[1]:
  drawLine(p1, p2)

# printField()
print("Intersection: ", countIntersections())
