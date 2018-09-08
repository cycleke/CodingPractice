#include <cstdio>
#include <cstring>

int c[1423] = {6};
const int dig[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int main() {
  int n;
  scanf("%d", &n);
  n -= 4;
  for (int i = 1; i < 1423; i++) {
    int x = i;
    c[i] = 0;
    while (x) {
      c[i] += dig[x % 10];
      x /= 10;
    }
  }
  int ans = 0;
  for (int a = 0; a < 712; a++) {
    if (c[a] + c[a] + c[a + a] == n) {
      ans++;
    }
    for (int b = a + 1; b < 712; b++) {
      if (c[a] + c[b] + c[a + b] != n) continue;
      ans += 2;
    }
  }
  printf("%d\n", ans);
  return 0;
}
