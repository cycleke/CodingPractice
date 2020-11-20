#include <cstdio>

long long a, b;

bool Check(long long x, long long y) {
  for (long long i = x; i > 0; i--) {
    if (a % i == 0 && a / i <= y) return true;
    if (b % i == 0 && b / i <= y) return true;
  }
  return false;
}

int main() {
  scanf("%lld%lld", &a, &b);
  long long sum = a + b, ans = 1ll << 63;
  for (long long i = 1; i * i <= sum; i++) {
    if (sum % i) continue;
    long long x = i, y = sum / i;
    if (Check(x, y)) {
        ans = (x + y) * 2;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
