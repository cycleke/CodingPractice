#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;

// const int INF = 0x3fffffff;
// const int MOD = 1e9 + 7;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int T;
  cin >> T;
  while (T--) {
    ll n, m;
    cin >> n >> m;
    ll x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    /*
      int d = min(y1, y3);
      int u = max(y2, y4);
      ll white = ceil(m * (d - 1) / 2) + ceil(m * (n - u) / 2);
      ll black = floor(m * (d - 1) / 2) + floor(m * (n - u) / 2);
    */

    auto Contain = [](ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x4,
                      ll y4) {
      return x1 <= x3 && y1 <= y3 && x2 >= x4 && y2 >= y4;
    };

    auto B = [](ll x1, ll y1, ll x2, ll y2) {
      ll t = (x2 - x1 + 1) * (y2 - y1 + 1);
      if (t % 2 == 0)
        return t / 2;
      else
        return t / 2 + ((x1 + y1) % 2 == 1 ? 1 : 0);
    };
    auto W = [](ll x1, ll y1, ll x2, ll y2) {
      ll t = (x2 - x1 + 1) * (y2 - y1 + 1);
      if (t % 2 == 0)
        return t / 2;
      else
        return t / 2 + ((x1 + y1) % 2 == 0 ? 1 : 0);
    };

    ll white = n * m / 2 + (n * m % 2 == 1 ? 1 : 0);
    if (x2 < x3 || x4 < x1 || y2 < y3 || y4 < y1) {
      // white += area1 / 2 - ceil(area2 / 2.0);
      white += B(x1, y1, x2, y2) - W(x3, y3, x4, y4);
    } else if (Contain(x1, y1, x2, y2, x3, y3, x4, y4)) {
      // white += area1 / 2 - area2;
      white += B(x1, y1, x2, y2) - (x4 - x3 + 1) * (y4 - y3 + 1);
    } else if (Contain(x3, y3, x4, y4, x1, y1, x2, y2)) {
      // white -= ceil(area2 / 2.0);
      white -= W(x3, y3, x4, y4);
    } else {
      ll a[4] = {x1, x2, x3, x4};
      ll b[4] = {y1, y2, y3, y4};
      sort(a, a + 4);
      sort(b, b + 4);
      ll x5 = a[1], x6 = a[2];
      ll y5 = b[1], y6 = b[2];
      // white += (area1 / 2 - area3 / 2) -
      //         (ceil(area2 / 2.0) - ceil(area3 / 2.0)) - ceil(area3 / 2.0);
      white += (B(x1, y1, x2, y2) - B(x5, y5, x6, y6)) -
               (W(x3, y3, x4, y4) - W(x5, y5, x6, y6)) - W(x5, y5, x6, y6);
    }
    cout << white << " " << n * m - white << endl;
  }

  return 0;
}
