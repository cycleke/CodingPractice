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

int n;
vi ids;
vector<string> strs;

bool gen_ans(vi &ans, const string &whole_string) {
  vvi l(n);
  for (int i = 0; i < 2 * n - 2; i++) {
    const string &str = strs[i];
    const int length = str.length();
    ans[i] = 0;
    if (str == whole_string.substr(0, length)) {
      ans[i] ^= 1;
    }
    if (str == whole_string.substr(n - length, length)) {
      ans[i] ^= 2;
    }
    if (ans[i] == 0) {
      return false;
    }
    l[length].push_back(i);
  }
  for (int i = 1; i < n; i++) {
    int &a1 = ans[l[i][0]];
    int &a2 = ans[l[i][1]];
    if (a1 ^ a2)
      continue;
    if (a1 != 3)
      return false;
    a1 = 1;
    a2 = 2;
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;

  for (int i = 0; i < 2 * n - 2; i++) {
    string str;
    cin >> str;
    strs.push_back(str);
    if (int(str.length()) == n - 1)
      ids.push_back(i);
  }

  if (n == 2) {
    cout << "PS" << endl;
    return 0;
  }

  vi ans(2 * n - 2);
  string s1 = strs[ids[0]];
  string s2 = strs[ids[1]];
  string whole_string;
  if (s1.substr(1) == s2.substr(0, n - 2)) {
    whole_string = s1 + s2.substr(n - 2);
    if (gen_ans(ans, whole_string)) {
      for (auto i : ans) {
        if (i == 1)
          cout << "P";
        else
          cout << "S";
      }
      cout << endl;
      return 0;
    }
  }
  if (s2.substr(1) == s1.substr(0, n - 2)) {
    whole_string = s2 + s1.substr(n - 2);
    if (gen_ans(ans, whole_string)) {
      for (auto i : ans) {
        if (i == 1)
          cout << "P";
        else
          cout << "S";
      }
      cout << endl;
      return 0;
    }
  }
  return 0;
}
