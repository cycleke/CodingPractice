#include <bits/stdc++.h>
using namespace std;

int n;

struct Graph {
  int map[5][7];

  bool allCleared() const {
    for (int i = 0; i < 5; i++) {
      // for (int j = 0; j < 7; j++)
      if (map[i][0] != 0)
        return false;
    }
    return true;
  }
} now, pre[5];

struct MoveInfo {
  int x, y, kind;

  MoveInfo() {}
  MoveInfo(int _x, int _y, int _kind) : x(_x), y(_y), kind(_kind) {}

  void Println() const { cout << x << " " << y << " " << kind << endl; }
} steps[5];

int step_id;

bool visited[5][7];

inline bool CheckPosition(int x, int y) {
  if (x < 0 || x >= 5 || y < 0 || y >= 7)
    return false;
  if (visited[x][y] || now.map[x][y] == 0)
    return false;
  return true;
}

bool mark[5][7], update_data[5][7];
int max_x, max_y, min_x, min_y;

void dfsUpdate(int x, int y, int dir) {
  visited[x][y] = true;
  max_x = max(max_x, x);
  max_y = max(max_y, y);
  min_x = min(min_x, x);
  min_y = min(min_y, y);
  static const int dx[] = {0, 0, 1, -1};
  static const int dy[] = {1, -1, 0, 0};
  if (dir == -1) {
    for (int i = 0; i < 4; i++) {
      int _x = x + dx[i];
      int _y = y + dy[i];
      if (CheckPosition(_x, _y) && now.map[x][y] == now.map[_x][_y])
        dfsUpdate(_x, _y, i);
    }
  } else {
    int _x = x + dx[dir];
    int _y = y + dy[dir];
    if (CheckPosition(_x, _y) && now.map[x][y] == now.map[_x][_y])
      dfsUpdate(_x, _y, dir);
  }
  visited[x][y] = false;
}

inline bool Update(int x, int y) {
  max_x = max_y = -1;
  min_x = min_y = 10;
  dfsUpdate(x, y, -1);
  bool flag = false;
  if (max_x - min_x + 1 >= 3) {
    for (int i = min_x; i <= max_x; i++) {
      mark[i][y] = true;
      update_data[i][y] = true;
    }
    flag = true;
  }
  if (max_y - min_y + 1 >= 3) {
    for (int i = min_y; i <= max_y; i++) {
      mark[x][i] = true;
      update_data[x][i] = true;
    }
    flag = true;
  }
  return flag;
}

void UpdateAll() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7; j++) {
      if (!mark[i][j])
        continue;
      now.map[i][j] = 0;
      mark[i][j] = false;
    }
    for (int j = 0; j < 7; j++) {
      if (now.map[i][j] > 0)
        continue;
      int delta = 0;
      for (int k = j + 1; k < 7; k++)
        if (now.map[i][k] > 0) {
          now.map[i][j + delta] = now.map[i][k];
          delta++;
          now.map[i][k] = 0;
        }
      break;
    }
  }
}

inline bool Move(int x, int y, bool kind) {
  int _x, _y;
  if (kind) {
    if (x == 4)
      return false;
    swap(now.map[x][y], now.map[x + 1][y]);
    steps[step_id++] = MoveInfo(x, y, 1);
    _x = x + 1;
    _y = y;
    if (now.map[x][y] == 0) {
      for (int i = x; i <= x + 1; i++) {
        for (int j = 0; j < 7; j++) {
          if (now.map[i][j] > 0)
            continue;
          int delta = 0;
          for (int k = j + 1; k < 7; k++) {
            if (now.map[i][k] > 0) {
              if (i == x + 1 && y == k)
                _y = j + delta;
              now.map[i][j + delta] = now.map[i][k];
              delta++;
              now.map[i][k] = 0;
            }
          }
          break;
        }
      }
    }
  } else {
    if (x == 0)
      return false;
    swap(now.map[x][y], now.map[x - 1][y]);
    steps[step_id++] = MoveInfo(x, y, -1);
    _x = x - 1;
    _y = y;
    if (now.map[x][y] == 0) {
      for (int i = x - 1; i <= x; i++) {
        for (int j = 0; j < 7; j++) {
          if (now.map[i][j] > 0)
            continue;
          int delta = 0;
          for (int k = j + 1; k < 7; k++) {
            if (now.map[i][k] > 0) {
              if (i == x - 1 && y == k)
                _y = j + delta;
              now.map[i][j + delta] = now.map[i][k];
              delta++;
              now.map[i][k] = 0;
            }
          }
          break;
        }
      }
    }
  }
  bool flag = false;
  flag |= Update(x, y);
  flag |= Update(_x, _y);
  while (flag) {
    UpdateAll();
    flag = false;
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 7 && now.map[i][j] != 0; j++) {
        if (update_data[i][j]) {
          update_data[i][j] = false;
          if (Update(i, j))
            flag = true;
        }
      }
  }
  return true;
}

bool dfs(int depth, int x, int y, bool kind) {
  if (depth >= n)
    return false;
  pre[depth] = now;
  if (Move(x, y, kind)) {
    if (now.allCleared()) {
      if (depth == n - 1) {
        for (int i = 0; i < n; i++)
          steps[i].Println();
        return true;
      } else {
        return false;
      }
    }
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 7 && now.map[i][j] != 0; j++) {
        if (dfs(depth + 1, i, j, 1))
          return true;
        if (i > 0 && now.map[i - 1][j] == 0) {
          if (dfs(depth + 1, i, j, 0))
            return true;
        }
      }
    }
    step_id--;
  }
  now = pre[depth];
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < 5; i++) {
    int x, id = 0;
    while (cin >> x) {
      if (x == 0)
        break;
      now.map[i][id++] = x;
    }
  }

  bool found = false;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7 && now.map[i][j] != 0; j++) {
      if (dfs(0, i, j, 1)) {
        found = true;
        break;
      }
      if (i > 0 && now.map[i - 1][j] == 0 && dfs(0, i, j, 0)) {
        found = true;
        break;
      }
    }
    if (found)
      break;
  }
  if (!found)
    cout << -1 << endl;
  return 0;
}
