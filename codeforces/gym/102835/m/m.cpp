#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define debug(...) fprintf(stderr, __VA_ARGS__)

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 3;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
  int n, m, ns = 0, ms = 0;
  cin >> n >> m;
  for (int i = 0, x; i < n; ++i) {
    cin >> x;
    ns |= 1 << x;
  }
  for (int i = 0, x; i < m; ++i) {
    cin >> x;
    ms |= 1 << x;
  }

  int cnt = 0;
  for (int s = 0; s < 16; ++s) {
    int ns_ = 0, ms_ = 0;
    for (int i = 0; i < 4; ++i)
      if (s >> i & 1) {
        ns_ |= 1 << (i / 2);
        ms_ |= 1 << (i % 2);
      }
    cnt += ns_ == ns && ms_ == ms;
  }
  cout << cnt << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
