// by OwenCreeper
#include "bits/stdc++.h"
#define N 1000000
#define MOD 1000000007
using namespace std;
typedef long long ll;
inline int read() {
  int num = 0, k = 1;
  char ch = getchar();
  while (ch > '9' || ch < '0') k = ch == '-' ? -1 : 1, ch = getchar();
  while (ch >= '0' && ch <= '9') num *= 10, num += ch - 48, ch = getchar();
  return num * k;
}
void solve(int n) {
  double now, a;
  scanf("%lf", &a);
  for (int i = 1; i <= n; i++) {
    if (i == 1)
      now = 1 / (1 / (1 / (1 / a + 1 / (3 * a)) + 3 * a) + 1 / (3 * a));
    else
      now =
          1 / (1 / (1 / (1 / now + 1 / a + 1 / (3 * a)) + 3 * a) + 1 / (3 * a));
  }
  printf("%.7f\n", now);
}
char s[N + 5];
void work() {
  scanf("%s", s);
  int n;
  if (strlen(s) <= 3) {
    sscanf(s, "%d", &n);
    solve(n);
  } else
    solve(100);
}
int main(int argc, char const *argv[]) {
  int T;
  scanf("%d", &T);
  while (T--) work();
  return 0;
}
