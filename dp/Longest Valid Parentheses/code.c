#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.com/problems/longest-valid-parentheses/description/

int longestValidParentheses(char* s) {
  size_t l = strlen(s);
  int *stack = malloc((l + 2) * sizeof(*stack));
  int top = 0, curMax, max = 0;
  char c;

  stack[0] = -1;

  for (size_t i = 0; i < l; i++) {
    c = s[i];
    if (c == '(') {
      stack[++top] = (int)i;
      continue;
    }

    char tc = s[stack[top]];
    if (tc == '(') {
      --top;
      continue;
    }

    stack[++top] = (int)i;
  }

  stack[++top] = (int)l;

  for (int i = 0; i < top; ++i) {
    curMax = stack[i+1] - stack[i] - 1;
    if (max < curMax) {
      max = curMax;
    }
  }

  free(stack);
  return max;
}

int main(void) {
  printf("%d\n", longestValidParentheses(")(((((()())()()))()(()))("));
  printf("%d\n", longestValidParentheses("(()))))"));
  printf("%d\n", longestValidParentheses(")()()"));
  printf("%d\n", longestValidParentheses(")(()()())"));
  printf("%d\n", longestValidParentheses("(()"));
  printf("%d\n", longestValidParentheses("(()))"));
  printf("%d\n", longestValidParentheses(")()"));
  printf("%d\n", longestValidParentheses("()(()"));
  printf("%d\n", longestValidParentheses("()(()((())"));
}
