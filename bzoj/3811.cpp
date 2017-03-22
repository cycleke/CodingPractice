#include <cstdio>

typedef unsigned long long ul;

inline ul gul() {
	static ul a;
	static char c;
	do c = getchar_unlocked(); while (c < 48);
	a = c - 48;
	while (47 < (c = getchar_unlocked()))
		a = (a << 3) + (a << 1) + c - 48;
	return a;
}

int n, k;
ul a[100004];

inline void case1() {
	ul res = 0;
	for (register int i = 0; i < n; ++i) res |= a[i];
	printf("%llu", res >> 1);
	if (res & 1) puts(".5");
	else puts("");
}

inline void case2() {
	ul res = 0, cnt = 0;
	bool flag;
	for (register int i = 0; i < 32; ++i)
		for (register int j = 0; j < 32; ++j) {
			flag = false;
			for (register int k = 0; k < n; ++k)
				if (a[k] >> i & 1) {
					flag = true;
					break;
				}
			if (!flag) continue;
			flag = false;
			for (register int k = 0; k < n; ++k)
				if (a[k] >> j & 1) {
					flag = true;
					break;
				}
			if (!flag) continue;
			flag = false;
			for (register int k = 0; k < n; ++k)
				if ((a[k] >> i & 1) ^ (a[k] >> j & 1)) {
					flag = true;
					break;
				}

			if (i + j - 1 - flag < 0)
				++cnt;
			else
				res += 1ULL << (i + j - 1 - flag);
		}
	res += cnt >> 1;
	printf("%llu", res);
	if (cnt & 1) puts(".5");
	else puts("");
}

ul b[25];
int c[25];

inline void case345() {
	int cnt = 0;
	for (register int i = 0; i < n; ++i)
		for (register int j = 23; ~j; --j)
			if (a[i] >> j & 1) {
				if (b[j]) a[i] ^= b[j];
				else {
					c[cnt++] = b[j] = a[i];
					break;
				}
			}
	
	ul res = 0, tot = 0;
	int all = 1 << cnt, val;
	for (register int s = all - 1; ~s; --s) {
		val = 0;
		for (register int i = 0; i < cnt; ++i)
			if (s >> i & 1) val ^= c[i];
		ul a = 0, b = 1;
		for (register int i = 0; i < k; ++i) {
			a *= val, b *= val;
			a += b >> cnt;
			b &= all - 1;
		}
		
		res += a;
		tot += b;
		res += tot >> cnt;
		tot &= all - 1;
	}

	printf("%llu", res);
	if (tot) puts(".5");
	else puts("");
}

int main() {
	n = gul(), k = gul();
	for (register int i = 0; i < n; ++i)
		a[i] = gul();
	
	if (k == 1) case1();
	else if (k == 2) case2();
	else case345();
	
	return 0;
}
