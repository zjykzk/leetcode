#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void print(int **d, int r, int *c) {
  for (int i = 0; i < r ; i++) {
    for (int j = 0; j < c[i]; j++) {
      printf("%d\t", d[i][j]);  
    }
    putchar('\n');
  }
  puts("--------------");
}

void printH(int (**d)[2], int r, int *c) {
  for (int i = 0; i < r ; i++) {
    for (int j = 0; j < c[i]; j++) {
      printf("[%d %d]\t", d[i+1][j+1][0], d[i+1][j+1][1]);  
    }
    putchar('\n');
  }
  puts("--------------");
}

int calculateMinimumHP(int** dungeon, int dungeonRowSize, int *dungeonColSizes) {
  typedef int health[2];
  health **h = malloc(sizeof *h * (size_t)(dungeonRowSize+1));
  int i, j, b;
  bool fromLeft;

  h[0] = malloc((size_t)(dungeonColSizes[0]+1) * sizeof **h);
  for (i = 1; i <= dungeonRowSize; i++) {
    h[i] = malloc((size_t)(dungeonColSizes[i-1]+1) * sizeof **h);
  }

#define blood(h, i, j) h[i][j][0]
#define min_init(h, i, j) h[i][j][1]

  for (i = 0; i <= dungeonRowSize; i++) {
    blood(h, i, 0) = 1<<(8*sizeof(int)-1);
  }
  for (i = 0; i <= dungeonColSizes[0]; i++) {
    blood(h, 0, i) = 1<<(8*sizeof(int)-1);
  }

  blood(h, 0, 1) = 1;
  min_init(h, 0, 1) = 1;

  for (i = 1; i <= dungeonRowSize; i++) {
    for (j = 1; j <= dungeonColSizes[i-1]; j++) {
      fromLeft = blood(h, i-1, j) < blood(h, i, j-1);
      b = (fromLeft ? blood(h, i, j-1) : blood(h, i-1, j)) + dungeon[i-1][j-1];
      blood(h, i, j) = b;
      min_init(h, i, j) = fromLeft? min_init(h, i, j-1) : min_init(h, i-1, j);
      if (b <= 0) {
        blood(h, i, j) = 1;
        min_init(h, i, j) += 1 - b;
      }
      printf("l:%d,%d, u:%d,%d, n:%d,%d\n", blood(h, i, j-1), min_init(h, i, j-1), blood(h, i-1,j), min_init(h,i-1,j), blood(h, i,j), min_init(h,i,j));
    }
  }

  printH(h, dungeonRowSize, dungeonColSizes);

  return min_init(h,dungeonRowSize,dungeonColSizes[dungeonRowSize-1]);
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
    size_t r = 3;
    int **d = malloc(sizeof *d * r);
    int *c = malloc(sizeof *c * r);
    init_data(d[0], c[0], P99_PROTECT({-2,-3,3}));
    init_data(d[1], c[1], P99_PROTECT({-5,-10,1}));
    init_data(d[2], c[2], P99_PROTECT({10,30,-5}));
    printf("%d\n", calculateMinimumHP(d, r, c));
    print(d, r, c);
  }
}
