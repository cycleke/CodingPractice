#include <cstdio>
#define N 50010
#define SN 502
#define block 110
int belong[N], l[SN], r[SN];
long long v[N], add[SN];

void Update(int x, int y, int val) {
	if (belong[x] == belong[y]) {
		for (int i = x; i <= y; ++i) v[i] += val;
		return;
	}
	for (int i = x; i <= r[belong[x]]; ++i)
	  v[i] += val;
	for (int i = belong[x] + 1; i < belong[y]; ++i)
	  add[i] += val;
	for (int i = l[belong[y]]; i <= y; ++i)
	  v[i] += val;
}

int main() {
	int n, num;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", v + i);
	num = n / block; if (n % block) ++num;
	for (int i = 1; i <= num; ++i)
	  l[i] = (i - 1) * block + 1, r[i] = i * block;
	r[num] = n;
	for (int i = 1; i <= n; ++i)
	  belong[i] = (i - 1) / block + 1;
	for (int T = 0; T < n; ++T) {
		int f, a, b, c;
		scanf("%d%d%d%d", &f, &a, &b, &c);
		if (f) printf("%lld\n", v[b] + add[belong[b]]);
		else Update(a, b, c);
	}
	return 0;
}
