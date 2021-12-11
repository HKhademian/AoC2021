// clear && g++ -Wall day11.cpp -o day11 && ./day11 && rm ./day11
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef unsigned char       U8;
typedef unsigned short      U16;
typedef unsigned long       U32;
typedef unsigned long long  U64;
typedef signed   char       I8;
typedef signed   short      I16;
typedef signed   long       I32;
typedef signed   long long  I64;

void readMap(const string path, vector<vector<U8>> &map) {
  ifstream file(path);
  string line;
  map.clear();
  if (!file.is_open()) {
    cerr << "Error opening file" << endl;
    exit(1);
    return;
  }
  while (getline(file, line)) {
    vector<U8> row;
    for (char c : line) {
      row.push_back(U8(c-'0'));
    }
    map.push_back(row);
  }
}

void showMap(const vector<vector<U8>> &map) {
  for (const auto &row : map) {
    for(const auto &c : row) {
      cout << U8(c+'0');
    }
    cout << endl;
  }
}

void progress(vector<vector<U8>> &map) {
  const I64 Y = map.size(), X = map[0].size();

  for(I64 y=0; y<Y; ++y)
  for(I64 x=0; x<X; ++x)
    map[y][x]++;
  
  bool changed = true;
  while(changed) {
    changed = false;

    for(I64 y=0; y<Y; ++y)
    for(I64 x=0; x<X; ++x)
    if(map[y][x] > 9) {
      changed = true;

      for(I64 yy=y-1; yy<=y+1; ++yy)
      for(I64 xx=x-1; xx<=x+1; ++xx)
      if(yy>=0 && yy<Y && xx>=0 && xx<X)
      if(yy!=y || xx!=x)
      if(map[yy][xx])
        map[yy][xx]++;

      map[y][x] = 0;
    }
  }
}

U64 countFlashes(const vector<vector<U8>> &map) {
  U64 c = 0;
  for(const auto &row : map)
  for(const auto &ch : row)
    if(!ch)
      ++c;
  return c;
}

int main() {
  vector<vector<U8>> map;
  readMap("./input.txt", map);
  //showMap(map);

  U64 part1 = 0, step;

  for(step=1; ; ++step) {
    progress(map);
    U64 f = countFlashes(map);
    if(step<=100) part1 += f;
    //cout << endl << "Step " << step << " Flashes: " << f << endl;
    //showMap(map);
    if(f==map.size()*map[0].size()) break;
  }
  
  cout << "Part1: " << part1 << endl;
  cout << "Part2: " << step << endl;
  return 0;
}