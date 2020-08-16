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

const int MAX_LENGTH = 2e6 + 3;

char s[MAX_LENGTH];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int q, x, it = 0, n;
  cin >> s >> q;
  n = strlen(s);
  for (char c; q; --q) {
    cin >> c >> x;
    switch (c) {
    case 'M': {
      it = (it + x + n) % n;
      break;
    }
    case 'A': {
      cout << s[(it + x - 1) % n] << "\n";
      break;
    }
    default: assert(0); break;
    }
  }

  return 0;
}
