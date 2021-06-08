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

constexpr int MAXN = 36;
constexpr int MAXS = 1 << 18;

vector<int> ls, rs;
vector<pii> le, re, lre;
int w[MAXN], mod, lw[MAXS], rw[MAXS], sum[MAXS];

void gao(int n, const vector<pii> &es, vector<int> &ss, int bias, int ws[]) {
  ss.clear();
  for (int s = 0; s < (1 << n); ++s) {
    ws[s] = 0;

    bool valid = true;
    for (pii e : es) {
      int u = e.first - bias;
      int v = e.second - bias;
      if ((s >> u & 1) == 0 && (s >> v & 1) == 0) {
        valid = false;
        break;
      }
    }

    if (!valid) { continue; }

    ws[s] = 1;
    ss.push_back(s);
    for (int i = 0; i < n; ++i) {
      if (s >> i & 1) { ws[s] = 1ll * ws[s] * w[i + bias] % mod; }
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m >> mod;
  for (int i = 0; i < n; ++i) { cin >> w[i]; }

  int l = n / 2, r = n - l;
  le.clear();
  re.clear();
  lre.clear();
  for (int i = 0, u, v; i < m; ++i) {
    cin >> u >> v;
    if (u > v) { swap(u, v); }
    bool lu = u <= l, lv = v <= l;
    if (lu && lv) {
      le.emplace_back(u - 1, v - 1);
    } else if (lu || lv) {
      lre.emplace_back(u - 1, v - 1);
    } else {
      re.emplace_back(u - 1, v - 1);
    }
  }

  if (n == 1) {
    cout << "0\n";
    return;
  }

  gao(l, le, ls, 0, lw);
  gao(r, re, rs, l, rw);

  memset(sum, 0, sizeof(int) * (1 << r));
  for (int lhs : ls) {
    int t = 0;
    for (pii e : lre) {
      int u = e.first;
      int v = e.second - l;
      if (~lhs >> u & 1) { t |= 1 << v; }
    }
    sum[t] += lw[lhs];
    if (sum[t] >= mod) { sum[t] -= mod; }
  }

  for (int j = 0; j < r; ++j) {
    for (int i = 0; i < (1 << r); ++i) {
      if (i & (1 << j)) {
        sum[i] += sum[i ^ (1 << j)];
        if (sum[i] >= mod) { sum[i] -= mod; }
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < (1 << r); ++i) {
    ans = (ans + 1ll * sum[i] * rw[i]) % mod;
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int v_v = 0, o_o;
  for (cin >> o_o; v_v < o_o; solve()) cout << "Case #" << ++v_v << ": ";

  return 0;
}
