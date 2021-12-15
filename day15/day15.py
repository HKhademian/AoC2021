import heapq
from collections import defaultdict


def solve(costs):
  HEIGHT, WIDTH = len(costs), len(costs[0])
  rows, cols = HEIGHT, WIDTH
  mincosts = defaultdict(int)

  START=(0,0)
  TARGET=(rows-1,cols-1)

  # priority queue element : (cost, row, col)
  pqueue = [(0, START[0], START[1])]
  visited = set()

  while len(pqueue) > 0:
    cost, row, col = heapq.heappop(pqueue)

    if (row, col) == TARGET:
      # reach goal
      return cost
    
    if (row, col) in visited:
      continue
    
    visited.add((row, col))
    mincosts[(row, col)] = cost

    neighbours = [(row-dR, col-dC)
      for (dR,dC) in [(0, 1), (0, -1), (1, 0), (-1, 0)]
      if (row-dR) in range(rows) and (col-dC) in range(cols)
    ]

    for adjRow, adjCol in neighbours:
      adjCost = costs[adjRow][adjCol]
      heapq.heappush(pqueue, (cost+adjCost, adjRow, adjCol))

  return -1 # no path found

lines = open("./simple.txt").read().strip().split("\n")
costs = [[int(v) for v in line] for line in lines]
print(f"Part 1: {solve(costs)}")

HEIGHT, WIDTH = len(costs), len(costs[0])
costs = [[(costs[r%HEIGHT][c%WIDTH] + r//HEIGHT + c//WIDTH - 1)%9+1
  for c in range(WIDTH*5)]
  for r in range(HEIGHT*5)]
print(f"Part 2: {solve(costs)}")
