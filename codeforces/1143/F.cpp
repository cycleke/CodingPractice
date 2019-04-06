#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;
typedef vector<pii> vpii;

#define SZ(a) int((a).size())
#define ALL(a) (a).begin(), (a).end()
#define EXIST(s, x) ((s).find(x) != (s).end())
#define A_EXIST(a, x) (find(ALL(a), x) != (a).end())

const int INF = 0x3ffffff;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

typedef pair<ll, ll> point;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  vector<point> p(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    p[i] = point(x, y - 1ll * x * x);
  }
  sort(ALL(p), greater<point>());
  vector<point> stk(n);
  int top = 0;
  for (int i = 0; i < n; ++i) {
    auto cross = [&](const point &o, const point &a, const point &b) {
      // vector cross : OA * OB
      return (a.first - o.first) * (b.second - o.second) -
             (a.second - o.second) * (b.first - o.first);
    };
    while (top >= 2 && cross(stk[top - 2], stk[top - 1], p[i]) <= 0) {
      --top;
    }
    stk[top++] = p[i];
  }
  while (top >= 2 && stk[top - 2].first == stk[top - 1].first) {
    --top;
  }
  cout << top - 1 << "\n";
  return 0;
}
