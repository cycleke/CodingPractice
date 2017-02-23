#include <cstdio>

const int mod = 1e9 + 7, MaxN = 1e6 + 5;
typedef int arr[MaxN];

arr f, d, inv;

void Inv(int a, int &r) {
	r = 1;
	for (int b = mod - 2; b; b >>= 1, a = (long long)a * a % mod)
	  if (b & 1) r = (long long)a * r % mod;
}

void Init() {
    d[1] = 0;
    d[0] = d[2] = 1;
    f[0] = f[1] = 1;
	f[2] = 2;
	inv[0] = inv[1] = 1;
    for (int i = 3; i < MaxN; ++i) {
        d[i] = (i - 1LL) * (d[i - 1] + d[i - 2]) % mod;
        f[i] = (long long)f[i - 1] * i % mod;
    }
	Inv(f[MaxN - 1], inv[MaxN - 1]);
	for (int i = MaxN - 2; i; --i)
	  inv[i] = (long long)inv[i + 1] * (i + 1) % mod;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("t.in", "r", stdin);
#endif // ONLINE_JUDGE
    int T, n, m, t;
    Init();
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        t = (long long)f[n] * inv[n - m] % mod * inv[m] % mod * d[n - m] % mod;
        printf("%d\n", t);
    }
}
