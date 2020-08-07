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
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int MAXN = 2e3 + 5;

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  static pii p[MAXN];
  for (int i = 0; i < n; ++i) cin >> p[i].first >> p[i].second;

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    static map<pair<double, double>, int> count;
    count.clear();
    int x1 = p[i].first, y1 = p[i].second;
    ll l1 = x1 * x1 + y1 * y1;
    for (int j = 0; j < i; ++j) {
      int x2 = p[j].first, y2 = p[j].second;
      int cross = x1 * y2 - x2 * y1;
      if (cross == 0) continue;
      ll l2 = x2 * x2 + y2 * y2;
      double x = 1.0 * (y1 * l2 - y2 * l1) / cross;
      double y = 1.0 * (x2 * l1 - x1 * l2) / cross;
      ans = max(ans, ++count[make_pair(x, y)]);
    }
  }
  cout << ans + 1 << "\n";

  return 0;
}
