/*
 * 给出一个无重叠的 ，按照区间起始端点排序的区间列表。
 *
 * 在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。
 *
 * 示例 1:
 *
 * 输入: intervals = [[1,3],[6,9]], newInterval = [2,5]
 * 输出: [[1,5],[6,9]]
 * 示例 2:
 *
 * 输入: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 * 输出: [[1,2],[3,10],[12,16]]
 * 解释: 这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。
 *
 * /

#include <stdio.h>
#include <stdlib.h>

#define S(in) (in[0])
#define E(in) (in[1])

int bs(int** intervals, int sz, int v) {

  int s = -1, e = sz, m;
  
  while (s + 1 < e) {

    m = s + (e - s) / 2;
    int v1 = S(intervals[m]), v2 = E(intervals[m]);

    if (v1 > v) {
      e = m;
      continue;
    }

    if (v2 < v) {
      s = m;
      continue;
    }

    return m;
  }

  return s;
}

int** insert(
    int** intervals, int intervalsSize, int* intervalsColSize,
    int* newInterval, int newIntervalSize,
    int* returnSize, int** returnColumnSizes
    ) {

  int s = bs(intervals, intervalsSize, S(newInterval));
  int e = bs(intervals, intervalsSize, E(newInterval));

#define IN_INTERVAL(v, i) (i >= 0 && (intervals[i][0]<=v && intervals[i][1]>=v))
  int sIn = IN_INTERVAL(newInterval[0], s);
  int eIn = IN_INTERVAL(newInterval[1], e);

#define MAX(a, b) (a > b ? a : b)

  int siz = intervalsSize - (e - s); // interval - (e - s + 1) + 1
  if (!sIn) {
    siz++;
  }
  /*printf("s=%d,e=%d,size=%d\n", s, e, siz);*/

  int** ret = malloc(sizeof(int*) * siz);
  *returnColumnSizes = malloc(sizeof(int) * siz);

  int i = 0;
  for (; i < s; i++) {
    //printf("i=%d\n", i);
    ret[i] = malloc(sizeof(int) * 2);
    (*returnColumnSizes)[i] = 2;
    ret[i][0] = S(intervals[i]);
    ret[i][1] = E(intervals[i]);
  }

  ret[i] = malloc(sizeof(int) * 2);
  if (sIn && eIn) {
    ret[i][0] = S(intervals[s]);
    ret[i][1] = E(intervals[e]);
    (*returnColumnSizes)[i] = 2;
  } else if (sIn && !eIn) {
    ret[i][0] = S(intervals[s]);
    ret[i][1] = E(newInterval);
    (*returnColumnSizes)[i] = 2;
  } else if (!sIn) {
    if (s >= 0 && s < intervalsSize) {
      ret[i][0] = S(intervals[s]);
      ret[i][1] = E(intervals[s]);
      (*returnColumnSizes)[i] = 2;
      i++;
    }

    ret[i] = malloc(sizeof(int) * 2);
    if (eIn) {
      ret[i][0] = S(newInterval);
      ret[i][1] = E(intervals[e]);
    } else {
      ret[i][0] = S(newInterval);
      ret[i][1] = E(newInterval);
    }
    (*returnColumnSizes)[i] = 2;
  }
  i++;

  for (int j = e + 1; j < intervalsSize; i++, j++) {
    //printf("i=%d\n", i);

    ret[i] = malloc(sizeof(int) * 2);
    ret[i][0] = S(intervals[j]);
    ret[i][1] = E(intervals[j]);
    (*returnColumnSizes)[i] = 2;
  }

  *returnSize = siz;

  return ret;
}

void debugResult(int** intervals, int size) {

  printf("[");
  for (int i = 0; i < size; i++) {

    if (i > 0) {
      printf(",");
    }
    printf("[%d,%d]", intervals[i][0], intervals[i][1]);
  }
  printf("]\n");
}

void debugInput(int** intervals, int intervalsSize, int* newInterval, int newIntervalSize) {

  printf("input:");
  debugResult(intervals, intervalsSize);
  printf("new interval:[%d,%d]\n", S(newInterval), E(newInterval));
}

void debugColumnSizes(int* columnSize, int size) {
  printf("column size:[");
  for (int i = 0; i < size; i++) {
    if (i > 0) {
      printf(",");
    }
    printf("%d", columnSize[i]);
  }
  printf("]\n");
}

int main() {

  int returnSize;
  int* returnColumnSizes;
  int** ret;

#define RUN debugInput(a, intervalsSize, newInterval, 2); \
    ret = insert(a, intervalsSize, columnSize, newInterval, 2, &returnSize, &returnColumnSizes); \
    debugResult(ret, returnSize); \
    debugColumnSizes(returnColumnSizes, returnSize);

  {
    int e0[] = {1, 3};
    int e1[] = {6, 9};
    int columnSize[] = {2, 2};
    int* a[] = {e0, e1};
    int intervalsSize = 2;
    int newInterval[] = {2, 5};
    RUN
  }

  {
    int e0[] = {1,2};
    int e1[] = {3,5};
    int e2[] = {6,7};
    int e3[] = {8,10};
    int e4[] = {12,16};
    int columnSize[] = {2, 2, 2, 2, 2};
    int* a[] = {e0, e1, e2, e3, e4};
    int intervalsSize = 5;
    int newInterval[] = {4,8};
    RUN
  }

  {
    int e0[] = {1, 3};
    int e1[] = {6, 9};
    int columnSize[] = {2, 2};
    int* a[] = {e0, e1};
    int intervalsSize = 2;
    int newInterval[] = {2, 5};
    RUN
  }

  {
    int columnSize[] = {};
    int* a[] = {};
    int intervalsSize = 0;
    int newInterval[] = {2, 5};

    RUN
  }

  {
    int columnSize[] = {2};
    int e0[] = {1, 5};
    int* a[] = {e0};
    int intervalsSize = 1;
    int newInterval[] = {2, 3};

    RUN
  }

  {
    int columnSize[] = {2};
    int e0[] = {1, 5};
    int* a[] = {e0};
    int intervalsSize = 1;
    int newInterval[] = {6, 8};

    RUN
  }

  {
    int columnSize[] = {2};
    int e0[] = {1, 5};
    int* a[] = {e0};
    int intervalsSize = 1;
    int newInterval[] = {0, 3};

    RUN
  }

  {
    int columnSize[] = {2};
    int e0[] = {1, 5};
    int* a[] = {e0};
    int intervalsSize = 1;
    int newInterval[] = {2, 13};

    RUN
  }

  {
    int columnSize[] = {2};
    int e0[] = {0, 5};
    int e1[] = {9, 12};
    int* a[] = {e0, e1};
    int intervalsSize = 2;
    int newInterval[] = {7,16};

    RUN
  }

  {
    int columnSize[] = {2};
    int e0[] = {2,7};
    int e1[] = {8,8};
    int e2[] = {10,10};
    int e3[] = {12,13};
    int e4[] = {16,19};
    int* a[] = {e0, e1, e2, e3, e4};
    int intervalsSize = 5;
    int newInterval[] = {9, 17};

    RUN
  }
}
