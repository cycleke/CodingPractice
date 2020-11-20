#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e7 + 5;
const int MAXM = 100 + 5;
const unsigned BLOCK = 1 << 8;
const unsigned END_TAIL = BLOCK - 1;

unsigned a[MAXN], A, B, C, x, y, z, n, m, b[MAXM], c[BLOCK], ta[MAXN];
inline unsigned rng61() {
  unsigned t;
  x = x ^ (x << 16);
  x = x ^ (x >> 5);
  x = x ^ (x << 1);
  t = x;
  x = y;
  y = z;
  z = (t ^ x) ^ y;
  return z;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int i, shift, case_count = 0;
  while (cin >> n >> m >> A >> B >> C) {
    cout << "Case #" << ++case_count << ": ";
    x = A, y = B, z = C;
    for (i = 0; i ^ n; ++i) a[i] = rng61();

    for (shift = 0; shift ^ 32; shift += 8) {
      for (i = 0; i ^ BLOCK; ++i) c[i] = 0;
      for (i = 0; i ^ n; ++i) ++c[(a[i] >> shift) & END_TAIL];
      for (i = 1; i ^ BLOCK; ++i) c[i] += c[i - 1];
      for (i = n - 1; ~i; --i) ta[--c[(a[i] >> shift) & END_TAIL]] = a[i];
      for (i = 0; i ^ n; ++i) a[i] = ta[i];
    }

    for (; m; --m) {
      cin >> i;
      cout << a[i] << ' ';
    }
    cout << '\n';
  }

  return 0;
}
