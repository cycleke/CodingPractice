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

  int o_o;
  cin >> o_o;
  while (o_o--) {
    string str;
    cin >> str;
    int n = str.length();
    if (n > 26) {
      cout << "No\n";
      continue;
    }
    vi a;
    for (int i = 0; i < n; ++i) {
      a.push_back(str[i] - 'a');
    }
    sort(a.begin(), a.end());

    bool flag = true;
    for (int i = 1; i < n; ++i) {
      if (a[i] != a[i - 1] + 1) {
        flag = false;
        break;
      }
    }
    cout << (flag ? "Yes\n" : "No\n");
  }

  return 0;
}
