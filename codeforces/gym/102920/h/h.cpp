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

constexpr int BIAS = 3e4;
constexpr int MAX_EXP = 5 * BIAS;
constexpr int MAXN = 5e4;
constexpr int G = 10;
constexpr int P = 786433;
// constexpr int G = 3;
// constexpr int P = 998244353;

int mpow(int a, int b) {
  int r = 1;
  for (; b; b >>= 1, a = 1ll * a * a % P) (b & 1) && (r = 1ll * r * a % P);
  return r;
}

int rev[MAX_EXP];

void ntt(int *x, int n, int sign) {
  for (int i = 0; i < n; ++i)
    if (rev[i] < i) swap(x[i], x[rev[i]]);
  for (int j = 1; j < n; j <<= 1) {
    int gn = mpow(G, (P - 1) / (j << 1));
    for (int i = 0; i < n; i += (j << 1)) {
      for (int k = 0, g = 1; k < j; ++k, g = 1ll * g * gn % P) {
        int &a = x[i + j + k], &b = x[i + k], t = 1ll * g * a % P;
        (a = b - t) < 0 ? a += P : 0;
        (b = b + t) >= P ? b -= P : 0;
      }
    }
  }
  if (sign == -1) {
    reverse(x + 1, x + n);
    for (int i = 0, inv = mpow(n, P - 2); i < n; ++i)
      x[i] = 1ll * x[i] * inv % P;
  }
}

int u[MAX_EXP], l[MAX_EXP], xms[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int nu, nm, nl;

  cin >> nu;
  for (int i = 0, x; i < nu; ++i) {
    cin >> x;
    u[x + BIAS] = 1;
  }

  cin >> nm;
  for (int i = 0; i < nm; ++i) cin >> xms[i], xms[i] += BIAS;

  cin >> nl;
  for (int i = 0, x; i < nl; ++i) {
    cin >> x;
    l[x + BIAS] = 1;
  }

  int n = 1, bit = 0;
  while (n < 4 * BIAS) n <<= 1, ++bit;
  rev[0] = 0;
  for (int i = 1; i < n; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

  // debug(n, MAX_EXP);
  // for (int i = 0; i < n; ++i) {
  //   if (u[i] == 0) continue;
  //   debug(i, u[i], i - BIAS);
  // }

  // for (int i = 0; i < n; ++i) {
  //   if (l[i] == 0) continue;
  //   debug(i, l[i], i - BIAS);
  // }

  ntt(u, n, 1), ntt(l, n, 1);

  for (int i = 0; i < n; ++i) u[i] = 1ll * u[i] * l[i] % P;
  ntt(u, n, -1);

  // for (int i = 0; i < n; ++i) {
  //   if (u[i] == 0) continue;
  //   debug(i, u[i], i - 2 * BIAS);
  // }

  int ans = 0;
  for (int i = 0; i < nm; ++i) ans += u[2 * xms[i]];
  cout << ans << "\n";

  return 0;
}
