#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int MOD = 1e9 + 7;
const int MAXN = 8e5 + 3;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void prework() {}

struct Node {
  int value;
  Node *next;
  Node() {}
  Node(int x) : value(x), next(nullptr) {}
};

typedef pair<Node *, Node *> List;

List l[MAXN];
int pa[MAXN];

int find(int x) { return x == pa[x] ? x : pa[x] = find(pa[x]); }

List merge(List a, List b) {
  if (a.first == nullptr) return b;
  a.second->next = b.first;
  return {a.first, b.second};
}

List new_list(int x) {
  static Node pool[MAXN * 2], *pool_ptr = pool;
  *pool_ptr = Node(x);
  List t = {pool_ptr, pool_ptr};
  ++pool_ptr;
  return t;
}

void solve() {
  int n, m, q;
  cin >> n >> m;
  iota(pa, pa + n, 0);
  for (int i = 0; i < n; ++i) l[i] = {nullptr, nullptr};
  for (int u, v; m; --m) {
    cin >> u >> v;
    l[u] = merge(l[u], new_list(v));
    l[v] = merge(l[v], new_list(u));
  }
  cin >> q;
  for (int o; q; --q) {
    cin >> o;
    if (find(o) != o) continue;
    vi a;
    for (Node *it = l[o].first; it != nullptr; it = it->next) {
      int x = find(it->value);
      if (x != o) {
        pa[x] = o;
        a.push_back(x);
      }
    }
    l[o] = {nullptr, nullptr};
    for (int x : a) l[o] = merge(l[o], l[x]);
  }
  for (int i = 0; i < n; ++i) cout << find(i) << " \n"[i == n - 1];
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  prework();
  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
