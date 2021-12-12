#!/usr/bin/env -S python3

def readMap(source):
  nodes  = []
  edges  = []
  smalls = []
  with open(source) as file:
    while(line := file.readline()[:-1]):
      atitle,btitle = line.split('-')
      if not atitle in nodes:
        nodes.append(atitle)
        smalls.append(atitle!='start' and atitle!='end' and atitle.islower())
      if not btitle in nodes:
        nodes.append(btitle)
        smalls.append(btitle!='start' and btitle!='end' and btitle.islower())
      a = nodes.index(atitle)
      b = nodes.index(btitle)
      edges.append((a,b))
  N = len(nodes)
  graph = [[(a,b) in edges or (b,a) in edges
    for a in range(N)] for b in range(N)]
  return graph, smalls, nodes, edges

def printGraph(graph):
  for row in graph:
    for cell in row:
      print(1 if cell else 0, end='')
    print()

def findPath(graph, smalls, START, END, path, spoil):
  cur = path[-1]
  if cur==END:
    return 1
  allpath = 0
  for n in range(len(graph)):
    if graph[cur][n] and n!=START:
      if not smalls[n] or not n in path:
        allpath += findPath(graph, smalls, START, END, path+[n], spoil)
      elif not spoil:
        allpath += findPath(graph, smalls, START, END, path+[n], True)
  return allpath

graph, smalls, nodes, edges = readMap("./input.txt")
START, END = nodes.index('start'), nodes.index('end')

# print(smalls)
# print(nodes)
# print(edges)
# print(START, END)
# print(graph[START])
# printGraph(graph)

part1 = findPath(graph, smalls, START, END, [START], True)
part2 = findPath(graph, smalls, START, END, [START], False)

print("Part1: ", part1)
print("Part2: ", part2)
