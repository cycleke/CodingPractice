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

class MinDegreeSubgraph {
public:
  string exists(int n, long long m, int k);
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

string MinDegreeSubgraph::exists(int n, long long m, int k) {
  if (n <= k || m < k * (k + 1ll) / 2) return "NONE";
  if ((n * 2ll - k) * (k - 1) / 2 >= m) return "SOME";
  return "ALL";
}

// CUT begin
ifstream data("MinDegreeSubgraph.sample");

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

bool do_test(int n, long long m, int k, string __expected) {
    time_t startClock = clock();
    MinDegreeSubgraph *instance = new MinDegreeSubgraph();
    string __result = instance->exists(n, m, k);
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
        int n;
        from_stream(n);
        long long m;
        from_stream(m);
        int k;
        from_stream(k);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536017751;
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
        cout << "MinDegreeSubgraph (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
