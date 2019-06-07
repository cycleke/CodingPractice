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

class EllysHash {
public:
  long long getHash(int N, string A, string B, string C) {
    int left = N / 2;
    int right = N - left;
    left_hashs.clear();
    right_hashs.clear();

    gao(left, A, B, C, 0, 0, left_hashs);
    gao(N, A, B, C, left, 0, right_hashs);

    sort(left_hashs.begin(), left_hashs.end());
    sort(right_hashs.begin(), right_hashs.end());

    long long result = MOD;

    for (auto left_hash : left_hashs) {
      for (int i = 0; i < right; ++i) {
        left_hash = left_hash * KEY % MOD;
      }
      long long goal = MOD - left_hash;
      auto it = lower_bound(right_hashs.begin(), right_hashs.end(), goal);
      if (it != right_hashs.end()) {
        result = min(result, (left_hash + *it) % MOD);
      }

      result = min(result, (left_hash + right_hashs.front()) % MOD);
    }

    return result;
  }

private:
  static const long long KEY = 127;
  static const long long MOD = 1000000000000037LL;
  vector<long long> left_hashs, right_hashs;

  static void gao(const int &N, const string &A, const string &B,
                  const string &C, int idx, long long hash_value,
                  vector<long long> &hashs) {
    if (idx >= N) {
      hashs.push_back(hash_value);
    } else {
      gao(N, A, B, C, idx + 1, (hash_value * KEY + A[idx]) % MOD, hashs);
      gao(N, A, B, C, idx + 1, (hash_value * KEY + B[idx]) % MOD, hashs);
      gao(N, A, B, C, idx + 1, (hash_value * KEY + C[idx]) % MOD, hashs);
    }
  }
};

// CUT begin
ifstream data("EllysHash.sample");

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

bool do_test(int N, string A, string B, string C, long long __expected) {
  time_t startClock = clock();
  EllysHash *instance = new EllysHash();
  long long __result = instance->getHash(N, A, B, C);
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
    string A;
    from_stream(A);
    string B;
    from_stream(B);
    string C;
    from_stream(C);
    next_line();
    long long __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if (do_test(N, A, B, C, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1559897087;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : "
         << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
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
    cout << "EllysHash (900 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
