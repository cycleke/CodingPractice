#include <cstdio>

char key[256];
bool mark[256];

int main() {
  char a[103], b[103];
  scanf("%s%s", a, b);
  int count = 0;
  for (int i = 0; a[i]; i++) {
    if (!key[a[i]]) {
      if (mark[b[i]]) {
        puts("Failed");
        return 0; 
      }
      count++;
      key[a[i]] = b[i];
      mark[b[i]] = true;
    } else {
      if (key[a[i]] == b[i]) continue;
      puts("Failed");
      return 0;
    }
  }
  if (count < 26) {
    puts("Failed");
    return 0;
  }
  char ch = getchar_unlocked();
  while (ch < 'A' || ch > 'Z') {
    ch = getchar_unlocked();
  }
  putchar_unlocked(key[ch]);
  for (ch = getchar_unlocked(); ch >= 'A' && ch <= 'Z'; ch = getchar_unlocked()) {
    putchar_unlocked(key[ch]);
  }
  return 0;
}
