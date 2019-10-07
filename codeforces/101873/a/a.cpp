#include <bits/stdc++.h>
using namespace std;

const int MAXX = 1000;

vector<int> blue[MAXX * 2 + 1], red[MAXX * 2 + 1];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(6);


  int n;
  cin >> n;
  for (int i = 0, x, y, c; i < n; ++i) {
    cin >> x >> y >> c;
    if (c == 1) {
      blue[x + MAXX].push_back(y);
    } else if (c == 2) {
      red[x + MAXX].push_back(y);
    }
  }

  static vector<pair<double, double>> ans;

  ans.clear();
  ans.emplace_back(-1001, 1001);
  for (int x = -MAXX; x <= MAXX; ++x) {
    auto &v = blue[x + MAXX];
    if (v.empty()) continue;

    if (x & 1) {
      double xx = x + 0.02;
      sort(v.begin(), v.end(), greater<int>());
      ans.emplace_back(xx, 1001);
      for (int y : v) {
        ans.emplace_back(xx, y + 0.01);
        ans.emplace_back(x - 0.01, y + 0.01);
        ans.emplace_back(x - 0.01, y - 0.01);
        ans.emplace_back(xx, y - 0.01);
      }
      ans.emplace_back(xx, -1000.1);
      ans.emplace_back(x + 0.03, -1000.1);
      ans.emplace_back(x + 0.03, 1001);
    } else {
      double xx = x - 0.02;
      sort(v.begin(), v.end());
      ans.emplace_back(x - 0.03, 1001);
      ans.emplace_back(x - 0.03, -1000.1);
      ans.emplace_back(xx, -1000.1);
      for (int y : v) {
        ans.emplace_back(xx, y - 0.01);
        ans.emplace_back(x + 0.01, y - 0.01);
        ans.emplace_back(x + 0.01, y + 0.01);
        ans.emplace_back(xx, y + 0.01);
      }
      ans.emplace_back(xx, 1001);
    }
  }
  ans.emplace_back(1001, 1001);
  ans.emplace_back(1001, 1002);

  cout << ans.size() << '\n';
  for (auto p : ans) cout << p.first << ' ' << p.second << '\n';

  ans.clear();
  ans.emplace_back(-1001, -1001);
  for (int x = -MAXX; x <= MAXX; ++x) {
    auto &v = red[x + MAXX];
    if (v.empty()) continue;

    if (x & 1) {
      double xx = x - 0.02;
      sort(v.begin(), v.end(), greater<int>());
      ans.emplace_back(x - 0.03, -1001);
      ans.emplace_back(x - 0.03, 1000.1);
      ans.emplace_back(xx, 1000.1);
      for (int y : v) {
        ans.emplace_back(xx, y + 0.01);
        ans.emplace_back(x + 0.01, y + 0.01);
        ans.emplace_back(x + 0.01, y - 0.01);
        ans.emplace_back(xx, y - 0.01);
      }
      ans.emplace_back(xx, -1001);
    } else {
      double xx = x + 0.02;
      sort(v.begin(), v.end());
      ans.emplace_back(xx, -1001);
      for (int y : v) {
        ans.emplace_back(xx, y - 0.01);
        ans.emplace_back(x - 0.01, y - 0.01);
        ans.emplace_back(x - 0.01, y + 0.01);
        ans.emplace_back(xx, y + 0.01);
      }
      ans.emplace_back(xx, 1000.1);
      ans.emplace_back(x + 0.03, 1000.1);
      ans.emplace_back(x + 0.03, -1001);
    }
  }
  ans.emplace_back(1001, -1001);
  ans.emplace_back(1001, -1002);

  cout << ans.size() << '\n';
  for (auto p : ans) cout << p.first << ' ' << p.second << '\n';


  return 0;
}
