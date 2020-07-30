#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int MAXM = 1e5 + 5;
int mindiv[MAXM];

void sieve() {
  vi primes;
  mindiv[1] = 1;
  for (int i = 2; i < MAXM; ++i) {
    if (mindiv[i] == 0) {
      mindiv[i] = i;
      primes.push_back(i);
    }
    for (int prime : primes) {
      int t = i * prime;
      if (t >= MAXM) break;
      mindiv[t] = prime;
      if (i % prime == 0) break;
    }
  }
}

template <int MAX_LENGTH> class BinaryIndexTree {
public:
  void add(int x, int delta) {
    for (; x <= n; x += x & -x) a[x] += delta;
  }

  int ask(int x) {
    int sum = 0;
    for (; x > 0; x &= x - 1) sum += a[x];
    return sum;
  }

  void set(int n) {
    this->n = n;
    memset(a + 1, 0, sizeof(int) * n);
  }

private:
  int n, a[MAX_LENGTH];
};

BinaryIndexTree<MAXM> bit;

const int MAXN = 2 * MAXM;

int w[MAXM];
vi adj[MAXN];
int dep[MAXN], lca_dep[MAXN];
ll value[MAXN], ans[MAXN];

int build_tree(int m) {
  int n = m;
  dep[1] = 1;
  for (int i = 2, x; i <= m; ++i) {
    dep[i] = dep[i - 1] + 1;
    for (x = i; x != mindiv[x]; x /= mindiv[x]) ++dep[i];
    lca_dep[i] = bit.ask(m) - bit.ask(x - 1) + 1;
    for (x = i; x > 1; x /= mindiv[x]) bit.add(mindiv[x], 1);
  }

  static int stk[MAXN];
  int top = 0;
  stk[++top] = 1;
  for (int i = 2; i <= m; ++i) {
    for (; top > 1 && dep[stk[top - 1]] >= lca_dep[i]; --top)
      adj[stk[top - 1]].push_back(stk[top]);
    if (dep[stk[top]] != lca_dep[i]) {
      ++n;
      dep[n] = lca_dep[i];
      w[n] = 0;
      adj[n].push_back(stk[top]);
      stk[top] = n;
    }
    stk[++top] = i;
  }
  for (; top > 1; --top) adj[stk[top - 1]].push_back(stk[top]);
  return n;
}

void dfs1(int u) {
  value[u] = w[u], ans[u] = 0;
  for (int v : adj[u]) {
    dfs1(v);
    value[u] += value[v];
    ans[u] += ans[v] + value[v] * (dep[v] - dep[u]);
  }
}

void dfs2(int u) {
  for (int v : adj[u]) {
    ll x = ans[u] - ans[v] - value[v] * (dep[v] - dep[u]);
    ll y = value[u] - value[v];
    ans[v] += x + y * (dep[v] - dep[u]);
    value[v] += y;
    dfs2(v);
  }
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  sieve();
  int m;
  while (cin >> m) {
    bit.set(m);
    for (int i = 1; i <= m; ++i) cin >> w[i];

    int n = build_tree(m);
    dfs1(1), dfs2(1);

    ll res = LLONG_MAX;
    for (int i = 1; i <= n; ++i) {
      adj[i].clear();
      res = min(res, ans[i]);
    }
    cout << res << "\n";
  }

  return 0;
}
