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
  unordered_map<int, int> count;

  vi inc, dec;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    switch (count[x]) {
    case 0: {
      inc.push_back(x);
      count[x] = 1;
    } break;
    case 1: {
      dec.push_back(x);
      count[x] = 2;
    } break;
    default: {
      cout << "NO\n";
      return 0;
    } break;
    }
  }

  sort(inc.begin(), inc.end());
  sort(dec.begin(), dec.end(), greater<int>());

  cout << "YES\n";
  cout << inc.size() << "\n";
  for (int &x : inc) {
    cout << x << " ";
  }
  cout << "\n" << dec.size() << "\n";
  for (int &x : dec) {
    cout << x << " ";
  }
  return 0;
}
