#!/usr/bin/env -S python3

# (x,y)  x:p[0] y:p[1]

def printPoints(points, fold=(None,-1)):
  (faxle, fpos) = fold 
  minx, maxx = min(v for (v,_) in points) , max(v for (v,_) in points)
  miny, maxy = min(v for (_,v) in points) , max(v for (_,v) in points)
  for y in range(miny, maxy+1):
    for x in range(minx, maxx+1):
      print('#' if (x,y) in points else
            '-' if faxle=='y' and y==fpos else
            '|' if faxle=='x' and x==fpos else
            '.', end='')
    print()

def parseInput(path):
  points, folds = [],[]
  with open(path) as f:
    for line in f:
      line=line[:-1]
      if ',' in line:
        points.append(tuple(int(v) for v in line.split(',')))
      elif '=' in line:
        folds.append(tuple([line[11], int(line.split('=')[1])]))
  return points, folds

def foldPoints(points, fold):
  (faxle, fpos) = fold
  gstill = [(x,y) for (x,y) in points if (faxle=='x' and x<fpos) or (faxle=='y' and y<fpos)]
  gfold  = [(2*fpos-x,y) if faxle=='x' else (x,2*fpos-y)
          for (x,y) in points
          if (faxle=='x' and x>fpos) or (faxle=='y' and y>fpos)]
  result = list(gstill)
  [result.append(p) for p in gfold if not p in gstill]
  return result

points, folds = parseInput("./input.txt")

# print(folds)

for fold in folds:
  points = foldPoints(points, fold)
  print("After fold at", fold, "Visible points:", len(points))
  # printPoints(points)
  
printPoints(points)
