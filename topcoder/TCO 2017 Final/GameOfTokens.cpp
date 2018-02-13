#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
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

class GameOfTokens {
public:
  int count(string pattern);
};

#define EP emplace
#define PB push_back
#define MK make_pair
#define ACCU accumulate
#define MSET(a, b) memset(a, b, sizeof(a))
#define MCPY(a, b) memcpy(a, b, sizeof(a))
#define SZ(a) int((a).size())
#define ALL(a) (a).begin(), (a).end()
#define INF 0x3f3f3f3f
#define IINF 0x3f3f3f3f3f3f3f3fll
#define EPS 1e-9
#define PI 3.1415926535897932384626
#define MOD 1000000007
#define FOR_IN(i, a) for (auto i : x)
#define REP(i, l, r) for (int i = (l); i < (r); ++i)
#define QREP(i, l, r) for (int i = (l); i <= (r); ++i)
#define PER(i, l, r) for (int i = (r)-1; i >= (l); --i)
#define QPER(i, l, r) for (int i = (r); i >= (l); --i)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

//Head File

int f[107][10107], g[107][10107], n, n2;

void Update(int p, int q, int r) {
  int &x = f[p + n][q + n2];
  x += r;
  if (x >= MOD)
    x -= MOD;
}

int GameOfTokens::count(string pattern) {
  reverse(ALL(pattern));
  MSET(f, 0);
  n = SZ(pattern);
  n2 = n * n;
  f[n][n2] = 1;
  REP (i, 0, n) {
    MCPY(g, f);
    MSET(f, 0);
    REP (j, 0, (n << 1) | 1)
      REP (k, 0, (n2 << 1) | 1)
      if (g[j][k] != 0) {
        int cnt = j - n, ret = k - n2;
        if (pattern[i] == 'A' || pattern[i] == '?')
          Update(max(cnt + 1, 0), ret, g[j][k]);
        if (pattern[i] == 'B' || pattern[i] == '?')
          Update(min(cnt - 1, 0), ret, g[j][k]);
        if (pattern[i] == '.' || pattern[i] == '?')
          Update(cnt, ret + cnt, g[j][k]);
      }
  }
  int ans = 0;
  REP (j, 0, (n << 1) | 1)
    REP (k, n2 + 1, (n2 << 1) | 1) {
    ans += f[j][k];
    if (ans >= MOD)
      ans -= MOD;
  }
  return ans;
}

// CUT begin
ifstream data("GameOfTokens.sample");

string next_line() {
  string s;
  getline(data, s);
  return s;
}

template <typename T> void from_stream(T &t) {
  stringstream ss(next_line());
  ss >> t;
}

void from_stream(string &s) {
  s = next_line();
}

template <typename T>
string to_string(T t) {
  stringstream s;
  s << t;
  return s.str();
}

string to_string(string t) {
  return "\"" + t + "\"";
}

bool do_test(string pattern, int __expected) {
  time_t startClock = clock();
  GameOfTokens *instance = new GameOfTokens();
  int __result = instance->count(pattern);
  double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
  delete instance;

  if (__result == __expected) {
    cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
    return true;
  }
  else {
    cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
    cout << "           Expected: " << to_string(__expected) << endl;
    cout << "           Received: " << to_string(__result) << endl;
    return false;
  }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
  int cases = 0, passed = 0;
  while (true) {
    if (next_line().find("--") != 0)
      break;
    string pattern;
    from_stream(pattern);
    next_line();
    int __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if ( do_test(pattern, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1518514457;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(2);
  set<int> cases;
  bool mainProcess = true;
  for (int i = 1; i < argc; ++i) {
    if ( string(argv[i]) == "-") {
      mainProcess = false;
    } else {
      cases.insert(atoi(argv[i]));
    }
  }
  if (mainProcess) {
    cout << "GameOfTokens (450 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
