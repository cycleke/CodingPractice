#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
const int MAXN = 2e3 + 5;

int n, q, ans[MAXN];
pii a[MAXN], b[MAXN];

pii gen(int x, int y) {
  int g = __gcd(x, y);
  x /= g, y /= g;
  if (x < 0) x = -x, y = -y;
  else if (x == 0 && y < 0) y = -y;
  return make_pair(x, y);
}

void solve() {
  static map<pii, int> cnt;
  for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
  for (int i = 0; i < q; ++i) cin >> b[i].first >> b[i].second;
  for (int i = 0; i < q; ++i) {
    cnt.clear();
    for (int j = 0; j < n; ++j) {
      int dx = a[j].first - b[i].first, dy = a[j].second - b[i].second;
      ++cnt[gen(dx, dy)];
      auto it = cnt.find(gen(-dy, dx));
      if (it != cnt.end()) ans[i] += it->second;
    }
  }

  for (int i = 0; i < n; ++i) {
    cnt.clear();
    for (int j = 0; j < n; ++j) {
      if (j == i) continue;
      int dx = a[j].first - a[i].first, dy = a[j].second - a[i].second;
      ++cnt[gen(dx, dy)];
    }
    for (int j = 0; j < q; ++j) {
      int dx = b[j].first - a[i].first, dy = b[j].second - a[i].second;
      auto it = cnt.find(gen(-dy, dx));
      if (it != cnt.end()) ans[j] += it->second;
    }
  }

  for (int i = 0; i < q; ++i) cout << ans[i] << '\n', ans[i] = 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while (cin >> n >> q) solve();
  return 0;
}
