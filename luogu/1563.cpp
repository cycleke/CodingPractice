#include <cstdio>

char job[100000][11];
int direction[100000];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%d%s", direction + i, job[i]);
  }
  int now = 0;
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (x ^ direction[now]) {
      now = (now +  y) % n;
    } else {
      now = (now + n - y) % n;
    }
  }
  printf("%s\n", job[now]);
  return 0;
}
