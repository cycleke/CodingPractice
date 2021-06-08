#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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

constexpr int MAXN = 50;
const double PI = acos(-1);

struct Point {
  int x, y;

  Point() {}
  Point(int x, int y) : x(x), y(y) {}

  Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
  int operator*(const Point &p) const { return x * p.x + y * p.y; }
} p[MAXN], q;

double len[MAXN];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> p[i].x >> p[i].y;
    if (i) len[i] = hypot(p[i].x - p[i - 1].x, p[i].y - p[i - 1].y);
  }
  len[0] = hypot(p[0].x - p[n - 1].x, p[0].y - p[n - 1].y);

  cin >> q.x >> q.y;

  double ans = 0;
  for (int i = 0; i < n; ++i) {
    double dist = hypot(p[i].x - q.x, p[i].y - q.y);
    Point a = p[(i - 1 + n) % n] - p[i], b = p[(i + 1) % n] - p[i];
    double ang = PI - acos(a * b / (len[i] * len[(i + 1) % n]));
    debug(ang, len[i], len[i + 1], a * b);
    ans += ang * dist;
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(3);

  int v_v = 0, o_o;
  for (cin >> o_o; v_v < o_o; solve()) cout << "Case #" << ++v_v << ": ";

  return 0;
}
