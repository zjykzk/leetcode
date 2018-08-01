#include <stdio.h>
#include <stdbool.h>
#include <string.h>


int numDecodings(char* s) {
  int p[2], m;
  size_t l = strlen(s);
  char c;

  p[0] = *s == '*' ? 9 : 1; p[1] = 1;


#define C 1000000007
#define M(m) ((m) > C ? (m) % C : (m))

  for (size_t i = 1; i < l; i++) {
    m = s[i] == '*' ? p[0] * 9 : p[0];

    c = s[i-1];
    if (s[i] == '*') {
      if (c == '*') {
        m += 15*p[1];
      } else if (c == '1') {
        m += 9*p[1];
      } else if (c == '2') {
        m += 6*p[1];
      }
      goto END;
    }

    if (c == '*') {
      m += p[1] >> (s[i] >= '1' && s[i] <= '6');
      goto END;
    }

    if (c == '1') {
      m += p[1];
      goto END;
    }

    if (c == '2' && s[i] >= '1' && s[i] <= '6') {
      m += p[1];
    }
END:
    m = M(m);
    printf("%d\n", m);

    p[1] = p[0];
    p[0] = m;
  }

  return p[0];
}

int main(void) {
  char *s = "1*";
  printf("%s, %d\n", s, numDecodings(s));
  s = "*";
  printf("%s, %d\n", s, numDecodings(s));
  s = "**";
  printf("%s, %d\n", s, numDecodings(s));
  s = "*1";
  printf("%s, %d\n", s, numDecodings(s));
  s = "*1*1*0";
  printf("%s, %d\n", s, numDecodings(s));
}
