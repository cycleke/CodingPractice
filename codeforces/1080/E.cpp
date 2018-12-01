#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;

const int INF = 0x3ffffff;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;
  int a[n][m];
  for (int i = 0; i < n; i++) {
    char s[m + 1];
    cin >> s;
    for (int j = 0; j < m; j++) {
      a[i][j] = s[j] - 'a';
    }
  }

  ll ans = 0;
  int t[n], c[n][26], b[n * 2 + 3][26], r[n * 2 + 3];
  for (int j = 0; j < m; j++) {
    memset(t, 0, sizeof t);
    memset(c, 0, sizeof c);
    memset(b, 0, sizeof b);
    for (int k = j; k < m; k++) {
      int cnt = 0;
      for (int i = 0; i < n; i++) {
        t[i] ^= 1 << a[i][k];
        c[i][a[i][k]]++;
        if (!(t[i] & (t[i] - 1))) {
          memcpy(b[i * 2 + 2], c[i], sizeof c[i]);
        } else {
          b[i * 2 + 2][0] = 0x3f3f3f3f + cnt++;
        }
      }

      memset(b[0], 1, sizeof b[0]);
      memset(b[n * 2 + 2], 2, sizeof b[n * 2 + 2]);

      int l = 2 * n + 1, mx = 0, c = 0;
      for (int i = 1; i <= l; i++) {
        r[i] = (i < mx) ? min(r[2 * c - i], mx - i) : 1;
        while (!memcmp(b[i + r[i]], b[i - r[i]], sizeof b[0])) {
          r[i]++;
        }
        if (i + r[i] > mx) {
          mx = i + r[i];
          c = i;
        }
      }
      for (int i = 0; i < n; i++) {
        if (!(t[i] & (t[i] - 1))) {
          ans += r[i * 2 + 2] / 2;
        }
      }
      for (int i = 1; i < 2 * n + 2; i += 2) {
        ans += r[i] / 2;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
