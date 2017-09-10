#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

typedef vector < int > vi;

class PermutationSubsequence {
public:
    int n;
    vi findBest(vi arr) {
        n = (int) arr.size();
        vi b(n, -1);
        for (int i = 0; i < n; ++i) {
            if (arr[i] != -1) {
                b[arr[i]] = i;
            }
        }
        for (int i = n - 1; ~i; --i) {
            vi ans = dfs(arr, b, i, 0);
            if (ans.size() > 0) {
                return ans;
            }
        }
        return {-1};
    }
    vi dfs(vi a, vi b, int w, int i) {
        if (i == n) {
            return a;
        }
        if (a[i] != -1) {
            return check(a, w, i) ? dfs(a, b, w, i + 1) : vi();
        }
        for (int j = 0; j < n; ++j) {
            if (b[j] == -1) {
                a[i] = j;
                b[j] = i;
                if (check(a, w, i)) {
                    vi res = dfs(a, b, w, i + 1);
                    if (res.size() > 0) {
                        return res;
                    }
                }
                a[i] = b[j] = -1;
            }
        }
        return vi();
    }
    bool check(vi &a, int w, int i) {
        for (int k = max(0, i - w); k <= min(n - 1, i + w); ++k) {
            if (i != k && a[k] != -1) {
                if (abs(a[i] - a[k]) + abs(i - k) <= w + 1)
                    return false;
            }
        }
        return true;
    }
};

// CUT begin
ifstream data("PermutationSubsequence.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<int> arr, vector<int> __expected) {
    time_t startClock = clock();
    PermutationSubsequence *instance = new PermutationSubsequence();
    vector<int> __result = instance->findBest(arr);
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
        vector<int> arr;
        from_stream(arr);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(arr, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502454549;
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
        cout << "PermutationSubsequence (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
