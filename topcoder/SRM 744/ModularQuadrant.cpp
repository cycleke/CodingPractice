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

class ModularQuadrant {
public:
  long long sum(int r1, int r2, int c1, int c2) {
    return sum(r2, c2) - sum(r2, c1 - 1) - sum(r1 - 1, c2) +
           sum(r1 - 1, c1 - 1);
  }

private:
  ll sum(ll r, ll c) {
    if (r < 0 || c < 0)
      return 0;
    if (r < c)
      swap(r, c);

    ll res = 0;

    // Not Square part
    while (r > c && (r - c) % 3) {
      res += (r % 3) * (c + 1);
      r--;
    }
    res += (r - c) * (c + 1);
    // Square part

    if (c % 3 == 0)
      c--;
    else if (c % 3 == 1) {
      res += 2 * c + 1;
      c -= 2;
    }
    if (c > 0) {
      ll cycle = (c - 2) / 3 + 1;
      res += (5 + c * 2 + 1) * cycle;           // 2 part
      res += (3 + (c - 1) * 2 + 1) * cycle / 2; // 1 part
    }
    cerr << "#############" << endl;
    cerr << r << " " << c << " " << res << endl;
    cerr << "#############" << endl;
    return res;
  }
};

// CUT begin
ifstream data("ModularQuadrant.sample");

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

template <typename T> string to_string(T t) {
  stringstream s;
  s << t;
  return s.str();
}

string to_string(string t) { return "\"" + t + "\""; }

bool do_test(int r1, int r2, int c1, int c2, long long __expected) {
  time_t startClock = clock();
  ModularQuadrant *instance = new ModularQuadrant();
  long long __result = instance->sum(r1, r2, c1, c2);
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
    int r1;
    from_stream(r1);
    int r2;
    from_stream(r2);
    int c1;
    from_stream(c1);
    int c2;
    from_stream(c2);
    next_line();
    long long __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if (do_test(r1, r2, c1, c2, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1545441460;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : "
         << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
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
    cout << "ModularQuadrant (250 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
