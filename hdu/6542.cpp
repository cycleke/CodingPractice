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

#define fi first
#define se second
#define pb push_back
#define mp make_pair

#define SZ(a) int((a).size())
#define ALL(a) (a).begin(), (a).end()
#define EXIST(s, x) ((s).find(x) != (s).end())
#define A_EXIST(a, x) (find(ALL(a), x) != (a).end())
#define ZERO(a) memset((a), 0, sizeof(a))

#define FOR(i, a, b) for (int i = int(a); i < int(b); ++i)
#define REP(i, a, b) for (int i = int(b) - 1; i >= a; --i)
#define FOR2(i, a, b, j, c, d) FOR(i, a, b) FOR(j, c, d)
#define REP2(i, a, b, j, c, d) REP(i, a, b) REP(j, c, d)
#define EACH(i, s) for (auto i = (s).begin(); i != (s).end(); ++i)
#define MUL_CASE                                                               \
  int o_o;                                                                     \
  cin >> o_o;                                                                  \
  for (int case_count = 0; case_count < o_o; ++case_count)
#define debug(...) fprintf(stderr, __VA_ARGS__)

const int INF = 0x3ffffff;
const ll LL_INF = 0x3fffffffffffffffll;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> u_int(begin, end);
// uniform_real_distribution<double> u_read(begin, end);
/* -- HEAD END -- */

int c[3][9], w[7];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  FOR(i, 0, 14) {
    string s;
    cin >> s;
    if (isdigit(s[0])) {
      switch (s[1]) {
      case 's':
        ++c[0][s[0] - '1'];
        break;
      case 'p':
        ++c[1][s[0] - '1'];
        break;
      case 'w':
        ++c[2][s[0] - '1'];
        break;
      }
    } else {
      if (s == "dong") {
        ++w[0];
      } else if (s == "nan") {
        ++w[1];
      } else if (s == "xi") {
        ++w[2];
      } else if (s == "bei") {
        ++w[3];
      } else if (s == "zhong") {
        ++w[4];
      } else if (s == "fa") {
        ++w[5];
      } else if (s == "bai") {
        ++w[6];
      }
    }
  }

  if ((c[0][0] && c[0][8] && c[1][0] && c[1][8] && c[2][0] && c[2][8] && w[0] &&
       w[1] && w[2] && w[3] && w[4] && w[5] && w[6]) &&
      (c[0][0] > 1 || c[0][8] > 1 || c[1][0] > 1 || c[1][8] > 1 ||
       c[2][0] > 1 || c[2][8] > 1 || w[0] > 1 || w[1] > 1 || w[2] > 1 ||
       w[3] > 1 || w[4] > 1 || w[5] > 1 || w[6] > 1)) {
    cout << "shisanyao!\n";
  } else {
    bool flag = false;
    FOR(i, 0, 3) {
      if (accumulate(c[i], c[i] + 9, 0) != 14) {
        continue;
      }
      flag = c[i][0] >= 3 && c[i][8] >= 3;
      FOR(j, 1, 8) { flag &= c[i][j] >= 1; }
      if (flag) {
        break;
      }
    }
    if (flag) {
      cout << "jiulianbaodeng!\n";
    } else {
      cout << "I dont know!\n";
    }
  }

  return 0;
}
