#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//
// m[i][j] the result of p[0:i-1], s[0:j-2], i >=1 j >= 2
// m[i][j] = m[i-1][j-1] if p[i-1] == s[j-2] or p[i-1] = '.'
// else if p[i-1] = '*'
//   m[i][j] = m[i-2][j-2] if p[i-1] == s[j-2] or p[i-1] = '.', eat the '.*' or 'x*' and match s[j]
//   m[i][j] = m[i][j-2] if p[i-1] == s[j-2] or p[i-1] = '.', eat '.*' and match s[j-2]
//   m[i][j] = m[i-2][j] if p[i-1] != s[j-2]

void print(bool **m, size_t r, size_t c) {
  for (size_t i = 0; i < r; i++) {
    for (size_t j = 0; j < c; j++) {
      printf("%d ", m[i][j]);
    }
    putchar('\n');
  }
  puts("----------");
}

bool isMatch(char* s, char* p) {
  size_t lp = strlen(p), ls = strlen(s), i, j;
  char cs, cp;
  bool **m = calloc(lp + 1, sizeof *m);
  for (i = 0; i <= lp; i++) {
    m[i] = calloc(ls + 2, sizeof **m);
  }

  m[0][1] = true;
  for (i = 1; i <= lp; i++) {
    cp = p[i-1];
    for (j = 1; j <= ls + 1; j++) {
      cs = s[j-2]; 
      if (cp == cs || cp == '.') {
        m[i][j] = m[i-1][j-1];
      }

      if (m[i][j]) continue;

      if (cp != '*') {
        continue;
      }

      if (p[i-2] == cs || p[i-2] == '.') {
        m[i][j] = m[i-2][j-1] || m[i][j-1];
      }

      if (!m[i][j]) {
        m[i][j] = m[i-2][j];
      }
      //print(m, lp+1, ls+2);
    }
  }

  return m[lp][ls+1];
}

int main(void) {
  char *s = "aa", *p = "a";
  printf("s=%s,p=%s,is=%s\n", s, p, isMatch(s, p) ? "OK" : "NO");
  s = "aa", p = "a*";
  printf("s=%s,p=%s,is=%s\n", s, p, isMatch(s, p) ? "OK" : "NO");
  s = "ab", p = ".*";
  printf("s=%s,p=%s,is=%s\n", s, p, isMatch(s, p) ? "OK" : "NO");
  s = "aab", p = "c*a*b";
  printf("s=%s,p=%s,is=%s\n", s, p, isMatch(s, p) ? "OK" : "NO");
  s = "mississippi", p = "mis*is*p*.";
  printf("s=%s,p=%s,is=%s\n", s, p, isMatch(s, p) ? "OK" : "NO");
}
