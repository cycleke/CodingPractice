#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;

const int INF = 0x3ffffff;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 500000 + 3;

char s[MAXN], t[MAXN];
int nxt[MAXN];

int main() {
  gets(s + 1);
  gets(t + 1);
  int l1 = strlen(s + 1);
  int l2 = strlen(t + 1);

  int j = 0;
  for (int i = 2; i <= l2; i++) {
    while (j && t[j + 1] != t[i])
      j = nxt[j];
    if (t[j + 1] == t[i])
      j++;
    nxt[i] = j;
  }

  int c0 = 0, c1 = 0;
  for (int i = 1; i <= l1; i++) {
    if (s[i] == '0') {
      c0++;
    } else {
      c1++;
    }
  }

  for (int i = 1, j = 1; i <= l1; i++, j++) {
    if (t[j] == '0' && c0 == 0) {
      putchar('1');
      c1--;
      j = nxt[j];
    } else if (t[j] == '1' && c1 == 0) {
      putchar('0');
      c0--;
      j = nxt[j];
    } else {
      putchar(t[j]);
      t[j] == '0' ? c0-- : c1--;
    }
    if (j == l2) {
      j = nxt[j];
    }
  }
  puts("");
  return 0;
}
