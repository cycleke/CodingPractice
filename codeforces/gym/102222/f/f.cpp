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

constexpr int MAXN = 200 + 3;
constexpr int MAXQ = 2e4 + 3;

tuple<int, int, int, int> query[MAXQ];
int ans[MAXQ], d[MAXN][MAXN], r[MAXN], rk[MAXN];

void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; ++i) {
    rk[i] = i;
    cin >> r[i];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) { cin >> d[i][j]; }
  }
  for (int i = 0, u, v, w; i < q; ++i) {
    cin >> u >> v >> w;
    query[i] = make_tuple(w, u - 1, v - 1, i);
  }

  sort(rk, rk + n, [&](const int &a, const int &b) { return r[a] < r[b]; });
  sort(query, query + q);

  for (int iq = 0, ik = 0, id, u, v, w; iq < q; ++iq) {
    tie(w, u, v, id) = query[iq];
    while (ik < n && r[rk[ik]] <= w) {
      int k = rk[ik++];
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
      }
    }
    ans[id] = d[u][v];
  }

  for (int i = 0; i < q; ++i) cout << ans[i] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(6);

  int v_v = 0, o_o;
  for (cin >> o_o; v_v < o_o; solve()) cout << "Case #" << ++v_v << ":\n";

  return 0;
}
