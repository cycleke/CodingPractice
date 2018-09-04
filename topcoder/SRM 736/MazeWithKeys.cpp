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

class MazeWithKeys {
public:
  int startingPoints(vector<string> a);
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

int MazeWithKeys::startingPoints(vector<string> a) {
  int n = a.size();
  int m = a[0].size();
  int ans = 0;

  auto Check = [&](int sx, int sy, bool use_door) {
                 static int door[26];
                 static bool vis[50][50], have_key[26];
                 MSET(vis, 0);
                 MSET(door, -1);
                 MSET(have_key, 0);

                 queue<int> Q;
                 Q.push(sx << 6 | sy);
                 while (!Q.empty()) {
                   int cx = Q.front() >> 6;
                   int cy = Q.front() & 63;
                   Q.pop();
                   if (a[cx][cy] == '*') return true;
                   if (vis[cx][cy]) continue;
                   vis[cx][cy] = true;
                   static const int d[] = {1, 0, -1, 0};
                   for (int i = 0; i < 4; i++) {
                     int dx = cx + d[i];
                     int dy = cy + d[i^1];
                     if (dx < 0 || dx >= n || dy < 0 || dy >= m) continue;
                     if (vis[dx][dy] || a[dx][dy] == '#') continue;
                     const char &ch = a[dx][dy];
                     if (ch >= 'A' && ch <= 'Z') {
                       door[ch - 'A'] = dx << 6 | dy;
                       if (use_door && have_key[ch - 'A']) Q.push(dx << 6 | dy);
                     } else {
                       if (ch >= 'a' && ch <= 'z') {
                         have_key[ch - 'a'] = true;
                         if (use_door && ~door[ch - 'a']) Q.push(door[ch - 'a']);
                       }
                       Q.push(dx << 6 | dy);
                     }
                   }
                 }
                 return false;
               };

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      if (a[i][j] == '.' && !Check(i, j, 0) && Check(i, j, 1)) ans++;
    }
  return ans;
}

// CUT begin
ifstream data("MazeWithKeys.sample");

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

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
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

bool do_test(vector<string> a, int __expected) {
    time_t startClock = clock();
    MazeWithKeys *instance = new MazeWithKeys();
    int __result = instance->startingPoints(a);
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
        vector<string> a;
        from_stream(a);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1535897053;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MazeWithKeys (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
