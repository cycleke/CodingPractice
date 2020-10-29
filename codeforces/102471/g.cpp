#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300 + 3;
const int PROBLEMS = 10;
const int PENALTY = 20;
const int GOLD_MEDAL = 1200;
const int SILVER_MEDAL = 800;
const int BRONZE_MEDAL = 400;
const int PROBLEM_FIRST_BLOOD = 800;
const int ALL_FIRST_BLOOD = 700;
const int ALL_LAST_BLOOD = 500;
const int CONTEST_TIME = 300;
const int HAPPINESS_RATE = 5000;

int getInt() {
  char ch = getchar();
  while (ch != '-' && !isdigit(ch)) ch = getchar();
  if (ch == '-') return -1;
  int x = ch - '0';
  while (isdigit(ch = getchar())) x = x * 10 + ch - '0';
  return x;
}

int n, team_rank[MAXN], all_first_time, all_last_time, first_time[PROBLEMS];

struct Team {
  int id, solved, total_time, solved_time[PROBLEMS];

  void read(int id) {
    this->id = id;
    solved = total_time = 0;
    for (int i = 0; i < PROBLEMS; ++i) {
      int done_time = getInt();
      if (done_time == -1) continue;
      int wrong_time = getInt();
      solved_time[solved++] = done_time;
      total_time += done_time + PENALTY * wrong_time;
      first_time[i] = min(first_time[i], done_time);
    }
    sort(solved_time, solved_time + solved, greater<int>());
    if (solved) {
      all_last_time = max(all_last_time, solved_time[0]);
      all_first_time = min(all_first_time, solved_time[solved - 1]);
    }
  }

  bool operator<(const Team &other) const {
    if (solved ^ other.solved) return solved > other.solved;
    if (total_time ^ other.total_time) return total_time < other.total_time;
    for (int i = 0; i < solved; ++i)
      if (solved_time[i] ^ other.solved_time[i])
        return solved_time[i] < other.solved_time[i];
    return id < other.id;
  }
} teams[MAXN], pang;

int need_time[PROBLEMS], need_wrong_time[PROBLEMS], can_solve, permu[PROBLEMS];

int main(int argc, char *argv[]) {
  n = getInt();

  fill(first_time, first_time + PROBLEMS, INT_MAX);
  all_first_time = INT_MAX, all_last_time = INT_MIN;
  for (int i = 1; i < n; ++i) {
    teams[i].read(i);
    team_rank[i] = i;
  }
  sort(team_rank + 1, team_rank + n,
       [&](int a, int b) { return teams[a] < teams[b]; });

  for (int i = 0; i < PROBLEMS; ++i) {
    need_time[i] = getInt();
    if (need_time[i] < 0) continue;
    permu[can_solve++] = i;
    need_wrong_time[i] = getInt();
  }

  int ans = 0;
  do {
    int happiness = 0, now = 0;
    pang.solved = pang.total_time = 0;
    for (int i = 0; i < can_solve; ++i) {
      int j = permu[i];
      if (now + need_time[j] > CONTEST_TIME) break;
      now += need_time[j];
      pang.solved_time[pang.solved++] = now;
      pang.total_time += now + need_wrong_time[j] * PENALTY;
      if (now <= first_time[j]) happiness += PROBLEM_FIRST_BLOOD;
      if (!i && now <= all_first_time) happiness += ALL_FIRST_BLOOD;
    }
    if (pang.solved && now >= all_last_time) happiness += ALL_LAST_BLOOD;
    reverse(pang.solved_time, pang.solved_time + pang.solved);
    int l = 1, r = n - 1;
    while (l <= r) {
      int mid = (l + r) / 2;
      (pang < teams[team_rank[mid]]) ? r = mid - 1 : l = mid + 1;
    }
    happiness += HAPPINESS_RATE / l;
    if (l <= n / 10) {
      happiness += GOLD_MEDAL;
    } else if (l <= 3 * n / 10) {
      happiness += SILVER_MEDAL;
    } else if (l <= 6 * n / 10) {
      happiness += BRONZE_MEDAL;
    }
    ans = max(ans, happiness);
  } while (next_permutation(permu, permu + can_solve));

  cout << ans << "\n";
  return 0;
}

