#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// the problem is equal to two person walk from the (0, 0) to (n-1,n-1)
// the max cherry can pick
//
// let s the steps, the person current walk
// let xi the person i's row number, xj the person j's row number
//
// c[s][xi][xj] = grid[xi][s-xi+1] +  TODO

int cherryPickup(int** grid, int gridRowSize, int gridColSize) {
  int c[2][51][51], cc, n, p, mi, mj, m, i, j;
  int t = 1, l = gridRowSize + gridColSize, xi, yi, xj, yj;
  for (i = 0; i <= gridRowSize; i++) {
    for (j = 0; j <= gridColSize; j++) {
      c[0][i][j] = -1;
      c[1][i][j] = -1;
    }
  }

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

  for (; t < l; t++) {
    c[0][0][0] = t == 1 ? 0 : -1;
    for (xi = 1, mi = min(gridRowSize + 1, t + 1); xi < mi; xi++) {
      yi = t - xi + 1;
      if (yi > gridColSize) continue;
      i = grid[xi-1][yi-1];

      for (xj = 1, mj = min(gridColSize + 1, t + 1); xj < mj; xj++) {
        yj = t - xj + 1;
        if (yj > gridColSize) continue;
        j = grid[xj-1][yj-1];

        n = t & 1; 
        if (i == -1 || j == -1) {
          c[n][xi][xj] = -1;
          continue;
        }

        p = !n;
        m = max(max(c[p][xi][xj], c[p][xi][xj-1]), max(c[p][xi-1][xj], c[p][xi-1][xj-1]));
        if (m == -1) {
          c[n][xi][xj] = -1;
          continue;
        }

        cc = i;
        if (xi != xj) {
          cc += j;
        }

        cc += m;
        c[n][xi][xj] = cc;
      }
    }
  }

  m =  max(c[(t-1)&1][gridRowSize][gridColSize], 0);
#undef max
#undef min

  return m;
}

int main(void) {
  /*int d[][10] = {*/
    /*{ 1,-1, 1,-1, 1,1, 1, 1,1,-1},*/
    /*{-1, 1, 1,-1,-1,1, 1, 1,1, 1},*/
    /*{ 1, 1, 1,-1, 1,1, 1, 1,1, 1},*/
    /*{ 1, 1, 1, 1, 1,1, 1, 1,1, 1},*/
    /*{-1, 1, 1, 1, 1,1, 1, 1,1, 1},*/
    /*{ 1,-1, 1, 1, 1,1,-1, 1,1, 1},*/
    /*{ 1, 1, 1,-1, 1,1,-1, 1,1, 1},*/
    /*{ 1,-1, 1,-1,-1,1, 1, 1,1, 1},*/
    /*{ 1, 1,-1,-1, 1,1, 1,-1,1,-1},*/
    /*{ 1, 1,-1, 1, 1,1, 1, 1,1, 1}};*/

  /*int d[][3] = {*/
    /*{ 1, 1, -1},*/
    /*{ 1,-1, 1},*/
    /*{-1, 1, 1},*/
  /*};*/
 
  int d[][3] = {
    {0, 1, -1},
    {1, 0, -1},
    {1, 1,  1},
  };
  int r = sizeof(d) / sizeof(d[0]), c = sizeof(d[0])/sizeof(int);
  int** m = malloc(sizeof(*m) * (size_t)r);
  for (int i = 0; i < r; i++) {
    m[i] = d[i];
  }
  printf("%d %d %d\n", r, c, cherryPickup(m, r, c));
}
