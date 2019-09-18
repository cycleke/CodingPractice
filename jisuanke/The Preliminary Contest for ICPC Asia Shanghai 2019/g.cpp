#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int MAXM = 2e4 + 5;
const int ALPHABET = 26;

const unsigned int SEED = 6163;

struct Query {
  int id, s, t;
  unsigned int val;
};

vector<Query> q[MAXN];
int ans[MAXM], n, m, cnt[ALPHABET];
char str[MAXN], t[MAXN];
unordered_map<unsigned int, int> sum[ALPHABET][ALPHABET];
unsigned int p[ALPHABET];

inline void add(unordered_map<unsigned int, int> &cnt, const unsigned int &val) {
  auto it = cnt.find(val);
  if (it != cnt.end()) ++it->second;
}

inline void gao(const int &len) {
  if (q[len].empty()) return;
  memset(cnt, 0, sizeof(cnt));
  unsigned int val = 0;
  for (register int i = 0; i < len; ++i) ++cnt[str[i] - 'a'];
  for (register int i = 0; i < ALPHABET; ++i) val = val * SEED + cnt[i];
  for (register int i = 0; i < ALPHABET; ++i)
    for (register int j = 0; j < ALPHABET; ++j) sum[i][j].clear();
  for (auto &qu : q[len]) sum[qu.s][qu.t][qu.val] = 0;
  for (register int l = 0, r = len - 1; r < n; ++l) {
    add(sum[str[l] - 'a'][str[r] - 'a'], val);
    val -= p[str[l] - 'a'];
    if (++r < n) val += p[str[r] - 'a'];
  }
  for (auto &qu : q[len]) ans[qu.id] = sum[qu.s][qu.t][qu.val];
}

inline void solve() {
  fgets(str, MAXN, stdin);
  n = strlen(str);
  while (str[n - 1] == '\n' || str[n - 1] == '\r') --n;
  for (int i = 1; i <= n; ++i) q[i].clear();

  scanf("%d\n", &m);
  for (int i = 0, l, j; i < m; ++i) {
    // cin >> t;
    fgets(t, MAXN, stdin);
    memset(cnt, 0, sizeof(cnt));
    l = strlen(t);
    while (t[l - 1] == '\n' || t[l - 1] == '\r') --l;
    if (l > n) {
      ans[i] = 0;
      continue;
    }
    for (j = 0; j < l; ++j) ++cnt[t[j] - 'a'];
    unsigned int val = 0;
    for (j = 0; j < ALPHABET; ++j) val = val * SEED + cnt[j];
    q[l].push_back((Query){i, t[0] - 'a', t[l - 1] - 'a', val});
  }
  for (int i = 1; i <= n; ++i) gao(i);
  for (int i = 0; i < m; ++i) printf("%d\n", ans[i]);
}

int main() {
  // freopen("in.txt", "r", stdin);
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  p[0] = 1;
  for (int i = 1; i < ALPHABET; ++i) p[i] = p[i - 1] * SEED;
  reverse(p, p + ALPHABET);

  int o_o;
  for (scanf("%d\n", &o_o); o_o; --o_o) solve();

  return 0;
}
