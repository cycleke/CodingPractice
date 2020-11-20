#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 5;

int n, m, a[MAXN], b[MAXN], mx[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];

  int solve = 0;
  ll sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += a[i];
    if (sum <= m)
      ++solve;
    else
      break;
  }

  if (solve == 0) {
    cout << "-1\n";
    return 0;
  }

  mx[solve - 1] = b[solve - 1];
  for (int i = solve - 2; ~i; --i) mx[i] = max(mx[i + 1], b[i]);

  ll sa = 0, sb = 0;
  int ball = 0, ga = 0, gb = 0;
  vector<ll> ans;
  for (int i = 0; i < n; ++i) {
    while (true) {
      sb += b[i];
      if (sb > m) break;
      while (ga < solve && sa + a[ga] <= sb) {
        sa += a[ga];
        ++ga, ++ball;
      }
      if (ball && mx[i] == b[i]) {
        ans.push_back(sb);
        --ball;
        continue;
      }
      break;
    }
    if (sb > m) break;
    gb = i + 1;
  }

  if (solve > gb) {
    cout << ans.size() << '\n';
    for (ll x : ans) cout << x << ' ';
    cout << '\n';
  } else {
    cout << "-1\n";
  }

  return 0;
}
