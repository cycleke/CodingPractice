#include <cstdio>

inline int max(int a, int b) {
  return a < b ? b : a;
}

int main() {
  int n;
  scanf("%d", &n);
  int li, ri, l1, l2, r1, r2;
  li = ri = 0;
  l1 = l2 = -1;
  r1 = r2 = 1e9 + 1;
  for (int i = 0; i < n; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    if (a > l1) {
      li = i;
      l2 = l1;
      l1 = a;
    } else if (a > l2) {
      l2 = a;
    }
    if (b < r1) {
      ri = i;
      r2 = r1;
      r1 = b;
    } else if (b < r2) {
      r2 = b;
    }
  }
  if (li == ri) {
    printf("%d\n", max(0, r2 - l2));
  } else {
    printf("%d\n", max(0, max(r2 - l1, r1 - l2)));
  }
  return 0;
}
