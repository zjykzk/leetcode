#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//
// 从(r-1,c-1)倒推，因为这个位置开始可以确定最小值，而从(0,0)开始无法确定。
//

void print(int **d, int r, int *c) {
  for (int i = 0; i < r ; i++) {
    for (int j = 0; j < c[i]; j++) {
      printf("%d\t", d[i][j]);  
    }
    putchar('\n');
  }
  puts("--------------");
}

int calculateMinimumHP(int** dungeon, int dungeonRowSize, int *dungeonColSizes) {
  int r = dungeonRowSize, *c = dungeonColSizes;
  int **m = malloc(sizeof *m * (size_t)r), i, j, d;
  for (i = 0; i < r; i++) {
    m[i] = malloc(sizeof **m * (size_t)c[i]);
  } 

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((b)>(a)?(a):(b))
  m[r-1][c[r-1]-1] = max(1, 1-dungeon[r-1][c[r-1]-1]);
  for (i = r - 2, j = c[r-1]-1; i >= 0; i--) {
    m[i][j] = max(1, m[i+1][j]-dungeon[i][j]);
  }
  for (i = r - 1, j = c[r-1]-2; j >= 0; j--) {
    m[i][j] = max(1, m[i][j+1]-dungeon[i][j]);
  }

  for (i = r - 2; i >= 0; i--) {
    for (j = c[i] - 2; j >= 0; j--) {
      d = dungeon[i][j];
      m[i][j] = max(1, min(max(1, m[i+1][j]-d), max(1, m[i][j+1]-d)));
    }
  }

  return m[0][0];
}


#define init_data(t, c, d)            \
{                                     \
  int data[] = d;                     \
  (t) = malloc(sizeof data);          \
  memcpy((t), data, sizeof data);     \
  c = sizeof data/sizeof data[0];     \
}

int main(void) {
#define P99_PROTECT(...) __VA_ARGS__
  {
    int r = 3;
    int **d = malloc(sizeof *d * (size_t)r);
    int *c = malloc(sizeof *c * (size_t)r);
    init_data(d[0], c[0], P99_PROTECT({-2,-3,3}));
    init_data(d[1], c[1], P99_PROTECT({-5,-10,1}));
    init_data(d[2], c[2], P99_PROTECT({10,30,-5}));
    printf("%d\n", calculateMinimumHP(d, r, c));
    print(d, r, c);
  }
}
