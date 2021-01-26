#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

#define debug(...) // fprintf(stderr, __VA_ARGS__)

int dig[20], cnt;
ull dp[2][21][2][1 << 16 | 1]; // h/d position leading mask

ull gao(int d, int pos, bool leading, int mask, bool limit) {
  if (pos == 0) return !leading;
  if (!limit && dp[d][pos][leading][mask] != -1ULL) {
    debug("# %d %d %d %d %llu\n", d, pos, leading, mask,
          dp[d][pos][leading][mask]);
    return dp[d][pos][leading][mask];
  }
  ull cur = 0;
  int bound = limit ? dig[pos] : (d ? 9 : 15);
  for (int i = 0; i <= bound; ++i) {
    if (mask >> i & 1) continue;
    cur +=
        gao(d, pos - 1, leading && i == 0,
            (leading && i == 0) ? 0 : (mask | (1 << i)), limit && i == bound);
  }
  if (!limit) dp[d][pos][leading][mask] = cur;
  return cur;
}

ull calc(ull x, char d) {
  int base = d == 'd' ? 10 : 16;
  for (cnt = 0; x; x /= base) dig[++cnt] = x % base;
  return gao(d == 'd', cnt, true, 0, true);
}

void solve() {
  char d;
  int type;
  cin >> d >> type;
  auto base = d == 'd' ? dec : hex;
  if (type == 0) {
    ull a, b;
    cin >> base >> a >> b;
    cout << base << calc(b, d) - (a == 0 ? -1 : calc(a - 1, d)) << "\n";
  } else {
    ull ith;
    cin >> base >> ith;
    --ith;
    ull l = 0, r = -1;
    if (ith == 0) {
      cout << "0\n";
    } else if (calc(r, d) < ith) {
      cout << "-\n";
    } else {
      while (r - l > 1) {
        ull mid = (l >> 1) + (r >> 1) + ((l & 1) & (r & 1));
        (calc(mid, d) < ith) ? l = mid : r = mid;
      }
      cout << base << r << "\n";
    }
  }
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  memset(dp, -1, sizeof(dp));
  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
