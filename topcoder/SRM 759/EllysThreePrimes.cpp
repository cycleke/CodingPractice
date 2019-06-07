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

class EllysThreePrimes {
public:
  vector<int> getPrimes(vector<int> sums) {
    silver();
    int n = five_digit_primes.size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        int p1 = five_digit_primes[i];
        int p2 = five_digit_primes[j];
        int p3 = 0, t;
        for (int k = 0; k < 5; ++k) {
          t = sums[k] - p1 % 10 - p2 % 10;
          if (t < 0 || t > 9) {
            p3 = 0;
            break;
          }
          static int p[] = {1, 10, 100, 1000, 10000};

          p3 += t * p[k];
          p1 /= 10;
          p2 /= 10;
        }
        if (!mark[p3] && p3 >= BOUND && p3 != five_digit_primes[i] &&
            p3 != five_digit_primes[j]) {
          return vector<int>({five_digit_primes[i], five_digit_primes[j], p3});
        }
      }
    }
    return vector<int>();
  }

private:
  vector<int> primes, five_digit_primes;
  static const int BOUND = 1e4;
  static const int MAX_NUM = 1e5;
  bool mark[MAX_NUM];
  void silver() {
    memset(mark, 0, sizeof(mark));
    mark[0] = mark[1] = true;
    for (int i = 2; i < MAX_NUM; ++i) {
      if (!mark[i]) {
        primes.push_back(i);
        if (i >= BOUND) {
          five_digit_primes.push_back(i);
        }
      }
      for (int &p : primes) {
        int t = i * p;
        if (t >= MAX_NUM) {
          break;
        }
        mark[t] = true;
        if (i % p == 0) {
          break;
        }
      }
    }
  }
};

// CUT begin
ifstream data("EllysThreePrimes.sample");

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

template <typename T> string to_string(vector<T> ts) {
  stringstream s;
  s << "[ ";
  for (int i = 0; i < ts.size(); ++i) {
    if (i > 0)
      s << ", ";
    s << to_string(ts[i]);
  }
  s << " ]";
  return s.str();
}

bool do_test(vector<int> sums, vector<int> __expected) {
  time_t startClock = clock();
  EllysThreePrimes *instance = new EllysThreePrimes();
  vector<int> __result = instance->getPrimes(sums);
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
    vector<int> sums;
    from_stream(sums);
    next_line();
    vector<int> __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if (do_test(sums, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1559894067;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : "
         << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
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
    cout << "EllysThreePrimes (600 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
