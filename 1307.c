#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int len[5], maxLen;
bool digitUsed[10];
int forbid[26];
int rLen;
int ans[26];

#define ATOI(a) ((a) - 'A')
#define ANS(c) ans[ATOI(c)]
#define FORBID(c) forbid[ATOI(c)]

void printDigit(char *s, int len) {
  
  for (int i = 0; i < len; i++) {
    if (ANS(s[i]) != -1) {
      printf("%d", ANS(s[i]));
    } else {
      putchar('-');
    }
  }
}

void debug(char** words, int wordsSize, char* result) {
  puts("debug-------");
  for (int i = 0; i < wordsSize; i++) {
    printf("%s+", words[i]);
  }
  puts(result);
  for (int i = 0; i < wordsSize; i++) {
    printDigit(words[i], len[i]);
    putchar('+');
  }
  printDigit(result, rLen);
  puts("\n====");
}

void calcLen(char **words, int wordsSize, char* result) {

  maxLen = -1;
  for (int i = 0; i < wordsSize; i++) {
    int l = strlen(words[i]);
    if (maxLen < l) {
      maxLen = l;
    }

    len[i] = l;
  }
  rLen = strlen(result);
}

void initForbid(char **words, int wordsSize, char* result) {

  memset(forbid, -1, sizeof(forbid));
  for (int i = 0; i < wordsSize; i++) {
    FORBID(words[i][0]) = 0;
  }
  FORBID(result[0]) = 0;
}

// return -1 if impossible
int sumAndCheck(char** words, int wordsSize, char* result, int rIndex, int c) {

  int s = c;
  for (int i = 0; i < wordsSize; i++) {
    int j = len[i] + rIndex;
    if (j < 0) {
      continue;
    }
    s += ANS(words[i][j]);
  }

  int i = rLen + rIndex;
  if (i < 0) {
    return -1;
  }

  int nc = s / 10, r = s % 10;
  char rc = result[i];

  if (ANS(rc) != r) {
    return -1;
  }

  return nc;
}

bool calc(char** words, int wordsSize, char* result, int rIndex, int wordIndex, int c) {

  if (wordIndex == wordsSize + 1) {
    int nc = sumAndCheck(words, wordsSize, result, rIndex, c);
      //debug(words, wordsSize, result);
    if (nc == -1) {
      return false;
    }

    if (rIndex + maxLen == 0) {
      //debug(words, wordsSize, result);
      if (maxLen == rLen) {
        return true;
      }

      if (maxLen + 1 != rLen) {
        return false;
      }

      int a = ANS(result[0]);
      if (a != -1) {
        return a == nc;
      }

      for (int i = 0; i < 10; i++) {
        if (!digitUsed[i]) {
          return true;
        }
      }
      return false;
    }

    return calc(words, wordsSize, result, rIndex-1, 0, nc);
  }


  bool isRet = wordIndex == wordsSize;

  int i = (isRet ? rLen : len[wordIndex]) + rIndex;
  //printf("ri=%d, i=%d, wordIndex=%d, len=%d, maxLen=%d\n", rIndex, i, wordIndex, len[wordIndex], maxLen);
  if (i < 0) {
    return calc(words, wordsSize, result, rIndex, wordIndex+1, c);
  }

  for (int d = i == 0 ? 1 : 0; d < 10; d++) {
    char *str = isRet ? result : words[wordIndex];
    char e = str[i];

    if (FORBID(e) == d) {
      continue;
    }

    if (ANS(e) != -1) {
      return calc(words, wordsSize, result, rIndex, wordIndex+1, c);
    }

    if (digitUsed[d]) {
      continue;
    }

    ANS(e) = d;
    digitUsed[d] = true;
    bool r = calc(words, wordsSize, result, rIndex, wordIndex+1, c);
    if (r) {
      return true;
    }
    ANS(e) = -1;
    digitUsed[d] = false;
  }

  return false;
}

bool isSolvable(char** words, int wordsSize, char* result) {

  calcLen(words, wordsSize, result);
  if (rLen > maxLen + 1 || rLen < maxLen) {
    return false;
  }

  initForbid(words, wordsSize, result);
  memset(ans, -1, sizeof(ans));
  memset(digitUsed, 0, sizeof(digitUsed));

  return calc(words, wordsSize, result, -1, 0, 0);
}

int main() {
  char *words[] = {
    //"DHG","HHD","DEG"
    "THAT","IS","WHY","IT","IS"
    //"LEET","CODE"
    //"THIS","IS","TOO"
    //"SIX","SEVEN","SEVEN"
    //"SEND","MORE"
  };
  int wordsSize = 5;

  char *result =
    //"EHGEEE"

    "TRUE"
    // 0

    //"POINT"
    //"FUNNY"
    //"TWENTY"
    //"MONEY"
    ;

  printf("%d\n", isSolvable(words, wordsSize, result));
}
