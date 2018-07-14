#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.com/problems/longest-valid-parentheses/description/

// max[i] the Longest Valid Parentheses length ending with s[i - 1]
//
// case 1: max[i] = 2 + max[i - 1] if s[i] = '(' and s[i-1] = ')'
// case 2: max[i] = 0, s[i] = ')' and s[i-1] = ')' and max[i-1] = 0
// case 3:
// let j = i - max[i] - 1
// max[i] = 2 + max[i] if j < 0
// max[i] = 2 + max[i] + max[j] if j >= 0
// case 4: max[i] = 0 if s[i-1] = '('
int byDP(char* s) {
  size_t l = strlen(s);
  int *max = malloc((l + 1) * sizeof(*max)), ret = 0;
  char c, p;

  max[0] = 0; max[1] = 0;
  for (size_t i = 1; i < l; i++) {
    c = s[i], p = s[i - 1];
    if (p == '(' && c == ')') {
      max[i + 1] = 2 + max[i - 1];
      continue;
    }

    if (p == ')' && c == ')') {
      if (max[i] == 0) {
        max[i + 1] = 0;
        continue;
      }

      if ((int)i > max[i] && s[(int)i - max[i] - 1] == '(') {
        max[i + 1] = 2 + max[i];
        if ((int)i > max[i] + 1) {
          max[i + 1] += max[(int)i - max[i] - 1];
        }
        continue;
      }
    }

    max[i + 1] = 0;
  }


  for (size_t i = 1; i <= l; i++) {
    if (ret < max[i]) {
      ret = max[i];
    }
  }

  free(max);
  return ret;
}

int byStack(char* s) {
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

int longestValidParentheses(char* s) {
  //return byDP(s);
  return byStack(s);
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
