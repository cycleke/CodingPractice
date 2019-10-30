#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e7 + 5;

char s[MAXN], str[MAXN];
int nxt[MAXN];

void get_next(char *S, int *nxt, int n) {
  nxt[0] = -1;
  int j = -1;
  for (int i = 1; i < n; ++i) {
    while ((~j) && S[j + 1] != S[i]) j = nxt[j];
    nxt[i] = (S[j + 1] == S[i]) ? (++j) : j;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long long a, b;
  while (cin >> a >> b >> s) {
    int n = strlen(s), m = 0;
    for (int i = n - 1; ~i; --i) {
      if (s[i] == '.') break;
      str[m++] = s[i];
    }
    get_next(str, nxt, m);

    long long ans = a - b;
    for (int i = 1; i < m; ++i) {
      ans = max(ans, a * (i + 1) - b * (i - nxt[i]));
      // cout << nxt[i] << ' ';
    }
    cout << ans << '\n';
  }
  return 0;
}
