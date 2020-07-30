#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
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

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string a, b;
  while (cin >> a >> b) {
    int n = a.length(), m = b.length();
    int total = n + m - __gcd(n, m);
    bool is_equal = true;
    for (int i = 0, j = 0, step = 0; step < total; ++step) {
      if (a[i] != b[j]) {
        cout << (a[i] < b[j] ? "<\n" : ">\n");
        is_equal = false;
        break;
      }
      ++i == n ? (i = 0) : 1;
      ++j == m ? (j = 0) : 1;
    }
    if (is_equal) cout << "=\n";
  }

  return 0;
}
