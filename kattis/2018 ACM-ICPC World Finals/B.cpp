#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<vector<int> > mark;
  vector<vector<vector<pair<int, int> > > > g;
  map<string, int> id;
  vector<string> words;
  vector<int> ids;
  int n = 0;
  string pre = "", cur;
  int id_pre = -1, id_cur = -1;
  vector<string> text;

  while ((cin >> cur) != "") {
    string real_cur(cur);
    if (real_cur.back() == '.' || real_cur.back() == ',') {
      real_cur.pop_back();
    }
    if (id.find(real_cur) == id.end()) {
      id[real_cur] = n++;
      words.push_back(real_cur);
      mark.push_back(vector<int>(2, 0));
      g.push_back(vector<vector<pair<int, int> > >(2));
    }
    id_cur = id[real_cur];
    ids.push_back(id_cur);
    if (cur.back() == '.') {
      ids.push_back(-1);
    } else if (cur.back() == ',') {
      ids.push_back(-2);
    }
    if (pre != "") {
      if (pre.back() == ',') {
        mark[id_pre][1] = 1;
        mark[id_cur][0] = 1;
      } else if (pre.back() != '.') {
        g[id_pre][1].emplace_back(id_cur, 0);
        g[id_cur][0].emplace_back(id_pre, 1);
      }
    }
    pre = cur;
    id_pre = id_cur;
  }

  vector<pair<int, int>> f;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 2; ++j) {
      if (mark[i][j] != 0) {
        f.emplace_back(i, j);
      }
    }
  }
  for (int x = 0; x < (int)f.size(); ++x) {
    int i = f[x].first;
    int j = f[x].second;
    for (auto &y : g[i][j]) {
      if (mark[y.first][y.second] == 0) {
        mark[y.first][y.second] = 1;
        f.push_back(y);
      }
    }
  }
  bool first = true;
  for (int i = 0; i < (int)ids.size(); ++i) {
    if (ids[i] == -1) {
      cout << '.';
    } else if (ids[i] == -2) {
      cout << ',';
    } else {
      if (!first) {
        cout << ' ';
      }
      first = false;
      cout << words[ids[i]];
    }
    if (ids[i] >= 0 && i + 1 < (int)ids.size() && ids[i + 1] >= 0 &&
        mark[ids[i]][1]) {
      cout << ',';
    }
  }
  cout << endl;
  return 0;
}
