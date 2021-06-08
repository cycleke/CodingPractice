#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 5e3 + 3;

int tot, root, fa[MAXN];
vector<int> val[MAXN], ch[MAXN];

void maintain(int x) {
  sort(val[x].begin(), val[x].end());
  sort(ch[x].begin(), ch[x].end(),
       [&](const int &a, const int &b) { return val[a][0] < val[b][0]; });
}

void insert(int x, int v) {
  maintain(x);
  if (val[x].size() == 3) {
    int y = ++tot;
    if (fa[x] == 0) {
      fa[x] = root = ++tot;
      ch[fa[x]].push_back(x);
    }
    fa[y] = fa[x], ch[fa[x]].push_back(y);
    val[y].push_back(val[x].back()), val[x].pop_back();
    if (ch[x].size()) {
      fa[ch[x].back()] = y;
      ch[y].push_back(ch[x].back()), ch[x].pop_back();
    }
    if (ch[x].size()) {
      fa[ch[x].back()] = y;
      ch[y].push_back(ch[x].back()), ch[x].pop_back();
    }
    val[fa[x]].push_back(val[x].back()), val[x].pop_back();
    maintain(x), maintain(y), maintain(fa[x]);
    x = fa[x];
  }
  if (ch[x].empty()) {
    val[x].push_back(v);
    maintain(x);
  } else {
    int id = 0;
    for (int i = 0; i < val[x].size(); ++i)
      if (v > val[x][i]) id = i + 1;
    insert(ch[x][id], v);
  }
}

void print(int x) {
  maintain(x);
  for (int i = 0; i < val[x].size(); ++i)
    printf("%d%c", val[x][i], " \n"[i == val[x].size() - 1]);
  for (int i = 0; i < ch[x].size(); ++i) print(ch[x][i]);
}

void solve() {
  int n;
  scanf("%d", &n);
  tot = root = 1;
  for (int x; n; --n) {
    scanf("%d", &x);
    insert(root, x);
  }
  print(root);
  for (int i = 0; i <= tot; ++i) val[i].clear(), ch[i].clear(), fa[i] = 0;
}

int main() {
  int v_v = 0, o_o;
  for (scanf("%d", &o_o); v_v < o_o; solve()) printf("Case #%d:\n", ++v_v);
  return 0;
}
