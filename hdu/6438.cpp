#include <cstdio>
#include <set>
using namespace std;
multiset<pair<int, bool> >s;

int main() {
  int _;
  scanf("%d", &_);
  while (_--) {
    int n, a;
    scanf("%d", &n);
    s.clear();
    int spent = 0;
    long long gained = 0;
    for (int i = 0; i < n; i++) {
      scanf("%d", &a);
      if (!s.empty() && s.begin()->first < a) {
        gained += a - s.begin()->first;
        if (s.begin()->second)
          spent += 2;
        s.erase(s.begin());
        s.insert(make_pair(a, true));
        s.insert(make_pair(a, false));
      } else {
        s.insert(make_pair(a, true));
      }
    }
    printf("%lld %d\n", gained, spent);
  }
  return 0;
}
