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

class Subrectangle
{
  public:
    int minMissed(string S)
    {
        int n = S.size();
        if (n == 0)
            return 1;

        int count = 0;
        for (char c : S)
            count += c == '#';
        if (count == 0)
            return 1;
        count = 0;
        for (int i = 0; i < n; ++i)
            if (S[i] == '#' && (i == 0 || S[i - 1] != '#'))
                ++count;
        if (count == 1)
            return 0;

        int res = n;
        for (int x = 1; x < 303; ++x)
            for (int y = 1; x + y < 303; ++y)
            {
                int temp = get_try(S, x, y, n);
                if (temp < res)
                    res = temp;
            }
        return res;
    }

    int get_char(int now, int x, int y)
    {
        return now % (x + y) < x ? '#' : '.';
    }

    int get_try(const string &S, int x, int y, const int &n)
    {
        int a = 0, b = n - 1;
        while (a < n && S[a] == '.')
        {
            ++a;
        }
        while (b >= 0 && S[b] == '.')
        {
            --b;
        }
        int ia = a, ib = n - b - 1;
        int res = 0, cur = 0;
        for (int i = a; i <= b; ++i)
        {
            char c = S[i];
            if (get_char(cur, x, y) == c)
                ++cur;
            else
            {
                if (cur % (x + y) < x)
                {
                    cur += x - (cur % (x + y)) + 1;
                }
                else
                {
                    cur += x + y - (cur % (x + y)) + 1;
                }
            }
        }
        cur += x - (cur % (x + y));
        res = cur - (b - a + 1);
        ia %= x + y;
        ib %= x + y;
        if (ia + ib <= y)
        {
            res += y - ia - ib;
        }
        else
        {
            res += x + y + y - ib - ia;
        }
        return res;
    }
};

// CUT begin
ifstream data("Subrectangle.sample");

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

bool do_test(string S, int __expected)
{
    time_t startClock = clock();
    Subrectangle *instance = new Subrectangle();
    int __result = instance->minMissed(S);
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
        int __answer;
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
        int T = time(NULL) - 1516642768;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Subrectangle (500 Points)" << endl
             << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
