#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;

int fib[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  fib[0] = fib[1] = 1;
  for (int i = 2; i < MAXN; ++i)
    fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;

  string s;
  cin >> s;
  int n = s.length();

  for (int i = 0; i < n; ++i)
    if (s[i] == 'm' || s[i] == 'w') {
      cout << "0\n";
      return 0;
    }

  int ans = 1;

  for (int i = 0, j; i < n; ++i) {
    if (s[i] != 'u' && s[i] != 'n') continue;
    j = i;
    while (j + 1 < n && s[j + 1] == s[i]) ++j;
    ans = 1LL * ans * fib[j - i + 1] % MOD;
    i = j;
  }
  cout << ans << '\n';
  return 0;
}
