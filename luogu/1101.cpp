#include <bits/stdc++.h>
using namespace std;

#define ILLEGAL(x) (x < 0 || x >= n)

char s[101][101];
bool a[101][101];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }

  const char t[] = "yizhong";
  const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
  const int dy[] = {1, -1, 1, -1, 0, 1, -1, 0};
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (s[i][j] != 'y') continue;
      for (int k = 0; k < 8; k++) {
        bool flag = true;
        int x = i, y = j;
        for (int i = 1; i < 7; i++) {
          x += dx[k];
          y += dy[k];
          if (ILLEGAL(x) || ILLEGAL(y) || s[x][y] != t[i]) {
            flag = false;
            break;
          }
        }
        if (!flag) continue;
        x = i, y = j;
        for (int i = 0; i < 7; i++) {
          a[x][y] = true;
          x += dx[k];
          y += dy[k];
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      putchar_unlocked(a[i][j] ? s[i][j] : '*');
    putchar_unlocked('\n');
  }
  
  return 0;
}
