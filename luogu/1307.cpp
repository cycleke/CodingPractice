#include <cstdio>
#include <cstring>

void Reverse(char *s) {
  int it = strlen(s) - 1;
  while ((~it) && s[it] == '0') it--;
  if (it == -1)
    puts("0");
  else {
    while (~it) putchar(s[it--]);
    putchar('\n');
  }
}

int main() {
  char num[12];
  scanf("%s", num);
  if (*num == '-') {
    putchar('-');
    Reverse(num + 1);
  } else {
    Reverse(num);
  }
  return 0;
}
