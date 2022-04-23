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

// constexpr int kMod = 1e9 + 7;
constexpr int kMaxN = 300 + 3;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Vec {
  int x, y;

  Vec(int _x = 0, int _y = 0) : x(_x), y(_y) {}

  Vec operator-(const Vec &other) const {
    return Vec(x - other.x, y - other.y);
  }

  i64 operator*(const Vec &other) const {
    return 1ll * x * other.x + 1ll * y * other.y;
  }

  i64 operator^(const Vec &other) const {
    return 1ll * x * other.y - 1ll * y * other.x;
  }

  double len() const { return sqrt(1ll * x * x + 1ll * y * y); }
} pts[kMaxN], ori;

double dist[kMaxN][kMaxN];

int sgn(int x) { return x != 0 ? (x < 0 ? -1 : 1) : 0; }

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> pts[i].x >> pts[i].y;
  }
  cin >> ori.x >> ori.y;
  for (int i = 0; i < n; ++i) {
    pts[i] = pts[i] - ori;
  }
  sort(pts, pts + n, [](const Vec &a, const Vec &b) {
    int sa = a.y != 0 ? sgn(a.y) : -sgn(a.x);
    int sb = b.y != 0 ? sgn(b.y) : -sgn(b.x);
    return sa == sb ? (a ^ b) > 0 : sa < sb;
  });

  constexpr double kInf = 1e18;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      dist[i][j] = (pts[i] ^ pts[j]) > 0 ? (pts[i] - pts[j]).len() : kInf;
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  double ans = kInf;
  for (int i = 0; i < n; ++i) {
    ans = min(ans, dist[i][i]);
  }
  if (ans == kInf) {
    cout << "IMPOSSIBLE\n";
  } else {
    cout << ans << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int o_o, v_v = 0;
  for (cin >> o_o; o_o; --o_o) {
    cout << "Case #" << ++v_v << ": ";
    solve();
  }
  return 0;
}
