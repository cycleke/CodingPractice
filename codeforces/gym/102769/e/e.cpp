#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 3;

struct Node {
  int val, id;

  bool operator<(const Node &other) const { return val > other.val; }
} a[MAXN * 2];
int cnt[MAXN];

void solve() {
  int n, p;
  cin >> n >> p;
  int max_b = -1;
  for (int i = 0; i < n; ++i) {
    cnt[i] = 0;
    a[i * 2].id = a[i * 2 + 1].id = i;
    cin >> a[i * 2].val >> a[i * 2 + 1].val;
    max_b = max(max_b, a[i * 2 + 1].val);
  }

  int n2 = 2 * n, cur = 0, ans = 0;
  sort(a, a + n2);
  for (int l = 0, r = -1;; ++l) {
    int bound = (1ll * a[l].val * p - 1) / 100 + 1;
    while (r + 1 < n2 && a[r + 1].val >= bound) {
      if (!(cnt[a[++r].id]++))
        ++cur;
    }
    ans = max(ans, cur);
    if (!(--cnt[a[l].id]))
      --cur;
    if (a[l].val <= max_b)
      break;
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
