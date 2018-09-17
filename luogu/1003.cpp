#include <cstdio>
#define N 10002
int A[N], B[N], G[N], K[N];
int main() {
  int n, x, y;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d%d", A + i, B + i, G + i, K + i);
  }
  scanf("%d%d",&x,&y);
  int i;
  for (i = n; i; --i)
    if (x>=A[i] && x<=A[i]+1 && y>=B[i] && y<=B[i]+G[i]) break;
  if (i == 0) i = -1;
  printf("%d\n", i);
  return 0;
}
