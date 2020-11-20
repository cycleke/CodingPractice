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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  string s, t;
  cin >> n >> s >> t;
  char res[n + 1] = {};
  int a[n], x = 0;
  for (int i = n - 1; ~i; --i) {
    a[i] = (s[i] - 'a' + t[i] - 'a' + x);
    x = a[i] / 26;
    a[i] %= 26;
  }
  for (int i = 0; i < n; ++i) {
    res[i] = (a[i] + x * 26);
    x = res[i] % 2;
    res[i] = res[i] / 2 + 'a';
  }
  cout << res << "\n";
  return 0;
}
