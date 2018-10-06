#include <bits/stdc++.h>
using namespace std;

int dp[101];
pair<int, pair<int, int> >rubbish[100];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int d, g;
  cin >> d >> g;
  for (int i = 0; i < g; i++) {
    int t, f, h;
    cin >> t >> f >> h;
    rubbish[i] = make_pair(t, make_pair(f, h));
  }
  sort(rubbish, rubbish + g);
  dp[0] = 10;
  for (int i = 0; i < g; i++) {
    int t = rubbish[i].first;
    int f = rubbish[i].second.first;
    int h = rubbish[i].second.second;
    for (int j = d; j >= 0; j--) {
      if (dp[j] < t) continue;
      if (j + h >= d) {
        cout << t << endl;
        return 0;
      }
      dp[j + h] = max(dp[j + h], dp[j]);
      dp[j] += f;
    }
  }
  cout << dp[0] << endl;
  return 0;
}
