#include <bits/stdc++.h>
using namespace std;

string s[20];
int n, common[20][20], max_lenght;

inline int getCommon(const string &a, const string &b) {
  int loop_end = min(a.length(), b.length());
  for (int i = 1; i < loop_end; i++) {
    if (a.substr(a.length() - i, i) == b.substr(0, i))
      return i;
  }
  return 0;
}

int used_count[20];
void dfs(int cur, int cur_length) {
  if (cur_length > max_lenght) {
    max_lenght = cur_length;
  }
  for (int i = 0; i < n; i++) {
    if (common[cur][i] > 0 && used_count[i] < 2) {
      used_count[i]++;
      dfs(i, cur_length + s[i].length() - common[cur][i]);
      used_count[i]--;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
    used_count[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      common[i][j] = getCommon(s[i], s[j]);
    }
  }
  char begin_ch;
  cin >> begin_ch;
  max_lenght = -1;
  for (int i = 0; i < n; i++) {
    if (s[i][0] != begin_ch) continue;
    used_count[i]++;
    dfs(i, s[i].length());
    used_count[i]--;
  }
  cout << max_lenght << endl;
  return 0;
}
