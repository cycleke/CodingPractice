#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int MOD = 998244353;
const int MAX_N = 1e5 + 5;
const int MAX_LENGTH = 1e6 + 3;
const int BASE = 239;

string str[MAX_N];
map<ull, int> cnt[MAX_LENGTH];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string &s = str[i];
    cin >> s;
    int length = s.length();
    ull hash = 0, p = 1;
    for (int j = 1; j <= length; ++j, p *= BASE) {
      hash += p * (s[length - j] - 'a');
      ++cnt[j][hash];
    }
  }

  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    static int next[MAX_LENGTH], f[MAX_LENGTH];
    const string &s = str[i];
    const int length = s.length();
    ull hash = s[0] - 'a';
    next[0] = -1;
    f[0] = cnt[1][hash];
    for (int j = 1, k = -1; j < length; ++j) {
      while ((~k) && s[k + 1] != s[j]) k = next[k];
      next[j] = (s[k + 1] == s[j]) ? ++k : k;
      hash = hash * BASE + s[j] - 'a';
      f[j] = cnt[j + 1][hash];
      if (~next[j]) f[next[j]] -= f[j];
    }
    for (int j = 0; j < length; ++j)
      ans = (ans + 1ll * (j + 1) * (j + 1) % MOD * f[j]) % MOD;
  }
  cout << ans << "\n";

  return 0;
}
