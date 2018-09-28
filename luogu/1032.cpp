#include <bits/stdc++.h>
using namespace std;

int main() {

  ios::sync_with_stdio(false);
  cin.tie(0);

  string a, b, t1, t2;
  vector<pair<string, string> > f;

  cin >> a >> b;
  while (cin >> t1 >> t2) {
    f.emplace_back(t1, t2);
  }

  unordered_set<string> s;
  queue<pair<string, int> > q;

  auto AddIntoQueue = [&](const string &str, const int &step) {
    if (step > 10) return;
    if (s.find(str) == s.end()) {
      s.insert(str);
      q.push(make_pair(str, step));
    }
  };

  bool found = false;
  AddIntoQueue(a, 0);
  while (!q.empty()) {
    const string str = q.front().first;
    const int step = q.front().second;
    q.pop();
    if (str == b) {
      found = true;
      cout << step << endl;
      break;
    }
    for (auto g : f) {
      if (str.find(g.first) == string::npos) continue;
      for (size_t i = str.find(g.first); i < str.length();
           i = str.find(g.first, i + 1)) {
        string copy_string = str;
        copy_string.replace(i, g.first.length(), g.second);
        AddIntoQueue(copy_string, step + 1);
      }
    }
  }

  if (!found) {
    cout << "NO ANSWER!" << endl;
  }
  return 0;
}
