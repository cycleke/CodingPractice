#include <bits/stdc++.h>

using namespace std;

const int maxm = 1e6 + 5;
int a[maxm], b[maxm];
long long s[maxm], t[maxm];
double p[maxm];
vector<int> G[maxm * 2];
map<long long, double> f[maxm];

int main() {
  int n, m;
  long long k;
  scanf("%d %d %lld", &m, &n, &k);

  vector<pair<long long, int> > eve;
  for (int i = 0; i < m; ++i) {
    scanf("%d %d %lld %lld %lf", a + i, b + i, s + i, t + i, p + i);
    if (a[i] == 1 || t[i] > k) {
      m--;
      i--;
      continue;
    }
    eve.emplace_back(s[i], a[i]);
    eve.emplace_back(t[i], b[i]);
  }
  eve.emplace_back(k + 1, 1);
  sort(eve.begin(), eve.end());
  eve.erase(unique(eve.begin(), eve.end()), eve.end());

  for (int i = 0; i < m; ++i) {
    int x = lower_bound(eve.begin(), eve.end(), make_pair(s[i], a[i])) -
            eve.begin();
    G[x].push_back(i);
  }
  map<long long, double>::iterator it;
  for (int i = eve.size() - 1; i >= 0; --i) {
    int pos = eve[i].second;
    long long cur_time = eve[i].first;
    double pre = (pos == 1) ? 1 : 0;
    if (pos != 1) {
      it = f[pos].upper_bound(cur_time);
      if (it != f[pos].end()) pre = it->second;
    }
    double x = pre;
    for (int y : G[i]) {
      it = f[b[y]].upper_bound(t[y]);
      if (it == f[b[y]].end()) continue;
      x = max(x, p[y] * it->second + (1 - p[y]) * pre);
    }
    f[pos][cur_time] = x;
  }
  printf("%.10lf", f[0].begin()->second);
  return 0;
}
