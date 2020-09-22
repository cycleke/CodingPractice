#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

const int STEPS = 5e3;

inline int mmul(int a, int b, int mod) { return 1ll * a * b % mod; }

inline int mpow(int a, int b, int mod) {
  int res = 1;
  for (; b; b >>= 1, a = mmul(a, a, mod)) (b & 1) && (res = mmul(res, a, mod));
  return res;
}

inline bool check(int x, int p) {
  if (!(x % p) || (mpow(p % x, x - 1, x) ^ 1)) return false;
  int k = x - 1, t;
  while (~k & 1) {
    if (((t = mpow(p % x, k >>= 1, x)) ^ 1) && (t ^ (x - 1))) return false;
    if (!(t ^ (x - 1))) return true;
  }
  return true;
}

inline bool Miller_Rabin(int x) {
  if (x < 2) return true;
  static const int p[12] = {2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251};
  for (int i = 0; i < 12; ++i) {
    if (!(x ^ p[i])) return true;
    if (!check(x, p[i])) return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  int T, l, r;
  for (cin >> T; T; --T) {
    cin >> l >> r;
    int len = r - l + 1, cnt = 0;
    if (len <= STEPS) {
      for (int i = l; i <= r; ++i) cnt += Miller_Rabin(i);
      cout << (3 * cnt < len ? "Yes\n" : "No\n");
    } else {
      static mt19937 rnd(
          chrono::high_resolution_clock::now().time_since_epoch().count());
      for (int i = 0; i < STEPS; ++i) {
        int x = rnd() % (len + 1) + l;
        cnt += Miller_Rabin(x);
      }
      cout << (3 * cnt < STEPS ? "Yes\n" : "No\n");
    }
  }

  return 0;
}
