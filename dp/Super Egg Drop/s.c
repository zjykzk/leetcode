#include <stdio.h>

int f(int m, int K, int N) {
  int i, ret = 0, c = 1;
  for (i = 1; i <= K; ++i) {
    c *= m - i + 1;
    c /= i;
    ret += c;
    if (ret >= N) break;
  }

  return ret;
}

int superEggDrop(int K, int N) {
  int b = 1, e = N, m;

  while (b < e) {
      m = (b+e)>>1;
      if (f(m, K, N) < N) {
        b = m + 1;
      } else {
        e = m;
      }
  }

  return b;
}

int main(void) {
  int K, N;
  K = 1, N = 2;
  printf("K=%d, N=%d, c=%d\n", K, N, superEggDrop(K, N));
  K = 2, N = 2;
  printf("K=%d, N=%d, c=%d\n", K, N, superEggDrop(K, N));
  K = 2, N = 6;
  printf("K=%d, N=%d, c=%d\n", K, N, superEggDrop(K, N));
  K = 2, N = 7;
  printf("K=%d, N=%d, c=%d\n", K, N, superEggDrop(K, N));
  K = 2, N = 9;
  printf("K=%d, N=%d, c=%d\n", K, N, superEggDrop(K, N));
  K = 3, N = 7;
  printf("K=%d, N=%d, c=%d\n", K, N, superEggDrop(K, N));
  K = 3, N = 14;
  printf("K=%d, N=%d, c=%d\n", K, N, superEggDrop(K, N));
}
