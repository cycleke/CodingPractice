#include <cstdio>

inline char gc() {
  static char b[1 << 16], *s = b, *e = b;
  if (s == e) e = (s = b) + fread(b, 1, 1 << 16, stdin);
  return (s == e) ? EOF : *s++;
}

inline void gi(int &a) {
  static int c;
  while (c = gc(), c < '0');
  a = c - '0';
  while (c = gc(), '-' < c)
    a = (a << 3) + (a << 1) + c - '0';
}

int c[2048699], seg;

inline void add(int x) {
  if (c[x += ::seg])
    return;
  for (; x; x >>= 1)
    ++c[x];
}
inline void del(int x) {
  if (!c[x += ::seg])
    return;
  for (; x; x >>= 1)
    --c[x];
}
inline int gmin() {
  if (!c[1])
    return 0;
  static int x;
  for (x = 1; x <= ::seg; x = (c[x << 1] ? x << 1 : x << 1 | 1));
  return x - ::seg;
}
inline int gmax() {
  if (!c[1])
    return 0;
  static int x;
  for (x = 1; x <= ::seg; x = (c[x << 1 | 1] ? x << 1 | 1 : x << 1));
  return x - ::seg;
}
inline int pred(int x) {
  for (x += ::seg; x ^ 1; x >>= 1)
    if ((x & 1) && c[x >> 1] > c[x]) break;
  if (x == 1) return 0;
  for (x ^= 1; x <= ::seg; x = (c[x << 1 | 1] ? x << 1 | 1 : x << 1));
  return x - ::seg;
}
inline int succ(int x) {
  for (x += ::seg; x ^ 1; x >>= 1)
    if ((~x & 1) && c[x >> 1] > c[x]) break;
  if (x == 1) return 0;
  for (x ^= 1; x <= ::seg; x = (c[x << 1] ? x << 1 : x << 1 | 1));
  return x - ::seg;
}

int main() {
  int n, m, opt, x;
  gi(n), gi(m);
  for (::seg = 1; ::seg <= n; ::seg <<= 1);
  while (m--) {
    gi(opt);
    if ((opt ^ 3) && (opt ^ 4))
      gi(x), ++x;
    if (opt == 1) add(x);
    else if (opt == 2) del(x);
    else if (opt == 3) printf("%d\n", gmin() - 1);
    else if (opt == 4) printf("%d\n", gmax() - 1);
    else if (opt == 5) printf("%d\n", pred(x) - 1);
    else if (opt == 6) printf("%d\n", succ(x) - 1);
    else puts(c[x + ::seg] ? "1" : "-1");
  }
}
