#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define debug(...) fprintf(stderr, __VA_ARGS__)

const int MAXN = 1e4 + 3;
const int MAXM = 500000 + 3;

pair<int, pii> es[MAXM];
int p[MAXN], id[MAXN], sz[MAXN];

int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i)
    cin >> es[i].second.first >> es[i].second.second >> es[i].first;
  sort(es, es + m);

  int min_start = 0;
  for (int l = 1, r = m - n + 1; l <= r;) {
    int mid = (l + r) / 2, cnt = 1;
    iota(p + 1, p + n + 1, 1);
    for (int i = mid; i < m && cnt < n; ++i) {
      int u = find(es[i].second.first), v = find(es[i].second.second);
      if (u == v) continue;
      p[u] = v, ++cnt;
    }
    if (cnt < n) {
      r = mid - 1;
    } else {
      min_start = mid;
      l = mid + 1;
    }
  }

  int cnt = 1;
  iota(p + 1, p + n + 1, 1);
  for (int i = min_start; i < m && cnt < n; ++i) {
    int u = find(es[i].second.first), v = find(es[i].second.second);
    if (u == v) continue;
    p[u] = v, id[cnt++] = i;
  }

  long long sum = 0;
  iota(p + 1, p + n + 1, 1);
  fill(sz + 1, sz + n + 1, 1);
  for (int i = cnt - 1; i; --i) {
    int e = id[i];
    int u = find(es[e].second.first), v = find(es[e].second.second);
    sum += 1ll * sz[u] * sz[v] * es[e].first;
    p[u] = v, sz[v] += sz[u];
  }
  cout << sum << "\n";

  return 0;
}
