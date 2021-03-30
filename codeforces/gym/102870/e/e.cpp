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

constexpr int MAXN = 4e5 + 3;
constexpr int G = 10;
constexpr int P = 786433;

int mpow(int a, int b) {
  int r = 1;
  for (; b; b >>= 1, a = 1ll * a * a % P) (b & 1) && (r = 1ll * a * r % P);
  return r;
}

ll c2kt[MAXN], c2t[MAXN];
int rev[MAXN], a[MAXN], b[MAXN], c[MAXN];

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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  ll k, c2k = 0;
  int n, lim = 1, cnt = 0;
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (ll x = (k - 1) / 2; x; x /= 2) c2k += x;
  for (int i = 0; i <= n; ++i)
    for (ll j = 2; j <= i + k - 1; j *= 2)
      c2kt[i] += (i + k - 1) / j, c2t[i] += i / j;

  for (int i = 0; i <= n; ++i) c[i] = c2kt[i] <= c2t[i] + c2k;

  while (lim < n + n + 1) lim <<= 1, ++cnt;
  rev[0] = 0;
  for (int i = 1; i < lim; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (cnt - 1));

  ntt(c, lim, 1);
  for (int bit = 0; bit < 17; ++bit) {
    for (int i = 0; i < lim; ++i) {
      int x = a[i] >> bit & 1;
      b[i] = x, a[i] ^= x << bit;
    }

    ntt(b, lim, 1);
    for (int i = 0; i < lim; ++i) b[i] = 1ll * b[i] * c[i] % P;
    ntt(b, lim, -1);

    for (int i = 1; i <= n; ++i) a[i] |= (b[i] & 1) << bit;
  }

  for (int i = 1; i <= n; ++i) cout << a[i] << " \n"[i == n];

  return 0;
}
