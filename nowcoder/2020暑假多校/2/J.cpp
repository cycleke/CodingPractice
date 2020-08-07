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

const int MAXN = 1e5 + 5;

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;

  static int pk[MAXN], p[MAXN];
  for (int i = 1; i <= n; ++i) cin >> pk[i];

  for (int i = 1; i <= n; ++i) {
    static bool vis[MAXN];
    if (vis[i]) continue;

    static int a[MAXN], b[MAXN];
    int cnt = 0;
    for (int x = i; !vis[x]; x = pk[x]) {
      vis[x] = true;
      a[cnt++] = x;
    }

    for (int i = 0; i < cnt; ++i) b[1LL * i * k % cnt] = a[i];

    p[b[cnt - 1]] = b[0];
    for (int i = 1; i < cnt; ++i) p[b[i - 1]] = b[i];
  }

  for (int i = 1; i <= n; ++i) cout << p[i] << " ";
  cout << "\n";

  return 0;
}
