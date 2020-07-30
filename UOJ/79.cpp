#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
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

class GeneralMatch {
public:
  int n;
  vector<vi> g;
  vi match, aux, label, orig, parent;
  queue<int> q;
  int aux_time;

  GeneralMatch(int n)
      : match(n, -1), aux(n, -1), label(n), orig(n), parent(n, -1),
        aux_time(-1) {
    this->n = n;
    g.resize(n);
  }

  void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }

  int find(int x) { return x == orig[x] ? x : orig[x] = find(orig[x]); }

  int lca(int u, int v) {
    ++aux_time;
    u = find(u), v = find(v);
    for (;; swap(u, v)) {
      if (~u) {
        if (aux[u] == aux_time) return u;
        aux[u] = aux_time;
        if (match[u] == -1) {
          u = -1;
        } else {
          u = find(parent[match[u]]);
        }
      }
    }
  }

  void blossom(int u, int v, int o) {
    while (find(u) != o) {
      parent[u] = v;
      v = match[u];
      q.push(v);
      label[v] = 0;
      orig[u] = orig[v] = o;
      u = parent[v];
    }
  }

  int bfs(int x) {
    iota(orig.begin(), orig.end(), 0);
    fill(label.begin(), label.end(), -1);
    while (!q.empty()) q.pop();
    q.push(x);
    label[x] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : g[u]) {
        if (label[v] == -1) {
          parent[v] = u;
          label[v] = 1;
          if (match[v] == -1) {
            while (v != -1) {
              int pv = parent[v];
              int next_v = match[pv];
              match[v] = pv;
              match[pv] = v;
              v = next_v;
            }
            return 1;
          }
          q.push(match[v]);
          label[match[v]] = 0;
        } else if (label[v] == 0 && find(u) != find(v)) {
          int o = lca(u, v);
          blossom(u, v, o);
          blossom(v, u, o);
        }
      }
    }
    return 0;
  }

  int find_max_match() {
    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (~match[i]) continue;
      res += bfs(i);
    }
    return res;
  }
};

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  GeneralMatch gm(n);
  for (int u, v; m; --m) {
    cin >> u >> v;
    gm.add_edge(--u, --v);
  }
  int res = gm.find_max_match();
  cout << res << "\n";
  for (int x : gm.match) cout << x + 1 << " ";

  return 0;
}
