#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define debug(...) fprintf(stderr, __VA_ARGS__)

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 3;

int getInt() {
  static int a, b;
  scanf("%d.%d", &a, &b);
  return a * 100 + b;
}

int main(int argc, char *argv[]) {
  int a[4], b;
  for (int i = 0; i < 4; ++i) a[i] = getInt();
  b = getInt();
  sort(a, a + 4);
  if ((a[0] + a[1] + a[2]) > 3 * b) {
    puts("impossible");
  } else if ((a[3] + a[1] + a[2]) <= 3 * b) {
    puts("infinite");
  } else {
    int ans = 3 * b - a[1] - a[2];
    printf("%d.%02d\n", ans / 100, ans % 100);
  }
  return 0;
}
