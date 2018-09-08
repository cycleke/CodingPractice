#include <cstdio>
#include <cstring>

int main() {
  char s[50];
  scanf("%s", s);
  int n = strlen(s);
  char op = -1;
  int length = 0;
  for (int i = 0; i <n; i++) {
    if (s[i] >= '0' && s[i] <= '9') {
      length++;
    } else {
      op = s[i];
      break;
    }
  }
  int pos = length;
  length--;
  while (s[length] == '0' && length) {
    length--;
  }
  while (~length) {
    putchar(s[length--]);
  }
  if (op == '%') {
    puts("%");
  } else if (~op) {
    pos++;
    putchar(op);
    while (s[pos] == '0' && pos < n - 1) {
      pos++;
    }
    int m = n - 1;
    while (s[m] == '0' && m > pos) {
      m--;
    }
    for (int i = m; i >= pos; i--) {
      putchar(s[i]);
    }
  }
  return 0;
}
