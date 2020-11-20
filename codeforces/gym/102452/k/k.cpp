#include <bits/stdc++.h>
using namespace std;

const int MAXN = 800 + 3;
const int INF = 0x3f3f3f3f;

int n, m, d[MAXN], flow[MAXN];
vector<int> algos[MAXN], softs[MAXN];

int gao(int x) { return x >= INF ? INF : x; }

int lr_solve(int &x, int &y) {
  int now = algos[1].empty() ? INF : algos[1].back();
  int cost = gao(now + (softs[1].empty() ? INF : softs[1].back()));
  int link = x = y = 1;
  for (int i = 2; i <= n; ++i) {
    now = gao(now + (flow[i - 1] >= 0 ? d[i - 1] : -d[i - 1]));
    if (algos[i].size() && algos[i].back() < now) {
      link = i;
      now = algos[i].back();
    }
    if (softs[i].size() && gao(now + softs[i].back()) < cost) {
      x = link, y = i;
      cost = gao(now + softs[i].back());
    }
  }
  return cost;
}

int rl_solve(int &x, int &y) {
  int now = algos[n].empty() ? INF : algos[n].back();
  int cost = gao(now + (softs[n].empty() ? INF : softs[n].back()));
  int link = x = y = n;
  for (int i = n - 1; i >= 1; --i) {
    now = gao(now + (flow[i] <= 0 ? d[i] : -d[i]));
    if (algos[i].size() && algos[i].back() < now) {
      link = i;
      now = algos[i].back();
    }
    if (softs[i].size() && gao(now + softs[i].back()) < cost) {
      x = link, y = i;
      cost = gao(now + softs[i].back());
    }
  }
  return cost;
}

int main() {
  ios::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 1; i < n; ++i) cin >> d[i];
  for (int i = 0, x, c; i < m; ++i) {
    cin >> x >> c;
    algos[x].push_back(c);
  }
  for (int i = 0, x, c; i < m; ++i) {
    cin >> x >> c;
    softs[x].push_back(c);
  }
  for (int i = 1; i <= n; ++i) {
    sort(algos[i].begin(), algos[i].end(), greater<int>());
    sort(softs[i].begin(), softs[i].end(), greater<int>());
  }

  long long ans = 0;
  for (int i = 0; i < m; ++i) {
    int x1, x2, y1, y2, ans1, ans2;
    ans1 = lr_solve(x1, y1);
    ans2 = rl_solve(x2, y2);
    if (ans1 <= ans2) {
      ans += ans1;
      algos[x1].pop_back();
      softs[y1].pop_back();
      for (int i = x1; i < y1; ++i) ++flow[i];
    } else {
      ans += ans2;
      algos[x2].pop_back();
      softs[y2].pop_back();
      for (int i = y2; i < x2; ++i) --flow[i];
    }
    cout << ans << "\n";
  }

  return 0;
}
