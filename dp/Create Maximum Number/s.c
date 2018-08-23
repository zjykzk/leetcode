#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int *maxSeq(int *d, int l, int *m, int k) {
  int i, j;
  for (i = 0, j = 0; i < l; i++) {
    while (j > 0 && m[j-1] < d[i] && l - i > k - j) {
      --j;
    }
    if (j < k) m[j++] = d[i];
  }
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
    r[k++] = greater(s1+i, l1-i, s2+j, l2-j) ? s1[i++] : s2[j++];
  }
  return r;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxNumber(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize) {
  int i, j, *n, *c, *k1, *k2, *kd;

#define max(a, b) ((a)>(b)?(a):(b))
#define min(a, b) ((a)>(b)?(b):(a))

  kd = malloc(sizeof *kd * (size_t)(k + k + nums1Size + nums2Size));
  memset(kd, 0, sizeof *kd * (size_t)k);
  c = kd; k1 = kd+k+k; k2 = k1+nums1Size;

  for (i = max(0, k-nums2Size), j = 1; i <= min(k, nums1Size); i++) {
    n = mergeMaxSeq(
        maxSeq(nums1, nums1Size, k1, i), i,
        maxSeq(nums2, nums2Size, k2, k-i), k-i,
        kd + (j&1 ? k : 0));
    if (greater(n, k, c, k)) {
      c = n;
      j++;
    }
  }

  if (c == kd + k) {
    memcpy(kd, c, sizeof *c * k);
  }
  *returnSize = k;

#undef max
#undef min

  return kd;
}

void printa(int *a, int l) {
  for (int i = 0; i < l; i++) {
    printf("%d ", a[i]);
  }
  putchar('\n');
}

int main(void) {

#define len(a) (sizeof a/sizeof a[0])

  /*int nums1[] = {3, 4, 6, 5};*/
  /*int nums2[] = {9, 1, 2, 5, 8, 3};*/
  /*int k = 5, r;*/

  /*int nums1[] = {3, 4, 6, 5};*/
  /*int nums2[] = {9, 9, 9, 3, 8, 3};*/
  /*int k = 5, r = k;*/

  /*int nums1[] = {6,7};*/
  /*int nums2[] = {6,0,4};*/
  /*int k = 5, r = k;*/

  int nums1[] = {3,9};
  int nums2[] = {8,9};
  int k = 3, r = k;

  printa(maxNumber(nums1, len(nums1), nums2, len(nums2), k, &r), k);

#undef len
}

