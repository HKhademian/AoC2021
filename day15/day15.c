// clear && gcc day15.c -o day15 && ./day15 && rm ./day15

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

// #define HEAP_DEBUG
#include "heap.c"

#define MAX_SIZE 256

typedef signed int long I32;

I32 solve(I32 width, I32 height, I32 tiles, I32* costs) {
  const I32 cols = width*tiles , rows = height*tiles;
  char *visited = (char*) calloc(cols*rows, sizeof(char));
  QNode *queue = (QNode*) calloc(1, sizeof(QNode));
  enqueue(queue, 0, 0, 0);
  
  while(queue->next) {
    QNode *node = dequeue(queue);
    I32 row = node->row, col = node->col, cost = node->cost;
    free(node);

    if(col==cols-1 && row==rows-1) {
      return cost;
    }
    if(visited[row*cols + col]) {
      // puts("visited");
      continue;
    }
    visited[row*cols + col] = 1;

    for(I32 adj_row=row-1; adj_row<=row+1; ++adj_row)
    for(I32 adj_col=col-1; adj_col<=col+1; ++adj_col) {
      if(adj_row==-1 || adj_row==rows)  continue; // row not in range
      if(adj_col==-1 || adj_col==cols)  continue; // col not in range
      if(adj_col==col && adj_row==row)  continue; // not same
      if(adj_col!=col && adj_row!=row)  continue; // not diagnal
      I32 adj_cost = (
        costs[(adj_row%height)*width + (adj_col%width)] + (I32)(adj_row/height) + (I32)(adj_col/width) -1
      ) % 9 + 1;
      enqueue(queue, adj_row, adj_col, cost + adj_cost);
    }
  }

  return -1;
}


I32* readMap(const char* path, I32 *width, I32 *height) {
  FILE* file = fopen(path, "r");
  if(!file) {
    fprintf(stderr, "Cannot open file\n");
    exit(1);
    return NULL;
  }

  char ch;
  I32* costs = (I32*) calloc(MAX_SIZE*MAX_SIZE, sizeof(I32));
  I32* p = costs;

  *height=0;
  while((ch=fgetc(file))!=EOF) {
    (*width)=0;
    (*height)++;
    
    do *(p++) = ch - '0', (*width)++;
    while((ch=fgetc(file))!='\n');
  }

  return costs;
}

int main(void) {
  I32 width, height;
  
  I32 *costs = readMap("./input.txt", &width, &height);

  // I32 tiles = 2, rows = height*tiles, cols=width*tiles;
  // printf("read complete\nw:%-3lu\nh:%-3lu\n", width, height);
  // for(I32 r=0; r<rows; r++) {
  //   for(I32 c=0; c<cols; c++){
  //     I32 cost = (
  //       costs[(r%height)*width + (c%width)] -1 + (I32)(r/height) + (I32)(c/width)
  //     ) % 9 + 1;
  //     printf("%-3lu ", cost);
  //   }printf("\n");
  // }
  // exit(1);

  printf("Part1: %lu\n", solve(width, height, 1, costs));
  printf("Part2: %lu\n", solve(width, height, 5, costs));
  
  return 0;
}
