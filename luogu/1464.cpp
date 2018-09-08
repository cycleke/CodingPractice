#include <cstdio>
#include <cstring>

int f[21][21][21];

int W(int a, int b, int c) {
  if (a <= 0 || b <= 0 || c <= 0)
    return 1;
  if (~f[a][b][c]) return f[a][b][c];
  if (a < b && b < c)
    return f[a][b][c] = W(a, b, c-1) + W(a, b-1, c-1) - W(a, b-1, c);
  return f[a][b][c] = W(a-1, b, c) + W(a-1, b-1, c) + W(a-1, b, c-1) - W(a-1, b-1, c-1);
}

int main() {
  long long a, b, c;
  memset(f, -1, sizeof(f));
  while (scanf("%lld%lld%lld", &a, &b, &c) != EOF) {
    if (a == -1 && b == -1 && c == -1) break;
    printf("w(%lld, %lld, %lld) = ", a, b, c);
    if (a <= 0 || b <= 0 || c <= 0) {
      puts("1");
    } else if (a > 20 || b > 20 || c > 20) {
      printf("%d\n", W(20, 20, 20));
    } else {
      printf("%d\n", W(a, b, c));
    }
  }
  return 0;
}
