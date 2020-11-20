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

  int n;
  cin >> n;

  int cnt[101];
  memset(cnt, 0, sizeof cnt);

  int unique_cnt = 0;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    unique_cnt += cnt[a] == 0;
    cnt[a]++;
  }
  if (unique_cnt == 2) {
    cout << n << endl;
    return 0;
  }

  int dp[101][10001];
  memset(dp, 0, sizeof dp);
  dp[0][0] = 1;
  for (int i = 0; i < 100; i++) {
    for (int j = i; j >= 0; j--) {
      for (int k = 10000; k >= 0; k--) {
        if (dp[j][k] == 0)
          continue;
        for (int o = cnt[i + 1]; o >= 1; o--) {
          int &t = dp[j + o][k + o * (i + 1)];
          t += dp[j][k];
          if (t > 2)
            t = 2;
        }
      }
    }
  }

  for (int i = 100; i >= 0; i--) {
    for (int j = 1; j <= 100; j++) {
      if (cnt[j] < i || dp[i][i * j] != 1)
        continue;
      cout << i << endl;
      return 0;
    }
  }
  return 0;
}
