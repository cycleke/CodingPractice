#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

char s[MAXN], t[MAXN];
vector<int> pos1, pos2;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, cnt1 = 0, cnt2 = 0;
  cin >> n >> s >> t;

  for (int i = 0; i < n; ++i) {
    cnt1 += (s[i] == 'a') + (t[i] == 'a');
    cnt2 += (s[i] == 'b') + (t[i] == 'b');
  }

  if ((cnt1 & 1) || (cnt2 & 1)) {
    cout << "-1\n";
    return 0;
  }

  for (int i = 0; i < n; ++i) {
    if (s[i] == 'a' && t[i] == 'b') pos1.push_back(i + 1);
    if (s[i] == 'b' && t[i] == 'a') pos2.push_back(i + 1);
  }

  cout << pos1.size() / 2 + pos2.size() / 2 + pos1.size() % 2 * 2 << '\n';
  for (size_t i = 0; i + 1 < pos1.size(); i += 2)
    cout << pos1[i + 1] << ' ' << pos1[i] << '\n';
  for (size_t i = 0; i + 1 < pos2.size(); i += 2)
    cout << pos2[i + 1] << ' ' << pos2[i] << '\n';

  if (pos1.size() & 1) {
    cout << pos2.back() << ' ' << pos2.back() << '\n';
    cout << pos1.back() << ' ' << pos2.back() << '\n';
  }

  return 0;
}
