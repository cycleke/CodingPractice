#include <bits/stdc++.h>
using namespace std;

long long fpow(long long a, long long b) {
  long long res = 1;
  for (; b; b >>= 1, a *= a)
    if (b & 1) res *= a;
  return res;
}

long long gao(long long n, long long f) { return n / f; }

void solve() {
  long long n, k;
  cin >> n >> k;
  if (k == 1 || k >= 30) {
    cout << n << "\n";
    return;
  }
  long long ans = 0;
  for (long long i = 1, pre = 1, nxt; pre <= n; ++i, pre = nxt) {
    nxt = fpow(i + 1, k);
    ans += gao(min(nxt - 1, n), i) - gao(pre - 1, i);
    // cerr << pre << " " << min(nxt - 1, n) << " "
    //      << gao(min(nxt - 1, n), i) - gao(pre - 1, i) << "\n";
  }
  cout << ans << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int T;
  cin >> T;
  for (int step = 1; step <= T; ++step) {
    cout << "Case #" << step << ": ";
    solve();
  }

  return 0;
}
