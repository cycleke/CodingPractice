#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <typeinfo>
#include <vector>

using namespace std;

class OnlySanta
{
  public:
    bool subseq(const string &A, const string &B)
    {
        int j = 0, sA = A.size(), sB = B.size();
        for (int i = 0; i < sA; ++i)
            if (j < sB && A[i] == B[j])
                ++j;
        return j == sB;
    }

    string solve(string S)
    {
        int it = -1, n = S.size();
        for (int i = 0; i < n; ++i)
        {
            if (S[i] == 'N')
                it = i;
        }

        if (it == -1)
            return "SANTA" + S;
        if (subseq(S.substr(0, it), "SA"))
            return S + "TA";
        return S.substr(0, it) + "SA" + S.substr(it) + "TA";
    }
};

// CUT begin
ifstream data("OnlySanta.sample");

string next_line()
{
    string s;
    getline(data, s);
    return s;
}

template <typename T>
void from_stream(T &t)
{
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s)
{
    s = next_line();
}

template <typename T>
string to_string(T t)
{
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t)
{
    return "\"" + t + "\"";
}

bool do_test(string S, string __expected)
{
    time_t startClock = clock();
    OnlySanta *instance = new OnlySanta();
    string __result = instance->solve(S);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected)
    {
        cout << "PASSED!"
             << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else
    {
        cout << "FAILED!"
             << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command)
{
    int cases = 0, passed = 0;
    while (true)
    {
        if (next_line().find("--") != 0)
            break;
        string S;
        from_stream(S);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if (do_test(S, __answer))
        {
            passed++;
        }
    }
    if (mainProcess)
    {
        cout << endl
             << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1516636590;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) == "-")
        {
            mainProcess = false;
        }
        else
        {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess)
    {
        cout << "OnlySanta (250 Points)" << endl
             << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
