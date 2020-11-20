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

const int MAXN = 1003;

int a[MAXN][MAXN];
int c1[MAXN], c2[MAXN], b[MAXN];
int r1[MAXN][MAXN], r2[MAXN][MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      b[j] = a[i][j];
    }
    sort(b, b + m);
    int *end = unique(b, b + m);
    c1[i] = end - b;
    for (int j = 0; j < m; j++) {
      r1[i][j] = lower_bound(b, end, a[i][j]) - b + 1;
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      b[j] = a[j][i];
    }
    sort(b, b + n);
    int *end = unique(b, b + n);
    c2[i] = end - b;
    for (int j = 0; j < n; j++) {
      r2[j][i] = lower_bound(b, end, a[j][i]) - b + 1;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << max(r1[i][j], r2[i][j]) + max(c1[i] - r1[i][j], c2[j] - r2[i][j])
           << " ";
    }
    cout << endl;
  }

  return 0;
}
