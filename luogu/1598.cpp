#include <cstdio>
#include <cstring>

int main() {
  int count[26];
  char buffer[405];
  int n = fread(buffer, 1, 405, stdin);
  memset(count, 0, sizeof(count));
  for (int i = 0; i < n; i++) {
    const char& ch = buffer[i];
    if (ch < 'A' || ch > 'Z') continue;
    count[ch - 'A']++;
  }
  int height = 0;
  for (int i = 0; i < 26; i++) {
    if (count[i] > height) {
      height = count[i];
    }
  }
  for (int i = height; i > 0; i--) {
    for (int alpha = 0; alpha < 26; alpha++) {
      if (count[alpha] >= i) {
        putchar('*');
      } else {
        putchar(' ');
      }
      putchar(' ');
    }
    puts("");
  }
  for (char alpha = 'A'; alpha <= 'Z'; alpha++) {
    putchar(alpha);
    putchar(' ');
  }
  return 0;
}
