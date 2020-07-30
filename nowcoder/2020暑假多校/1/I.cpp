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
  while (cin >> n >> m) {
    static int deg[50];
    int demand = 0;
    for (int i = 0; i < n; ++i) {
      cin >> deg[i];
      demand += deg[i];
    }

    GeneralMatch gm(2 * (n + m));
    for (int u, v, i = 0; i < m; ++i) {
      cin >> u >> v;
      --u, --v;
      if (deg[u] == 2) swap(u, v);
      if (deg[u] == 2) {
        gm.add_edge(2 * u, 2 * (n + i));
        gm.add_edge(2 * u + 1, 2 * (n + i));
        gm.add_edge(2 * v, 2 * (n + i) + 1);
        gm.add_edge(2 * v + 1, 2 * (n + i) + 1);
        gm.add_edge(2 * (n + i), 2 * (n + i) + 1);
      } else if (deg[v] == 2) {
        gm.add_edge(2 * u, 2 * v);
        gm.add_edge(2 * u, 2 * v + 1);
      } else {
        gm.add_edge(2 * u, 2 * v);
      }
    }
    gm.find_max_match();
    bool yes = true;
    for (int i = 0; i < n; ++i) {
      if (deg[i] == 2) {
        if (gm.match[2 * i] == -1 || gm.match[2 * i + 1] == -1) {
          yes = false;
          break;
        }
      } else {
        if (gm.match[2 * i] == -1) {
          yes = false;
          break;
        }
      }
    }
    cout << (yes ? "Yes\n" : "No\n");
  }

  return 0;
}
