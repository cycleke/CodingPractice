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

class SimpleMathProblemDiv2 {
public:
  long long calculate(int X);
};

#define EP emplace_back
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
#define FOREACH(i, a) for (auto i : x)
#define REP(i, l, r) for (int i = (l); i < (r); ++i)
#define QREP(i, l, r) for (int i = (l); i <= (r); ++i)
#define PER(i, l, r) for (int i = (r)-1; i >= (l); --i)
#define QPER(i, l, r) for (int i = (r); i >= (l); --i)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
//Head File

const int MAXX = 444778;

int fac[MAXX], prime[MAXX / 10];
bool vis[MAXX];

inline ll FastPow(ll a, int b) {
  ll res = 1;
  while (b) {
    if (b & 1) res *= a;
    b >>= 1;
    a *= a;
  }
  return res;
}

long long SimpleMathProblemDiv2::calculate(int X) {
  int pc = 0;
  for (int i = 2; i <= X; i++) {
    if (!vis[i]) {
      fac[i] = i;
      prime[pc++] = i;
    }
    for (int j = 0; prime[j] * i <= X; j++) {
      vis[prime[j] * i] = true;
      fac[prime[j] * i] = prime[j];
      if (prime[j] % i == 0) break;
    }
  }

  long long res = 0;
  QREP (i, 1, X) {
    int x = i, pre = -1;
    long long f = 0;
    while (x > 1) {
      if (pre != fac[x]) {
        pre = fac[x];
        //f += FastPow(pre, int(log(i) / log(pre)));
        ll t = pre;
        while (t * pre <= i) t *= pre;
        f += t;
      }
      x /= fac[x];
    }
    //cerr << i << " " << f << endl;
    res += f;
  }

  return res;
}

// CUT begin
ifstream data("SimpleMathProblemDiv2.sample");

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

bool do_test(int X, long long __expected) {
    time_t startClock = clock();
    SimpleMathProblemDiv2 *instance = new SimpleMathProblemDiv2();
    long long __result = instance->calculate(X);
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
        int X;
        from_stream(X);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541773233;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SimpleMathProblemDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
