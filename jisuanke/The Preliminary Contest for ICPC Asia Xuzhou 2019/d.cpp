#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

void get_next(char *S, int *nxt, int n) {
  nxt[0] = -1;
  int j = -1;
  for (int i = 1; i < n; ++i) {
    while ((~j) && S[j + 1] != S[i]) { j = nxt[j]; }
    nxt[i] = (S[j + 1] == S[i]) ? (++j) : j;
  }
}

int pattern(char *S, char *T, int *nxt, int n, int m) {
  int j = -1;
  for (int i = 0; i < m; ++i) {
    while ((~j) && S[j + 1] != T[i]) { j = nxt[j]; }
    j += S[j + 1] == T[i];
    if (j == n - 1) return 1;
  }
  return 0;
}

char S[MAXN], T[MAXN];
int nxt[MAXN];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int ls, lt, q;
  for (cin >> T >> q, lt = strlen(T); q; --q) {
    cin >> S;
    ls = strlen(S);
    if (lt > ls) {
      get_next(S, nxt, ls);
      cout << (pattern(S, T, nxt, ls, lt) ? "my child!\n" : "oh, child!\n");
    } else if (lt < ls) {
      get_next(T, nxt, lt);
      cout << (pattern(T, S, nxt, lt, ls) ? "my teacher!\n" : "senior!\n");
    } else {
      bool flag = 0;
      for (int i = 0; i < lt; i++)
        if (S[i] != T[i]) flag = 1;
      cout << (flag ? "friend!\n" : "jntm!\n");
    }
  }

  return 0;
}
