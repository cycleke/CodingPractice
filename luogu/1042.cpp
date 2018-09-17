#include <cstdio>

bool win[62500];

int iabs(int a) {
  return a < 0 ? -a : a;
}

void Ract(int n, int base) {
  int a = 0, b = 0;
  for (int i = 0; i < n; i++) {
    if (win[i]) a++;
    else b++;
    if ((a >= base || b >= base) && iabs(a - b) >= 2) {
      printf("%d:%d\n", a, b);
      a = b = 0;
    }
  }
  printf("%d:%d\n", a, b);
}

int main() {
  int n = 0;
  for (char ch = getchar(); ch != 'E'; ch = getchar()) {
    if (ch == 'W') win[n++] = true;
    else if (ch == 'L') win[n++] = false;
  }
  Ract(n, 11);
  puts("");
  Ract(n, 21);
  return 0;
}
