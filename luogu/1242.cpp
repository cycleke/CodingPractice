#include <bits/stdc++.h>
using namespace std;

string step;
int step_count, _s[46], _t[46];

void MovDisk(int x, int a, int b) {
  if (a == b) return;
  for (int i = x - 1; i; i--)
    MovDisk(i, _s[i], 3 - a - b);
  _s[x] = b;
  step_count++;
  step += "move ";
  if (x > 9) {
    step += char(x / 10 + '0');
    step += char(x % 10 + '0');
  } else
    step += char(x + '0');
  step += " from ";
  step += char(a + 'A');
  step += " to ";
  step += char(b + 'A');
  step += '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, s[46], t[46];
  cin >> n;
  auto getData = [&](int *a) {
    for (int i = 0; i < 3; i++) {
      int x, xx;
      cin >> x;
      for (int j = 0; j < x; j++) {
        cin >> xx;
        a[xx] = i;
      }
    }
  };
  getData(s);
  getData(t);

  srand(19260817);
  string ans_step = "";
  int ans_step_count = 0x3f3f3f3f;
  for (int m_step = 0; m_step < 92 + 92 + 92; m_step++) {
    step = "";
    step_count = 0;
    for (int i = 1; i <= n; i++) {
      _s[i] = s[i];
      _t[i] = t[i];
    }
    for (int i = n; i; i--) {
      if (rand() % (n - i + 2) == 0)
        MovDisk(i, _s[i], 3 - _s[i] - _t[i]);
      else
        MovDisk(i, _s[i], _t[i]);
    }
    for (int i = n; i; i--)
      MovDisk(i, _s[i], _t[i]);
    if (ans_step_count > step_count) {
      ans_step = step;
      ans_step_count = step_count;
    }
  }
  cout << ans_step << ans_step_count << endl;
  return 0;
}
