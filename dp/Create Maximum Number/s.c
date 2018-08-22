#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void printa(int *a, int l) {
  for (int i = 0; i < l; i++) {
    printf("%d ", a[i]);
  }
  putchar('\n');
}

int *maxSeq(int *d, int l, int *m, int k) {
  int i, j;
  for (i = 0, j = 0; i < l; i++) {
    while (j > 0 && m[j-1] < d[i] && l - i > k - j) {
      --j;
    }
    if (j < k) m[j++] = d[i];
  }
  printf("max seq %d %d %d\n", i, j, k);
  printa(m, k);
  return m;
}

bool greater(int *m1, int l1, int *m2, int l2) {
  for (int i = 0, j = 0; i < l1 && j < l2; i++, j++) {
    if (m1[i] > m2[j]) {
      return true;
    }
    if (m1[i] < m2[j]) {
      return false;
    }
  }

  return l1 > l2;
}

int *mergeMaxSeq(int *s1, int l1, int *s2, int l2, int *r) {
  int i = 0, j = 0, k = 0;
  while (i < l1 || j < l2) {
    r[k++] = greater(s1+i, l2-i, s2+j, l2-j) ? s1[i++] : s2[j++];
  }
  printf("mergeseq\n");
  printa(r, l1+l2);
  return r;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxNumber(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize) {
  int i, j, *n, *c;

#define max(a, b) ((a)>(b)?(a):(b))
#define min(a, b) ((a)>(b)?(b):(a))

  returnSize = malloc(sizeof *returnSize * (size_t)(k + k + nums1Size + nums2Size));
  memset(returnSize, 0, sizeof *returnSize * (size_t)k);
  n = returnSize;
  for (i = max(0, k-nums1Size), j = 0; i < min(k, nums2Size); i++) {
    n = mergeMaxSeq(
        maxSeq(nums1, nums1Size, returnSize+k+k, i), i,
        maxSeq(nums2, nums2Size, returnSize+k+k+nums1Size, k-i), k-i,
        returnSize + ((j+1)&1));
    if (greater(n, k, c, k)) {
      c = n;
      j++;
    }
  }

  if ((j&1) == 1) {
    memcpy(returnSize, returnSize + k, k);
  }

#undef max
#undef min

  return returnSize;
}

int main(void) {

#define len(a) (sizeof a/sizeof a[0])

  int nums1[] = {3, 4, 6, 5};
  int nums2[] = {9, 1, 2, 5, 8, 3};
  int k = 5, r;

  printa(maxNumber(nums1, len(nums1), nums2, len(nums2), k, &r), k);

#undef len
}

