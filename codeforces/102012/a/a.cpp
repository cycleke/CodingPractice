#include <bits/stdc++.h>
using namespace std;

unsigned long long k1, k2;

unsigned long long rdm() {
  static unsigned long long k3, k4;
  k3 = k1;
  k4 = k2;
  k1 = k4;
  k3 ^= k3 << 23;
  k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
  return k2 + k4;
}

const int MAXN = 1e5 + 5;
const int M = 1e5;
const int MOD = 1e9 + 7;

int n, m, f[MAXN];
tuple<unsigned long long, int, int> edges[MAXN];

int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

void solve() {
  cin >> n >> m >> k1 >> k2;
  if (n == 1) {
    cout << "0\n";
    return;
  }
  iota(f, f + n, 0);
  int u, v, cnt = 1;
  unsigned long long w, ans = 0;
  for (int i = 0; i < M; ++i) {
    u = rdm() % n;
    v = rdm() % n;
    w = rdm();
    edges[i] = {w, u, v};
  }
  sort(edges, edges + M);
  for (int i = 0; i < M; ++i) {
    tie(w, u, v) = edges[i];
    u = find(u), v = find(v);
    if (u ^ v) {
      f[u] = v;
      ans = (ans + w) % MOD;
      if (++cnt == n) break;
    }
  }
  cout << (cnt < n ? 0 : ans) << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();

  return 0;
}
