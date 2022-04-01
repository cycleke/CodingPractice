#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using pii = pair<int, int>;

void debug_out() { cerr << endl; }
template <typename T> string to_string(const vector<T> &vec) {
  string res = "[";
  bool first = true;
  for (const T &x : vec) {
    if (first) {
      first = false;
    } else {
      res += ",";
    }
    res += to_string(x);
  }
  return res + "]";
}
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

const int MAXN = 2e3 + 3;

int main() {
  ios::sync_with_stdio(false);

  int n;
  cin >> n;

  vector<pii> es;
  cout << "? 1\n";
  cout.flush();

  vector<int> v[2];
  for (int j = 1, d; j <= n; ++j) {
    cin >> d;
    if (d == 1) { es.emplace_back(1, j); }
    v[d & 1].push_back(j);
  }
  if (v[0].size() > v[1].size()) { v[0].swap(v[1]); }

  for (int u : v[0]) {
    if (u == 1) { continue; }
    cout << "? " << u << "\n";
    cout.flush();

    for (int j = 1, d; j <= n; ++j) {
      cin >> d;
      if (d == 1) { es.emplace_back(min(u, j), max(u, j)); }
    }
  }

  sort(es.begin(), es.end());
  es.erase(unique(es.begin(), es.end()), es.end());

  cout << "!\n";
  for (auto &[u, v] : es) { cout << u << " " << v << "\n"; }

  return 0;
}
