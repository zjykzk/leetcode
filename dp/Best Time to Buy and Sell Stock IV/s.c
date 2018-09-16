#include <stdio.h>
#include <stdlib.h>

// p[i][j] 表示第i个交易，第j天获取的最大利润
// 这天有三个选项：
// 1. 不做任何事情，那么就是p[i][j] = p[i][j-1]
// 2. 卖进，那么p[i][j] = p[i][j-1]
// 3. 买出，那么p[i][j] = max(p[i-1][t-1]+price[j]-price[t])，t : 1 -> j-1
//    这里可以优化，max(p[i-1][t-1]+price[j]-price[t]) = price[j] + max(p[i-1][t-1]-price[t])
//    在循环计算p[i][j]的时候，可以把这个也累计计算出来

int maxProfit(int k, int* prices, int pricesSize) {
  int *p = calloc((size_t)(pricesSize+1), sizeof *p);
  int i, j, tempMax, cp, ans;
  if (k > pricesSize/2) {
    k = pricesSize/2;
  }

#define MAX(a, b) (a)>(b)?(a):(b)

  for (i = 1; i <= k; i++) {
    tempMax = -prices[0];
    for (j = 1; j < pricesSize; j++) {
      cp = p[j]; 
      p[j] = MAX(p[j-1], prices[j]+tempMax);
      tempMax = MAX(cp-prices[j], tempMax);
    }
  }


  ans = p[pricesSize-1];
  free(p);
  return ans;
}

void test(int k, int *prices, int pricesSize) {
  printf("k=%d,prices:[", k);
  for (int i = 0; i < pricesSize; i++) {
    printf("%d,", prices[i]);
  }
  putchar(']');
  printf(", ans:%d\n", maxProfit(k, prices, pricesSize));
}

int main(void) {
  /*int prices[] = {2,4,1};*/
  /*test(2, prices, 3);*/
  /*int prices[] ={3,2,6,5,0,3};*/
  /*test(2, prices, 6);*/
  int prices[] ={1,2};
  test(1, prices, 2);
}
