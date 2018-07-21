#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// https://leetcode.com/problems/wildcard-matching/
// 

bool isMatch(char* s, char* p) {
  size_t sl = strlen(s), pl = strlen(p);
  bool **m = malloc((pl + 1) * sizeof (*m));
  for (size_t i = 0; i <= pl; i++) {
    m[i] = malloc((sl + 1) * sizeof (**m));
  }

  memset(m[0], false, sl);
  m[0][0] = true;

  for (size_t i = 1; i <= pl; i++) {
    for (size_t j = 0; j <= sl; j++) {
      bool ja = j > 0;
      if ((ja && p[i - 1] == s[j - 1]) || p[i - 1] == '?') {
        m[i][j] = m[i - 1][j - 1];
        continue;
      }

      if (p[i - 1] == '*') {
        m[i][j] = m[i - 1][j] || (ja ? m[i][j - 1] || m[i - 1][j - 1]: false);
        continue;
      }

      m[i][j] = false;
    }
  }

  return m[pl][sl];
}

int main(void) {
  char *s = "aa", *l = "a";
  printf("%s, %s:%s\n", s, l, isMatch(s, l) ? "true" : "false");
  s = "aa", l = "*";
  printf("%s, %s:%s\n", s, l, isMatch(s, l) ? "true" : "false");
  s = "cb", l = "?a";
  printf("%s, %s:%s\n", s, l, isMatch(s, l) ? "true" : "false");
  s = "adceb", l = "*a*b";
  printf("%s, %s:%s\n", s, l, isMatch(s, l) ? "true" : "false");
  s = "acdcb", l = "a*c?b";
  printf("%s, %s:%s\n", s, l, isMatch(s, l) ? "true" : "false");
  s = "aabbaabaaaabaabbbb", l = "b**bb*";
  printf("%s, %s:%s\n", s, l, isMatch(s, l) ? "true" : "false");
}
