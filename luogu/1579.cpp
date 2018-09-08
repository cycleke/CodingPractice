#include <cstdio>
#include <cstring>

bool is_prime[20000];
int prime[2000], prime_count;

void Silver(const int n) {
  prime_count = 0;
  memset(is_prime, true, sizeof(bool) * (n + 1));
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= n; i++) {
    if (is_prime[i]) {
      prime[prime_count++] = i;
    }
    for (int j = 0; j < prime_count; j++) {
      int t = i * prime[j];
      if (t > n || t < prime[j]) break;
      is_prime[t] = false;
      if (i % prime[j] == 0) break;
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  Silver(n);
  for (int i = 0; i < prime_count; i++) {
    bool found = false;
    for (int j = i; j < prime_count; j++) {
      int t = prime[i] + prime[j];
      if (t >= n || n - t < prime[j]) break;
      if (is_prime[n - t]) {
        printf("%d %d %d\n", prime[i], prime[j], n - t);
        found = true;
        break;
      }
    }
    if (found) break;
  }
  return 0;
}
