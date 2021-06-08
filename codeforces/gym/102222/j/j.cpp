#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using pii = pair<int, int>;
using p66 = pair<i64, i64>;

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

constexpr int MAXN = 1e5 + 3;

struct Vec {
  i64 x, y;

  Vec() {}
  Vec(int x_, int y_) : x(x_), y(y_) {}

  Vec operator-(const Vec &other) const {
    return Vec(x - other.x, y - other.y);
  }

  i64 dot(const Vec &other) const { return x * other.x + y * other.y; }
  i64 cross(const Vec &other) const { return x * other.y - y * other.x; }
} p, q;

int rk[MAXN], ord[MAXN];
tuple<int, int, int> dp[MAXN], bit[MAXN];
pair<Vec, int> lhs[MAXN], rhs[MAXN];

void gao(pair<Vec, int> ps[], int n, bool sign) {
  for (int i = 0; i < n; ++i) { rk[i] = i; }

  sort(rk, rk + n, [&](const int &a, const int &b) {
    i64 x = (ps[a].first - p).cross(ps[b].first - p);
    i64 y = (ps[a].first - q).cross(ps[b].first - q);
    return sign ? p66(x, y) > p66(0, 0) : p66(x, y) < p66(0, 0);
  });

  ord[rk[0]] = 0;
  for (int i = 1; i < n; ++i) {
    ord[rk[i]] =
        ord[rk[i - 1]] +
        ((ps[rk[i]].first - p).cross(ps[rk[i - 1]].first - p) == 0 ? 0 : 1);
  }

  sort(rk, rk + n, [&](const int &a, const int &b) {
    i64 x = (ps[a].first - q).cross(ps[b].first - q);
    i64 y = (ps[a].first - p).cross(ps[b].first - p);
    return sign ? p66(x, y) < p66(0, 0) : p66(x, y) > p66(0, 0);
  });

  bit[0] = make_tuple(0, -1, -1);
  for (int i = 0; i <= n; ++i) { bit[i] = bit[0]; }

  static auto upd = [&](int x, tuple<int, int, int> val) {
    for (; x <= n; x += x & -x) { bit[x] = max(bit[x], val); }
  };

  static auto qry = [&](int x) {
    auto res = make_tuple(0, 1, 1);
    for (; x; x &= x - 1) { res = max(res, bit[x]); }
    return res;
  };

  for (int i = 0, j; i < n; i = j) {
    for (j = i + 1; j < n; ++j) {
      if ((ps[rk[j]].first - q).cross(ps[rk[i]].first - q) != 0) { break; }
    }
    for (int k = i, len, cur, pre; k < j; ++k) {
      tie(len, cur, pre) = qry(ord[rk[k]]);
      dp[ps[rk[k]].second] = make_tuple(len + 1, -ps[rk[k]].second, cur);
    }

    for (int k = i; k < j; ++k) { upd(ord[rk[k]] + 1, dp[ps[rk[k]].second]); }
  }
}

void solve() {
  int n, lc = 0, rc = 0;
  cin >> p.x >> p.y >> q.x >> q.y >> n;

  Vec a, pq = q - p;
  for (int i = 0; i < n; ++i) {
    cin >> a.x >> a.y;
    if (pq.cross(a - p) > 0) {
      lhs[lc++] = make_pair(a, i);
    } else {
      rhs[rc++] = make_pair(a, i);
    }
  }

  gao(lhs, lc, true);
  gao(rhs, rc, false);

  auto res = make_tuple(0, -1, -1);
  for (int i = 0; i < n; ++i) { res = max(res, dp[i]); }

  int len, cur, pre;
  tie(len, cur, pre) = res;
  cout << len << "\n";

  while (true) {
    cout << -cur + 1 << "\n";
    if (len > 1) {
      tie(len, cur, pre) = dp[-pre];
    } else {
      break;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(6);

  int v_v = 0, o_o;
  for (cin >> o_o; v_v < o_o; solve()) cout << "Case #" << ++v_v << ": ";

  return 0;
}
