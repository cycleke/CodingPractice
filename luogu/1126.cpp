#include <bits/stdc++.h>
using namespace std;

struct Robot {
  int x, y, direction;
  Robot(int _x, int _y, int _dir) :
    x(_x), y(_y), direction(_dir) {}
};
int dis[51][51][4];
bool able[51][51], inQueue[51][51][4];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  memset(able , true, sizeof(able));
  memset(inQueue, false, sizeof(inQueue));
  memset(dis, 63, sizeof(dis));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int x;
      cin >> x;
      if (x == 1) {
        able[i][j] = able[i][j - 1] = able[i - 1][j] = able[i - 1][j - 1] = false;
      }
    }
  }

  int sx, sy, ex, ey;
  char start_direction;
  cin >> sx >> sy >> ex >> ey >> start_direction;

  queue<Robot> q;
  auto AddIntoQueue = [&](int x, int y, int direction, int step) {
    if (dis[x][y][direction] <= step) return;
    dis[x][y][direction] = step;
    if (inQueue[x][y][direction]) return;
    q.push(Robot(x, y, direction));
    inQueue[x][y][direction] = true;
  };

  const int dx[] = {-1, 0, 1, 0};
  const int dy[] = {0, 1, 0, -1};
  if (start_direction == 'N')
    AddIntoQueue(sx, sy, 0, 0);
  else if (start_direction == 'E')
    AddIntoQueue(sx, sy, 1, 0);
  else if (start_direction == 'S')
    AddIntoQueue(sx, sy, 2, 0);
  else if (start_direction == 'W')
    AddIntoQueue(sx, sy, 3, 0);
  else {
    cerr << "Wrong Data" << endl;
    return -2;
  }

  while (!q.empty()) {
    Robot r = q.front();
    q.pop();
    int step = dis[r.x][r.y][r.direction];
    //Change Direction
    AddIntoQueue(r.x, r.y, (r.direction + 1) & 3, step + 1);
    AddIntoQueue(r.x, r.y, (r.direction + 3) & 3, step + 1);

    //Go Forward
    int _x = r.x;
    int _y = r.y;
    for (int i = 0; i < 3; i++) {
      _x += dx[r.direction];
      _y += dy[r.direction];
      if (!able[_x][_y]) break;
      if (_x < 1 || _x >= n) break;
      if (_y < 1 || _y >= m) break;
      AddIntoQueue(_x, _y, r.direction, step + 1);
    }
  }

  int min_distance = 0x3f3f3f3f;
  for (int i = 0; i < 4; i++) {
    if (dis[ex][ey][i] < min_distance) {
      min_distance = dis[ex][ey][i];
    }
  }

  /*
  //debug log
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cout << endl;
      cout << i << ' ' << j << endl;
      cout << "Able:" << able[i][j] << endl;
      for (int k = 0; k < 4; k++)
        cout << k << ' ' << dis[i][j][k] << endl;
    }
  }
  */

  cout << (min_distance == 0x3f3f3f3f ? -1 : min_distance) << endl;
  return 0;
}
