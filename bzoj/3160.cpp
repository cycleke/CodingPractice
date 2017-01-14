#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = (1 << 19) + 13, mo = 1e9 + 7;
const double pi = acos(-1.0);
struct complex {
	double x, y;
	complex(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
	complex operator - (const complex &a) const {return complex(x - a.x, y - a.y);}
	complex operator + (const complex &a) const {return complex(x + a.x, y + a.y);}
	complex operator * (const complex &a) const {return complex(x * a.x - y * a.y, x * a.y + y * a.x);}
}a[N], b[N], c[N];
int rev[N], pw[N], p[N];
char s[N], str[N];
void fft(complex *a, int n, int flag) {
	static int i, j, k;
	for (i = 0; i < n; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (i = 1; i < n; i <<= 1) {
		complex wn(cos(pi/i), sin(flag*pi/i)), t1, t2;
		for (j = 0; j < n; j += (i<<1)) {
			complex w(1, 0);
			for (k = 0; k < i; ++k, w = w * wn) {
				t1 = a[j + k], t2 = w * a[j + k + i];
				a[j + k] = t1 + t2;
				a[j + k + i] = t1 - t2;
			}
		}
	}
}

int mancher() {
	int i = 0, j = 1, ret = 0;
	str[0] = '~';
	str[1] = '!';
	for (; s[i + 1]; ++i) str[++j] = s[i + 1], str[++j] = '!';
	for (i = 1, j = 0; str[i]; ++i) {
		if (p[j] + j > i) p[i] = min(p[2 * j - i], p[j] + j - i);
		else p[i] = 1;
		while (str[i + p[i]] == str[i - p[i]]) ++p[i];
		if (i + p[i] > j + p[j]) j = i;
		ret += p[i] >> 1;
		while (ret >= mo) ret -= mo;
	}
	return ret;
}

int main() {
	freopen("t.in", "r", stdin);
	int n, i, len, nn, t;
	long long ans = 0;
	scanf("%s", s + 1);
	for (n = 1; s[n]; ++n)
		if (s[n] == 'a') a[n].x = 1;
		else b[n].x = 1;
	--n; n <<= 1;
	for (nn = 1, len = 0; nn <= n; nn <<= 1) ++len;
	for (i = 0; i < nn; ++i) rev[i] = (rev[i>>1]>>1)|((i&1)<<len-1);
	fft(a, nn, 1); fft(b, nn, 1);
	for (i = 0; i < nn; ++i) c[i] = a[i] * a[i] + b[i] * b[i];
	fft(c, nn, -1);
	for (i = *pw = 1; i <= nn; ++i) if ((pw[i] = pw[i - 1] << 1) >= mo) pw[i] -= mo;
	for (i = 0; i < nn; ++i) {
		t = c[i].x / nn + 0.5;
		//printf("%d %d\n", i, t);
		ans = (ans + pw[(t + 1) >> 1] - 1);
		for (; ans >= mo; ) ans -= mo;
	}
	ans = ans + mo - mancher();
	while (ans >= mo) ans -= mo;
	printf("%d\n", (int)ans);
	return 0;
}
