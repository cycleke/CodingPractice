#include <bits/stdc++.h>
using namespace std;

namespace FastIO {
struct Control {
  int ct, val;
  Control(int Ct, int Val = -1) : ct(Ct), val(Val) {}
  inline Control operator()(int Val) { return Control(ct, Val); }
} _endl(0), _prs(1), _setprecision(2);

const int IO_SIZE = 1 << 16 | 127;

struct FastIO {
  char in[IO_SIZE], *p, *pp, out[IO_SIZE], *q, *qq, ch[20], *t, b, K, prs;
  FastIO() : p(in), pp(in), q(out), qq(out + IO_SIZE), t(ch), b(1), K(6) {}
  ~FastIO() { fwrite(out, 1, q - out, stdout); }
  inline char getc() {
    return p == pp && (pp = (p = in) + fread(in, 1, IO_SIZE, stdin), p == pp)
               ? (b = 0, EOF)
               : *p++;
  }
  inline void putc(char x) {
    q == qq && (fwrite(out, 1, q - out, stdout), q = out), *q++ = x;
  }
  inline void puts(const char str[]) {
    fwrite(out, 1, q - out, stdout), fwrite(str, 1, strlen(str), stdout),
        q = out;
  }
  inline void getline(string &s) {
    s = "";
    for (char ch; (ch = getc()) != '\n' && b;) s += ch;
  }
#define indef(T)                                                               \
  inline FastIO &operator>>(T &x) {                                            \
    x = 0;                                                                     \
    char f = 0, ch;                                                            \
    while (!isdigit(ch = getc()) && b) f |= ch == '-';                         \
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();      \
    return x = f ? -x : x, *this;                                              \
  }
  indef(int);
  indef(long long);

  inline FastIO &operator>>(string &s) {
    s = "";
    char ch;
    while (isspace(ch = getc()) && b) {}
    while (!isspace(ch) && b) s += ch, ch = getc();
    return *this;
  }
  inline FastIO &operator>>(double &x) {
    x = 0;
    char f = 0, ch;
    double d = 0.1;
    while (!isdigit(ch = getc()) && b) f |= (ch == '-');
    while (isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getc();
    if (ch == '.')
      while (isdigit(ch = getc())) x += d * (ch ^ 48), d *= 0.1;
    return x = f ? -x : x, *this;
  }
#define outdef(_T)                                                             \
  inline FastIO &operator<<(_T x) {                                            \
    !x && (putc('0'), 0), x < 0 && (putc('-'), x = -x);                        \
    while (x) *t++ = x % 10 + 48, x /= 10;                                     \
    while (t != ch) *q++ = *--t;                                               \
    return *this;                                                              \
  }
  outdef(int);
  outdef(long long);
  inline FastIO &operator<<(char ch) { return putc(ch), *this; }
  inline FastIO &operator<<(const char str[]) { return puts(str), *this; }
  inline FastIO &operator<<(const string &s) { return puts(s.c_str()), *this; }
  inline FastIO &operator<<(double x) {
    int k = 0;
    this->operator<<(int(x));
    putc('.');
    x -= int(x);
    prs && (x += 5 * pow(10, -K - 1));
    while (k < K) putc(int(x *= 10) ^ 48), x -= int(x), ++k;
    return *this;
  }
  inline FastIO &operator<<(const Control &cl) {
    switch (cl.ct) {
    case 0: putc('\n'); break;
    case 1: prs = cl.val; break;
    case 2: K = cl.val; break;
    }
    return *this;
  }
  inline operator bool() { return b; }
};
} // namespace FastIO

FastIO::FastIO io;

const int MAXN = 1e5 + 5;

int n, A[MAXN], B[MAXN], C[MAXN], rev[MAXN * 4];

const double PI = acos(-1);

inline void fft(complex<double> *a, int sign, int n, int bit) {
  for (int i = 0; i < n; ++i)
    if (i < rev[i]) swap(a[i], a[rev[i]]);

  for (int j = 1; j < n; j <<= 1) {
    complex<double> wn(cos(2 * PI / (j << 1)), sign * sin(2 * PI / (j << 1)));
    for (int i = 0; i < n; i += (j << 1)) {
      complex<double> w(1, 0), t0, t1;
      for (int k = 0; k < j; ++k) {
        t0 = a[i + k];
        t1 = w * a[i + j + k];
        a[i + k] = t0 + t1;
        a[i + j + k] = t0 - t1;
        w *= wn;
      }
    }
  }
  if (sign == -1)
    for (int i = 0; i < n; ++i) a[i] /= n;
}

inline void gao_big(int *A, int *B, int *C, long long &ans) {
  static int max_a, max_b, bit, nn;
  static long long cnt[MAXN];
  static complex<double> a[MAXN * 4], b[MAXN * 4];
  nn = 1, bit = 0;
  max_a = max_b = -1;
  for (int i = 0; i < n; ++i)
    if (max_a < A[i]) max_a = A[i];
  for (int i = 0; i < n; ++i)
    if (max_b < B[i]) max_b = B[i];
  while (nn <= max_a + max_b) nn <<= 1, ++bit;
  rev[0] = 0;
  for (int i = 1; i < nn; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

  for (int i = 0; i < nn; ++i) a[i] = b[i] = complex<double>(0, 0);
  for (int i = 0; i < n; ++i) {
    a[A[i]].real(a[A[i]].real() + 1);
    b[B[i]].real(b[B[i]].real() + 1);
  }

  /*
  cerr << endl;
  for (int i = 0; i <= max_a; ++i) cerr << a[i].real() << ' ';
  cerr << endl;
  for (int i = 0; i <= max_b; ++i) cerr << b[i].real() << ' ';
  cerr << endl;
  */

  fft(a, 1, nn, bit), fft(b, 1, nn, bit);
  for (int i = 0; i < nn; ++i) a[i] *= b[i];
  fft(a, -1, nn, bit);

  int end = min(max_a + max_b + 1, MAXN);
  // for (int i = 0; i < end; ++i) cerr << int(a[i].real() + 0.5) << ' ';
  // cerr << endl;

  cnt[0] = 0;
  for (int i = 1; i < end; ++i) cnt[i] = cnt[i - 1] + (a[i].real() + 0.5);
  // cerr << ans << '\n';
  for (int i = 0; i < n; ++i) ans += cnt[min(C[i] - 1, end - 1)];
  // cerr << ans << '\n';
}

inline void big() {
  static long long ans;
  ans = 0;
  gao_big(A, B, C, ans);
  gao_big(B, C, A, ans);
  gao_big(C, A, B, ans);
  io << 1LL * n * n * n - ans << '\n';
}

inline void gao_small(int *A, int *B, int *C, long long &ans) {
  static int cnt[MAXN], maxx;
  maxx = -1;
  for (int i = 0; i < n; ++i)
    if (maxx < A[i]) maxx = A[i];
  memset(cnt, 0, sizeof(int) * (maxx + 1));
  for (int i = 0; i < n; ++i) ++cnt[A[i]];
  for (int i = maxx - 1; i; --i) cnt[i] += cnt[i + 1];
  for (int i = 0, j; i < n; ++i)
    for (j = 0; j < n; ++j)
      if (B[i] + C[j] < maxx) ans += cnt[B[i] + C[j] + 1];
}

inline void small() {
  static long long ans;
  ans = 0;
  gao_small(A, B, C, ans);
  gao_small(B, A, C, ans);
  gao_small(C, A, B, ans);
  io << 1LL * n * n * n - ans << '\n';
}

inline void solve() {
  io >> n;
  for (int i = 0; i < n; ++i) io >> A[i];
  for (int i = 0; i < n; ++i) io >> B[i];
  for (int i = 0; i < n; ++i) io >> C[i];
  if (n <= 1000) {
    small();
  } else {
    big();
  }
}

int main() {
  int o_o, v_v;
  for (io >> o_o, v_v = 1; v_v <= o_o; ++v_v) {
    io << "Case #" << v_v << ": ";
    solve();
  }
}
