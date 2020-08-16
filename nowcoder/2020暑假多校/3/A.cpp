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

void prework() {}

const int MAXN = 2e6;

char s[MAXN];

void solve() {
  int n;
  cin >> n >> s;
  int fish = 0, clam = 0;
  for (int i = 0; i < n; ++i) {
    int x = s[i] - '0';
    if (x & 2) {
      ++fish;
    } else if (x & 1) {
      ++clam;
    } else if (clam) {
      --clam;
      ++fish;
    }
  }
  cout << fish + clam / 2 << "\n";
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  prework();
  int o_o;
  for (cin >> o_o; o_o; --o_o) solve();
  return 0;
}
