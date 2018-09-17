#include <cstdio>
#include <queue>
#include <set>
using namespace std;

int main() {
  int n, m, count = 0;
  scanf("%d%d", &m, &n);
  queue<int> q;
  set<int> s;
  for (int i = 0; i < n; i++) {
    int a;
    scanf("%d", &a);
    if (s.find(a) != s.end()) continue;
    if ((int)q.size() < m) {
      count++;
      q.push(a);
      s.insert(a);
    } else {
      s.erase(q.front());
      q.pop();
      count++;
      q.push(a);
      s.insert(a);
    }
  }
  printf("%d\n", count);
  return 0;
}
