#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

vector<tuple<int, int, int>> edges;
void add_edge(int u, int v, int w) { edges.emplace_back(u, v, w); }

int solve(int l, int r) {
  if ((r & -r) == r) {
    int k = __builtin_ctz(r) + 2;
    add_edge(1, 2, 1);
    for (int i = 3; i <= k; ++i) {
      add_edge(1, i, 1);
      for (int j = 2; j < i; ++j) add_edge(j, i, 1 << (j - 2));
    }
    return k;
  }
  int k = 0;
  while ((1 << (k + 1)) < r) ++k;
  solve(1, 1 << k);
  add_edge(1, k + 3, 1);
  for (int i = 0; i <= k; ++i)
    if ((r - 1) >> i & 1)
      add_edge(i + 2, k + 3, ((r - 1) >> (i + 1) << (i + 1)) + 1);
  return k + 3;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int l, r;
  cin >> l >> r;
  int n = solve(1, r - l + 1);
  if (l > 1) {
    ++n;
    add_edge(n - 1, n, l - 1);
  }
  cout << "YES\n" << n << " " << edges.size() << "\n";
  for (auto [u, v, w] : edges) cout << u << " " << v << " " << w << "\n";

  return 0;
}
