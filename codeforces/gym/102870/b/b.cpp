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

constexpr int MAXM = 1e9;
constexpr int MAXN = 1e6;

map<int, int> mp_mu, mp_phi;
int m, p, sum_mu[MAXN], sum_phi[MAXN], pri[MAXN], pri_cnt, lpf[MAXN];

void add(int &x, const int &y) { ((x += y) >= p) && (x -= p); }

void sieve() {
  pri[lpf[1] = 0] = 1, sum_mu[1] = 1, sum_phi[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    if (!lpf[i]) {
      pri[lpf[i] = ++pri_cnt] = i;
      sum_mu[i] = -1, sum_phi[i] = i - 1;
    }
    for (int j = 1, x; j <= lpf[i] && (x = i * pri[j]) < MAXN; ++j) {
      lpf[x] = j;
      if (j < lpf[i]) {
        sum_mu[x] = -sum_mu[i], sum_phi[x] = sum_phi[i] * (pri[j] - 1);
      } else {
        sum_mu[x] = 0, sum_phi[x] = sum_phi[i] * pri[j];
      }
    }
  }
  for (int i = 2; i < MAXN; ++i)
    sum_mu[i] = (sum_mu[i] + sum_mu[i - 1]) % p,
    sum_phi[i] = (sum_phi[i] + sum_phi[i - 1]) % p;
}

int S_mu(int n) {
  if (n < MAXN) return sum_mu[n];
  if (mp_mu.count(n)) return mp_mu[n];
  int res = 1;
  for (int i = 2, j; i <= n; i = j + 1) {
    j = n / (n / i);
    res -= S_mu(n / i) * (j - i + 1);
  }
  return mp_mu[n] = res;
}

int S_phi(int n) {
  if (n < MAXN) return sum_phi[n];
  if (mp_phi.count(n)) return mp_phi[n];
  ll res = 0;
  for (int i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i);
    res += 1ll * (S_mu(j) - S_mu(i - 1)) * (n / i) * (n / i);
  }
  return mp_phi[n] = ((res - 1) / 2 + 1) % p;
}

using Mat = int[2][2];

void mul(Mat a, Mat b) {
  static Mat c;
  memset(c, 0, sizeof(c));
  for (int k = 0; k < 2; ++k)
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 2; ++j)
        c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j]) % p;
  memcpy(a, c, sizeof(c));
}

int fib(int n) {
  if (n <= 1) return 1;
  if (n == 2) return 2;

  Mat a = {{1, 0}, {0, 1}};
  Mat b = {{0, 1}, {1, 1}};
  for (n -= 2; n; n >>= 1, mul(b, b)) (n & 1) && (mul(a, b), 0);
  return (1ll * a[1][0] + 2ll * a[1][1]) % p;
}

int S_g(int n) {
  if (n == 1) return 1;
  int res = n - (n & 1) - 3;
  add(res, fib(n));
  add(res, fib(n + 2));
  if (res < 0) res += p;
  debug(n, res);
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  cin >> m >> p;
  sieve();

  int res = 0;
  for (int i = 1, j, d; i <= m; i = j + 1) {
    d = m / i, j = m / d;
    int sg = S_g(d);
    int sphi = S_phi(j) - S_phi(i - 1);
    if (sphi < 0) sphi += p;
    add(res, 1ll * sg * sphi % p);
  }
  cout << res << "\n";

  return 0;
}
