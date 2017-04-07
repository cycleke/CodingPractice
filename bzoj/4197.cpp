#include <cstdio>
#include <cstring>
#include <algorithm>

int f[257][257], p[2][257][257], mod, n, ans;
static const int pr[] = {2, 3, 5, 7, 11, 13, 17, 19, 0};

struct num {
	int big, small;
} s[505];

inline bool operator < (const num &a, const num &b) {
	return (a.big ^ b.big) ? a.big < b.big : a.small < b.small;
}

inline void mov(int &a, const int &b) {
	a += b;
	if (a >= mod) a -= mod;
}

int main() {
	scanf("%d%d", &n, &mod);
	for (int i = 2; i <= n; ++i) {
		int t = i, s = 0;
		for (int _ = 0; _ < 8; ++_)
			if (t % pr[_] == 0) {
				s ^= 1 << _;
				while (t % pr[_] == 0) t /= pr[_];
			}
		::s[i] = (num) {t, s};
	}
	std::sort(s + 2, s + n + 1);
	f[0][0] = 1;
	for (int i = 2; i <= n; ++i) {
		if (s[i].big == 1 || s[i].big != s[i - 1].big) {
			memcpy(p[0], f, sizeof f);
			memcpy(p[1], f, sizeof f);
		}
		for (int j = 255; ~j; --j)
			for (int k = 255; ~k; --k) {
				if ((j & s[i].small) == 0)
					mov(p[0][j][k | s[i].small], p[0][j][k]);
				if ((k & s[i].small) == 0)
					mov(p[1][j | s[i].small][k], p[1][j][k]);
			}
		if (s[i].big == 1 || s[i].big != s[i + 1].big) {
			for (int j = 255; ~j; --j)
				for (int k = 255; ~k; --k) {
					f[j][k] = (p[0][j][k] + p[1][j][k] - f[j][k]) % mod + mod;
					while (f[j][k] >= mod) f[j][k] -= mod;
				}
		}
	}
	for (int j = 255; ~j; --j)
		for (int k = 255; ~k; --k)
			if ((j & k) == 0) mov(ans, f[j][k]);
	printf("%d\n", ans);
	return 0;
}
