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

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int h1, m1, s1, h2, m2, s2;
  scanf("%d:%d:%d", &h1, &m1, &s1);
  scanf("%d:%d:%d", &h2, &m2, &s2);

  int c1 = h1 * 60 * 60 + m1 * 60 + s1;
  int c2 = h2 * 60 * 60 + m2 * 60 + s2;
  cout << abs(c1 - c2) << "\n";

  return 0;
}
