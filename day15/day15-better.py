import heapq
from collections import defaultdict


def solve(costs, tiles):
  HEIGHT, WIDTH = len(costs), len(costs[0])
  rows, cols = HEIGHT*tiles, WIDTH*tiles
  mincosts = defaultdict(int)


  START=(0,0)
  TARGET=(rows-1,cols-1)

  # priority queue element : (cost, row, col)
  pqueue = [(0, START[0], START[1])]
  visited = set()

  while len(pqueue) > 0:
    cost, row, col = heapq.heappop(pqueue)
    if (row, col) in visited:
      continue
    
    visited.add((row, col))
    mincosts[(row, col)] = cost

    if (row,col) == TARGET:
      # reach goal
      return cost

    neighbours = [(row-dR, col-dC)
      for (dR,dC) in [(0, 1), (0, -1), (1, 0), (-1, 0)]
      if (row-dR) in range(rows) and (col-dC) in range(cols)
    ]

    for adjRow, adjCol in neighbours:
      adjCost = (costs[adjRow%HEIGHT][adjCol%WIDTH] + adjRow//HEIGHT + adjCol//WIDTH - 1)%9+1
      heapq.heappush(pqueue, (cost+adjCost, adjRow, adjCol))

  return -1 # no path found

lines = open("./input.txt").read().strip().split("\n")
costs = [[int(v) for v in line] for line in lines]

HEIGHT, WIDTH = len(costs), len(costs[0])
print(f"Part 1: {solve(costs, 1)}")
print(f"Part 2: {solve(costs, 5)}")
