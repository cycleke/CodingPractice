#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

const int MAXN = 1e5 + 5;

int n, m, a[MAXN], ans[MAXN];

int tree[MAXN * 4], pre;
void init(int n) {
  memset(tree, 0, sizeof(tree));
  for (pre = 1; pre <= n; pre <<= 1) {}
}
void update(int pos) {
  ++tree[pos += pre];
  for (pos >>= 1; pos; pos >>= 1) ++tree[pos];
}
int query(int s, int t) {
  int res = 0;
  for (s += pre - 1, t += pre + 1; s ^ t ^ 1; s >>= 1, t >>= 1) {
    if (~s & 1) res += tree[s ^ 1];
    if (t & 1) res += tree[t ^ 1];
  }
  return res;
}

int pos[MAXN];
pii con[MAXN * 20];
pair<pii, int> ques[MAXN];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int cnt = 0;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    pos[a[i]] = i;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i + i; j <= n; j += i)
      con[cnt++] = pii(max(pos[i], pos[j]), min(pos[i], pos[j]));
  }

  sort(con, con + cnt);

  for (int i = 0; i < m; ++i) {
    cin >> ques[i].first.second >> ques[i].first.first;
    ques[i].second = i;
  }
  sort(ques, ques + m);

  init(n);
  int i1 = 0, i2 = 0;
  for (int end = 1; end <= n; ++end) {
    for (; i1 < cnt && con[i1].first == end; ++i1) update(con[i1].second);
    for (; i2 < m && ques[i2].first.first == end; ++i2)
      ans[ques[i2].second] = query(ques[i2].first.second, ques[i2].first.first);
  }

  for (int i = 0; i < m; ++i) cout << ans[i] << '\n';
  return 0;
}
