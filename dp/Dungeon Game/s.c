#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int calculateMinimumHP(int** dungeon, int dungeonRowSize, int *dungeonColSizes) {
  typedef int health[2];
  health **h = malloc(sizeof *h * (size_t)(dungeonRowSize+1));
  int i, j, b;
  bool fromLeft;
  for (i = 0; i < dungeonRowSize; i++) {
    h[i] = malloc((size_t)(dungeonColSizes[i]+1) * sizeof **h);
  }

#define blood(h, i, j) h[i][j][0]
#define min_init(h, i, j) h[i][j][1]

  for (i = 0; i < dungeonRowSize; i++) {
    blood(h, i, 0) = 1<<(8*sizeof(int)-1);
  }

  blood(h, 0, 0) = dungeon[0][0];
  if (h[0][0] <= 0) {
    blood(h, 0, 0) = 1;
    min_init(h, 0, 0) = 1-dungeon[0][0];
  } else {
    min_init(h, 0, 0) = 1;
    blood(h, 0, 0) = 1+dungeon[0][0];
  }

  for (i = 1; i <= dungeonRowSize; i++) {
    for (j = 1; j <= dungeonColSizes[i]; j++) {
      fromLeft = blood(h, i-1, j) < blood(h, i, j-1);
      b = (fromLeft ? blood(h, i, j-1) : blood(h, i-1, j)) + dungeon[i][j];
      blood(h, i, j) = b;
      min_init(h, i, j) = fromLeft? min_init(h, i, j-1) : min_init(h, i-1, j);
      if (b <= 0) {
        blood(h, i, j) = 1;
        min_init(h, i, j) += 1 - b;
      }
    }
  }

  return min_init(h,dungeonRowSize,dungeonColSizes[dungeonRowSize-1]);
}

int main(void) {

}
