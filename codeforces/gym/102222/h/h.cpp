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

constexpr int MAXN = 1e5 + 3;

pii a[MAXN];
int s[MAXN], cnt;

void solve() {
  int n;
  ll sum = 0, ans = 0;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
    sum += a[i].second;
    a[i].first = lower_bound(s, s + cnt, a[i].first) - s;
  }

  sort(a, a + n, [&](const pii &a, const pii &b) {
    return 1ll * a.first * b.second < 1ll * a.second * b.first;
  });

  for (int i = 0; i < n; ++i) {
    ans += sum * a[i].first;
    sum -= a[i].second;
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(3);

  for (cnt = 1; s[cnt - 1] < MAXN; ++cnt) s[cnt] = cnt + s[cnt - 1];

  int v_v = 0, o_o;
  for (cin >> o_o; v_v < o_o; solve()) cout << "Case #" << ++v_v << ": ";

  return 0;
}
