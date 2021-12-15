// clear && gcc day15.c -o day15 && ./day15 && rm ./day15

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef unsigned long U32;
const U32 MAX_U32 = -1;

#define SIZE 256

U32 width, height;
U32 map[SIZE][SIZE];
U32 dpt[SIZE][SIZE];

static U32 min2(U32 a, U32 b) { return a>b?b:a; }
static U32 min4(U32 a, U32 b, U32 c, U32 d) { return min2(min2(a,b),min2(c,d)); }

void readMap(const char* path) {
  FILE* file = fopen(path, "r");
  if(!file) {
    fprintf(stderr, "Cannot open file\n");
    exit(1);
    return;
  }

  for(U32 y=0; y<SIZE; ++y)
  for(U32 x=0; x<SIZE; ++x)
    map[y][x] = 0 , dpt[SIZE][SIZE] = 0;

  char ch;
  height=0;
  while((ch=fgetc(file))!=EOF) {
    width=0;
    
    do map[height][width] = ch - '0', width++;
    while((ch=fgetc(file))!='\n');
    
    height++;
  }
}

int main(void) {
  // readMap("./sample.txt");
  readMap("./sample.txt");
  printf("read complete\nw:%-3d\nh:%-3d\n", width, height);

  printf("Part1: %u\n", findShortestPath(-1, -1, 0, 0));

  return 0;
}
