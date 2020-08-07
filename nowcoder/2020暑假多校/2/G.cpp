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

const int MAXN = 150000 + 3;
const int MAXM = 40000 + 3;

int a[MAXN], b[MAXM], ord[MAXM];
bitset<MAXM> cur, bs[MAXM];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < m; ++i) cin >> b[i];

  iota(ord, ord + m, 0);
  sort(ord, ord + m, [](int x, int y) { return b[x] < b[y]; });
  for (int i = 1; i <= m; ++i) {
    bs[i] = bs[i - 1];
    bs[i].set(ord[i - 1]);
  }
  int ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    cur >>= 1;

    static auto get_rank = [m](int x) {
      int l = 0, r = m;
      while (l < r) {
        int mid = (l + r) / 2;
        (x < b[ord[mid]]) ? r = mid : l = mid + 1;
      }
      return l;
    };

    cur &= bs[get_rank(a[i])];
    if (a[i] >= b[m - 1]) cur.set(m - 1);
    ans += cur[0];
  }
  cout << ans << "\n";

  return 0;
}
