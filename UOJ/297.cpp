#include <cstdio>
#include <cstring>
#define MAXN 20000003
short seed;
int n, k, S, mx = -0x3f3f3f3f;
int p[MAXN], q[MAXN], C[MAXN * 2];
inline int getrand() {
	return seed = ((seed * 12321) ^ 9999) & 32767;
}
inline void generateData() {
	scanf("%d%d%d", &k, &seed, &S);
	int t = 0;
	n = k << 1 | 1;
	memset(p, 0, sizeof(p));
	for (register int i = 1; i <= n; ++i) {
		p[i] = getrand() >> 7 & 1;
		t += p[i];
	}
	register int i = 1;
	while (t > k) {
		while (p[i] == 0)
			++i;
		p[i] = 0;
		--t;
	}
	while (t < k) {
		while (p[i] == 1)
			++i;
		p[i] = 1;
		++t;
	}
}

inline int Try(int value) {
	int o = mx;
	while (value >= C[o]) value -= C[o--];
	for(register int i = n; i >= 1; --i)
		if(!p[i] && q[i] == o && !value--) return i;
}

int main() {
	generateData();
	q[0] = MAXN;
	for (register int i = 1; i <= n; ++i) {
		q[i] = q[i - 1] + 1;
		if (!p[i]) {
			++C[q[i] -= 2];
			if (q[i] > mx) mx = q[i];
		}
	}
	printf("%d\n", Try(0));
	printf("%d\n", Try(S));
	printf("%d\n", Try(k - S));
	return 0;
}
