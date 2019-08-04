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

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
// Head File

const int MAXN = 2e5 + 3;

int A[MAXN];

class WeirdTriangle {
public:
  long long findAllTriangle(int N, vector<int> B, int seed, int MX) {
    A[0] = seed;
    for (int i = 1; i < N; ++i) {
      A[i] = (A[i - 1] * 1103515245LL + 12345LL) % 2147483648LL;
    }

    int postive = 0;
    for (int &x : B) {
      postive += x > 0;
    }
    for (int i = B.size(); i < N; ++i) {
      postive += (2 * (A[i] % MX) - MX + 1) > 0;
    }
    return 1LL * postive * (postive - 1) / 2 * (postive - 2) / 3;
  }
};

// CUT begin
ifstream data("WeirdTriangle.sample");

string next_line() {
  string s;
  getline(data, s);
  return s;
}

template <typename T> void from_stream(T &t) {
  stringstream ss(next_line());
  ss >> t;
}

void from_stream(string &s) { s = next_line(); }

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

template <typename T> string to_string(T t) {
  stringstream s;
  s << t;
  return s.str();
}

string to_string(string t) { return "\"" + t + "\""; }

bool do_test(int N, vector<int> B, int seed, int MX, long long __expected) {
  time_t startClock = clock();
  WeirdTriangle *instance = new WeirdTriangle();
  long long __result = instance->findAllTriangle(N, B, seed, MX);
  double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
  delete instance;

  if (__result == __expected) {
    cout << "PASSED!"
         << " (" << elapsed << " seconds)" << endl;
    return true;
  } else {
    cout << "FAILED!"
         << " (" << elapsed << " seconds)" << endl;
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
    int N;
    from_stream(N);
    vector<int> B;
    from_stream(B);
    int seed;
    from_stream(seed);
    int MX;
    from_stream(MX);
    next_line();
    long long __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if (do_test(N, B, seed, MX, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1564839078;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : "
         << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
         << " points" << endl;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(2);
  set<int> cases;
  bool mainProcess = true;
  for (int i = 1; i < argc; ++i) {
    if (string(argv[i]) == "-") {
      mainProcess = false;
    } else {
      cases.insert(atoi(argv[i]));
    }
  }
  if (mainProcess) {
    cout << "WeirdTriangle (500 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
