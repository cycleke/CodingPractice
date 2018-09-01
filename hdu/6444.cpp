#include <cstdio>
#include <vector>
using namespace std;

#define MAXN 10000

int a[MAXN];
int n, m, k;
long long s;
bool vis[MAXN];
long long sum[MAXN * 3];

long long Ract(const vector<int> &vec) {
  int size = vec.size();
  sum[0] = 0;
  for (int i = 1; i < 3 * size; i++) {
    sum[i] = sum[i - 1] + a[vec[(i - 1) % size]];
  }

  long long s1 = 0;
  long long t1 = m / size - 1;
  if (t1 < 0) t1 = 0;
  s1 = t1 * sum[size];
  if (s1 < 0) s1 = 0;

  int ml = m - t1 * size;
  long long ms = 0;
  int st = 0, ed = 0;
  static int q[MAXN * 3];
  q[ed++] = 0;
  for (int i = 0; i < 3 * size; i++) {
    while (st < ed && q[st] < i - ml) st++;
    ms = max(ms, sum[i] - sum[q[st]]);
    while (st < ed && sum[q[ed - 1]] >= sum[i]) ed--;
    q[ed++] = i;
  }
  return max(0ll, s - s1 - ms);
}

int main() {
  int o_o;
  scanf("%d", &o_o);
  for (int step = 1; step <= o_o; step++) {
    scanf("%d%I64d%d%d", &n, &s, &m, &k);
    for (int i = 0; i < n; i++) {
      vis[i] = false;
      scanf("%d", a + i);
    }
    long long ans = s;
    for (int i = 0; i < n; i++) {
      if (vis[i]) continue;
      vector<int> vec;
      int now = i;
      while (!vis[now]) {
        vis[now] = true;
        vec.push_back(now);
        now = (now + k) % n;
      }
      ans = min(ans, Ract(vec));
    }
    printf("Case #%d: %I64d\n", step, ans);
  }
  return 0;
}
