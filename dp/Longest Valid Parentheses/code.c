#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.com/problems/longest-valid-parentheses/description/

int longestValidParentheses(char* s) {
  size_t l = strlen(s);
  size_t *counts = calloc(l, sizeof *counts);
  char *stack = malloc(sizeof(*stack) * l), c;
  int top = -1;

  for (size_t i = 0; i < l; i++) {
    c = s[i];
    if (top == -1 || c == '(') {
      stack[++top] = c;
      counts[i] = counts[i - 1];
      continue;
    }

    char tc = stack[top];
    if (tc == '(' && c ==')') {
      //putchar('#');
      if (i > 1 && s[i-2] == ')') {
        //putchar('$');
        counts[i] = counts[i-2] + 2;
      } else if (s[i-1] == ')') {
        //putchar('!');
        counts[i] = counts[i-1] + 2;
        //printf("%d\n", (int)counts[i]);
      } else {
        //putchar('*');
        counts[i] = 2;
        //printf("%d\n", (int)counts[i]);
      }
      --top;
      continue;
    }

    if (c == ')') {
      counts[i] = counts[i - 1];
      //printf("%d:%d\n", (int)i, (int)counts[i]);
    }
  }

  free(stack);
  free(counts);
  return (int)counts[l-1];
}

int main(void) {
  printf("%d\n", longestValidParentheses(")()()"));
  printf("%d\n", longestValidParentheses(")(()()())"));
  printf("%d\n", longestValidParentheses("(()"));
  printf("%d\n", longestValidParentheses("(()))"));
  printf("%d\n", longestValidParentheses(")()"));
  printf("%d\n", longestValidParentheses("()(()"));
  printf("%d\n", longestValidParentheses("()(()((())"));
}
