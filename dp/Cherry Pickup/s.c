#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 关键是把题目转化成：
// 同时两个人从(0,0) -> (n-1,n-1)
// 另外，行数和列数定义后，可以走的次数是固定。例如，现在有r行， l列，那么最多可以走的次数是r+l-1
//
// 记行数为r，列数为l，当前走的步数为t，1<=t<=r+l-1
//
// 观察到，一个人现在的位置是(x, y)，已经走了t步，那么x+y=t+1。因此，两个人移动的时候可以记录状态
// c[t][x1][x2]表示两个人移动了t步，同时的位置分别是(x1, -tx1+1),(x2, -tx2+1)捡到的最多的樱桃数
//
// 状态转移函数：
// 1. c[t][x1][x2] = -1 if grid[x1][t-x1+1] == -1 || grid[x2][t-x2+1] == -1
// 任何一个人所在的位置是无法通过的，那么这个状态下的樱桃数就是不可能存在的，用-1标记
//
// 2. c[t][x1][x2] = grid[x1][t-x1+1] + (x1 == x2 ? 0 : grid[x2][t-x2+1]) +
// max(c[t-1][x1][x2],c[t-1][x1-1][x2],c[t-1][x1][x2-1],c[t-1][x1-1][x2-1])
// grid[x1][t-x1+1] 表示第一个人所在的位置樱桃的数量
// x1 == x2 判断的目的是避免重复计算，因为这个时候两个人站在同一个位置上面
// c[t-1][x1][x2] 两个人都往下走
// c[t-1][x1-1][x2] 第一个人往右走，第二个人往下走
// c[t-1][x1][x2-1] 第一个人往下走，第二个人往右走
// c[t-1][x1-1][x2-1] 两个人都往右走


int cherryPickup(int** grid, int gridRowSize, int gridColSize) {
  int c[2][51][51], cc, n, p, mi, mj, m, i, j;
  int t = 1, l = gridRowSize + gridColSize, xi, yi, xj, yj;
  for (i = 0; i <= gridRowSize; i++) {
    for (j = 0; j <= gridColSize; j++) {
      c[0][i][j] = -1;
      c[1][i][j] = -1;
    }
  }

  c[(t-1)&1][1][1] = grid[0][0] == -1 ? -1: 0; // for simplify the logic
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

  for (; t < l; t++) {
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
  int d[][10] = {
    { 1,-1, 1,-1, 1,1, 1, 1,1,-1},
    {-1, 1, 1,-1,-1,1, 1, 1,1, 1},
    { 1, 1, 1,-1, 1,1, 1, 1,1, 1},
    { 1, 1, 1, 1, 1,1, 1, 1,1, 1},
    {-1, 1, 1, 1, 1,1, 1, 1,1, 1},
    { 1,-1, 1, 1, 1,1,-1, 1,1, 1},
    { 1, 1, 1,-1, 1,1,-1, 1,1, 1},
    { 1,-1, 1,-1,-1,1, 1, 1,1, 1},
    { 1, 1,-1,-1, 1,1, 1,-1,1,-1},
    { 1, 1,-1, 1, 1,1, 1, 1,1, 1}};

  /*int d[][3] = {*/
    /*{ 1, 1, -1},*/
    /*{ 1,-1, 1},*/
    /*{-1, 1, 1},*/
  /*};*/
 
  /*int d[][3] = {*/
    /*{0, 1, -1},*/
    /*{1, 0, -1},*/
    /*{1, 1,  1},*/
  /*};*/
  int r = sizeof(d) / sizeof(d[0]), c = sizeof(d[0])/sizeof(int);
  int** m = malloc(sizeof(*m) * (size_t)r);
  for (int i = 0; i < r; i++) {
    m[i] = d[i];
  }
  printf("%d %d %d\n", r, c, cherryPickup(m, r, c));
}
