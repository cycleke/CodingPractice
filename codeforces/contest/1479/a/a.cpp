#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 3;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

int n;
int ask(int k) {
  static int a[MAXN];
  if (k <= 0 || k > n) return INT_MAX;
  if (a[k]) return a[k];
  cout << "? " << k << endl;
  cout.flush();
  cin >> a[k];
  return a[k];
}

void answer(int k) {
  cout << "! " << k << endl;
  cout.flush();
  exit(0);
}

int main() {
  ios::sync_with_stdio(false);

  cin >> n;
  int l = 1, r = n;
  while (l < r) {
    int m = (l + r) / 2;
    if (ask(m) < ask(m + 1)) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  answer(l);

  return 0;
}
