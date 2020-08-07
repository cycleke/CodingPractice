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

const int MAXN = 5e3 + 3;

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, m, k;
  cin >> n >> m >> k;

  static int a[MAXN][MAXN];
  static bool mark[MAXN][MAXN];

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      if (mark[i][j]) continue;
      int ij = i * j;
      for (int _i = i, _j = j, _ij = ij; _i <= n && _j <= m;
           _i += i, _j += j, _ij += ij)
        mark[_i][_j] = true, a[_i][_j] = _ij;
    }

  static int left_k[MAXN][MAXN], q[MAXN];
  int head, tail;

  for (int i = 1; i <= n; ++i) {
    head = tail = 0;
    int *arr = a[i], *left = left_k[i];

    for (int j = 1; j <= k; ++j) {
      while (head < tail && arr[q[tail - 1]] <= arr[j]) --tail;
      q[tail++] = j;
    }
    left[k] = arr[q[head]];
    for (int j = k + 1; j <= m; ++j) {
      if (j - q[head] >= k) ++head;
      while (head < tail && arr[q[tail - 1]] <= arr[j]) --tail;
      q[tail++] = j;
      left[j] = arr[q[head]];
    }
  }

  ll ans = 0;
  for (int j = k; j <= m; ++j) {
    head = tail = 0;
    for (int i = 1; i <= k; ++i) {
      while (head < tail && left_k[q[tail - 1]][j] <= left_k[i][j]) --tail;
      q[tail++] = i;
    }
    ans += left_k[q[head]][j];
    for (int i = k + 1; i <= n; ++i) {
      if (i - q[head] >= k) ++head;
      while (head < tail && left_k[q[tail - 1]][j] <= left_k[i][j]) --tail;
      q[tail++] = i;
      ans += left_k[q[head]][j];
    }
  }

  cout << ans << "\n";

  return 0;
}
