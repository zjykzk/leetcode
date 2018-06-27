#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// f(i, j) = f(i, j-1) + (s[j-1] == t[i-1] ? f(i-1,j-1) : 0)
//
int numDistinct(char* s, char* t) {
  size_t sl = strlen(s), tl = strlen(t), i, j;
  int** c = calloc(tl+1, sizeof(int *));
  for (i = 0; i <= tl; i++) {
    c[i] = calloc(sl+1, sizeof(int *));
  }
  
  for (i = 0; i <= sl; i++) {
    c[0][i] = 1;
  }
  
  for (i = 1; i <= tl; i++) {
    for (j = i; j <= sl; j++) {
      if (t[i-1] == s[j-1]) {
          c[i][j] = c[i-1][j-1];
      }
      
      c[i][j] += c[i][j-1];
    }
  }
  
  return c[tl][sl];
}

int main(void) {
    char *s = "babgbag", *t = "bag";
    printf("%d\n", numDistinct(s, t));
}
