#include <cstdio>

int s[2][30000032];
const int BASE = 33554432;
int tr[BASE * 2 + 5];

#define getchar_unlocked getchar

inline void get_int(int &a) {
  register char c;
  register char sign = 0;
  do {
    c = getchar_unlocked();
    if (c == '-') sign = 1;
  } while (c < 48);
  a = c ^ 48;
  while (47 < (c = getchar_unlocked()))
    a = (a << 3) + (a << 1) + (c ^ 48);
  if (sign) a = -a;
}

int main() {
  int n;
  get_int(n);
  scanf("%*d %*d %*d");
  for (int step = 0; step < n; ++step) {
    int operation;
    get_int(operation);
    if (operation == 1) {
      int k, l, poi = 0;
      get_int(k);
      get_int(l);
      if (k < 0) {
        k = -k;
        poi = 1;
      }
      int r = l;
      while (k != 0) {
        s[poi][r] += k & 1;
        k >>= 1;
        ++r;
      }
      for (int i = l; i <= r; ++i) {
        s[poi][i + 1] += (s[poi][i] & 2) >> 1;
        s[poi][i] &= 1;
      }
      ++r;
      while ((s[poi][r] & 2) != 0) {
        s[poi][r++] &= 1;
        s[poi][r] += 1;
      }

      l += BASE;
      r += BASE;
      for (int i = l; i <= r; ++i)
        tr[i] = s[0][i - BASE] ^ s[1][i - BASE];
      l >>= 1;
      r >>= 1;
      while (l != 0) {
        for (int i = l; i <= r; ++i)
          tr[i] = tr[i << 1] | tr[i << 1 | 1];
        l >>= 1;
        r >>= 1;
      }

    } else {
      int k;
      get_int(k);
      int l = k, fg = 0;
      for (l += BASE; l != 0; l >>= 1) if ((l & tr[l ^ 1] & 1) != 0) {
          fg = 1;
          l ^= 1;
          for (; l < BASE; l = l << 1 | tr[l << 1 | 1]);
          break;
        }
      l -= BASE;
      if (fg == 0 || s[0][l] == 1) puts((s[0][k] ^ s[1][k]) != 0 ? "1" : "0");
      else puts((s[0][k] == s[1][k]) ? "1" : "0");
    }
  }
  return 0;
}
