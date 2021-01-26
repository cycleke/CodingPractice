#include <bits/stdc++.h>
using namespace std;

string mm[13], dd[32];
unordered_map<string, int> month, day;

void init() {
  mm[1] = "Jan", mm[2] = "Feb", mm[3] = "Mar", mm[4] = "Apr", mm[5] = "May",
  mm[6] = "Jun", mm[7] = "Jul", mm[8] = "Aug", mm[9] = "Sept", mm[10] = "Oct",
  mm[11] = "Nov", mm[12] = "Dec";
  for (int i = 1; i <= 12; ++i) month[mm[i]] = i;

  for (int i = 1; i < 32; ++i) dd[i] = to_string(i) + "th";
  dd[1] = "1st", dd[2] = "2nd", dd[3] = "3rd", dd[21] = "21st", dd[22] = "22nd",
  dd[23] = "23rd", dd[31] = "31st";
  for (int i = 1; i < 32; ++i) day[dd[i]] = i;
}

void solve() {
  static string s1, s2;
  static set<pair<int, int>> s;

  int n;
  s.clear();
  for (cin >> n; n; --n) {
    cin >> s1 >> s2;
    s.emplace(month[s1], day[s2]);
  }

  cin >> s1 >> s2;
  auto p = make_pair(month[s1], day[s2]);
  auto it = s.upper_bound(p);
  if (it != s.end()) {
    cout << mm[it->first] << " " << dd[it->second] << "\n";
  } else {
    cout << "See you next year\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  init();
  int o_o, step = 0;
  for (cin >> o_o; step < o_o; solve()) cout << "Case #" << ++step << ": ";

  return 0;
}
