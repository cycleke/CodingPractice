#include <cstdio>

bool mark[1001];

int main() {
  int n;
  scanf("%d", &n);
  int count = 0;
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    if (!mark[x]) {
      mark[x] = true;
      count++;
    }
  }
  printf("%d\n", count);
  for (int i = 1; i < 1001; i++) {
    if (mark[i]) {
      printf("%d ", i);
    }
  }
  return 0;
}
