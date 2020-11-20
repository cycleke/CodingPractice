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

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

const int MAXM = int(1e6) + 5;

int c[MAXM], f[MAXM][5][3];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    c[x]++;
  }

  for (int i = 1; i <= m; i++) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 3; k++) {
        for (int o = 0; o < 3; o++) {
          if (j + o > c[i]) {
            continue;
          }
          f[i + 1][k + o][o] =
              max(f[i + 1][k + o][o], f[i][j][k] + o + (c[i] - o - j) / 3);
        }
      }
    }
  }
  cout << f[m + 1][0][0] << endl;

  return 0;
}
