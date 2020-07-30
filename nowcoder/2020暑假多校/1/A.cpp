#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

const int BUFFER_SIZE = 1u << 23 | 1;
char buffer[BUFFER_SIZE], *buffer_ptr = buffer;
#define alloc(x, type, len)                                                    \
  type *x = (type *)buffer_ptr;                                                \
  buffer_ptr += (len) * sizeof(type);
#define clear_buffer()                                                         \
  memset(buffer, 0, buffer_ptr - buffer), buffer_ptr = buffer;

template <int MAX_LENGTH> class SuffixArray {
#define L_TYPE true
#define S_TYPE false
public:
  int sa[MAX_LENGTH], rank[MAX_LENGTH], height[MAX_LENGTH];
  void compute(int n, int m, int *s) {
    sais(n, m, s, sa);
    for (int i = 0; i < n; ++i) rank[sa[i]] = i;
    for (int i = 0, h = 0; i < n; ++i) {
      if (rank[i]) {
        int j = sa[rank[i] - 1];
        while (s[i + h] == s[j + h]) ++h;
        height[rank[i]] = h;
      } else {
        h = 0;
      }
      if (h) --h;
    }
  }

private:
  int l_bucket[MAX_LENGTH], s_bucket[MAX_LENGTH];

  void induce(int n, int m, int *s, bool *type, int *sa, int *bucket,
              int *l_bucket, int *s_bucket) {
    memcpy(l_bucket + 1, bucket, m * sizeof(int));
    memcpy(s_bucket + 1, bucket + 1, m * sizeof(int));
    sa[l_bucket[s[n - 1]]++] = n - 1;
    for (int i = 0; i < n; ++i) {
      int t = sa[i] - 1;
      if (t >= 0 && type[t] == L_TYPE) sa[l_bucket[s[t]]++] = t;
    }
    for (int i = n - 1; i >= 0; --i) {
      int t = sa[i] - 1;
      if (t >= 0 && type[t] == S_TYPE) sa[--s_bucket[s[t]]] = t;
    }
  }
  void sais(int n, int m, int *s, int *sa) {
    alloc(type, bool, n + 1);
    alloc(bucket, int, m + 1);
    type[n] = false;
    for (int i = n - 1; i >= 0; --i) {
      ++bucket[s[i]];
      type[i] = s[i] > s[i + 1] || (s[i] == s[i + 1] && type[i + 1] == L_TYPE);
    }
    for (int i = 1; i <= m; ++i) {
      bucket[i] += bucket[i - 1];
      s_bucket[i] = bucket[i];
    }
    memset(rank, -1, n * sizeof(int));

    alloc(lms, int, n + 1);
    int n1 = 0;
    for (int i = 0; i < n; ++i) {
      if (!type[i] && (i == 0 || type[i - 1])) lms[rank[i] = n1++] = i;
    }
    lms[n1] = n;
    memset(sa, -1, n * sizeof(int));
    for (int i = 0; i < n1; ++i) sa[--s_bucket[s[lms[i]]]] = lms[i];
    induce(n, m, s, type, sa, bucket, l_bucket, s_bucket);
    int m1 = 0;
    alloc(s1, int, n + 1);
    for (int i = 0, t = -1; i < n; ++i) {
      int r = rank[sa[i]];
      if (r != -1) {
        int len = lms[r + 1] - sa[i] + 1;
        m1 += t == -1 || len != lms[rank[t] + 1] - t + 1 ||
              memcmp(s + t, s + sa[i], len * sizeof(int)) != 0;
        s1[r] = m1;
        t = sa[i];
      }
    }
    alloc(sa1, int, n + 1);
    if (n1 == m1) {
      for (int i = 0; i < n1; ++i) sa1[s1[i] - 1] = i;
    } else {
      sais(n1, m1, s1, sa1);
    }
    memset(sa, -1, n * sizeof(int));
    memcpy(s_bucket + 1, bucket + 1, m * sizeof(int));
    for (int i = n1 - 1; i >= 0; --i) {
      int t = lms[sa1[i]];
      sa[--s_bucket[s[t]]] = t;
    }
    induce(n, m, s, type, sa, bucket, l_bucket, s_bucket);
  }
#undef S_TYPE
#undef L_TYPE
};

const int MAXN = 1e5 + 5;

char s[MAXN];
int c[MAXN];
SuffixArray<MAXN> sa;

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    cin >> s;
    int last[] = {-1, -1};
    for (int i = n - 1; ~i; --i) {
      c[i] = (~last[s[i] - 'a'] ? last[s[i] - 'a'] - i : n);
      last[s[i] - 'a'] = i;
    }
    c[n] = n + 1;

    // for (int i = 0; i <= n; ++i) cout << c[i] << " \n"[i == n];

    sa.compute(n + 1, n + 1, c);
    for (int i = n - 1; i >= 0; --i) cout << sa.sa[i] + 1 << " \n"[i == 0];
    clear_buffer();
  }

  return 0;
}
