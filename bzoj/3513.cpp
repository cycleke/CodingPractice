#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 399999
struct complex {
    double x, i;
    complex(double _x = 0, double _i = 0) : x(_x), i(_i) {}
    complex operator + (const complex &a) {return complex(x + a.x, i + a.i);}
    complex operator - (const complex &a) {return complex(x - a.x, i - a.i);}
    complex operator * (const complex &a) {return complex(x * a.x - i*a.i, x * a.i + i * a.x);}
}a[N];
int rev[N], s[N];
const double pi = acos(-1.0);
void fft(complex *a, int n, int flag) {
    static int i, j, k; static complex t1, t2;
    for (i = 0; i < n; ++i) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (i = 1; i < n; i <<= 1) {
        complex wn(cos(pi/i), flag * sin(pi/i));
        for (j = 0; j < n; j += (i << 1)) {
            complex w(1, 0);
            for (k = 0; k < i; ++k) {
                t1 = a[j + k], t2 = w * a[i + j + k];
                a[j + k] = t1 + t2;
                a[i + j + k] = t1 - t2;
                w = w * wn;
            }
        }
    }
}
int main() {
	int __, n, i, x, mx, len, ___;
	long long tot, pre;
	scanf("%d", &__);
	while (__--) {
		scanf("%d", &n);
		___ = n;
		memset(s, 0, sizeof s);
		memset(a, 0, sizeof a);
		mx = -1;
		while (n--) {
			scanf("%d", &x);
			mx = std::max(mx, x);
			++s[x];
		}
		++mx;
		for (i = 1; i < mx; ++i) a[i].x = s[i];
		for (n = 1, len = 0; n <= (mx<<1); n <<= 1) ++len;
		for (i = 0; i < n; ++i) rev[i] = (rev[i>>1]>>1)|((i&1)<<len-1);
		fft(a, n, 1);
		for (i = 0; i <= n; ++i) a[i] = a[i] * a[i];
		fft(a, n, -1);
		tot = pre = 0LL;
		for (i = 0; i <= mx; ++i) {
			pre += a[i].x / n + 0.5;
			if (~i & 1) pre -= s[i >> 1];
			tot += pre * s[i];
		}
		tot >>= 1;
		pre = (long long)___ * (___ - 1) * (___ - 2) / 6LL;
		printf("%.7lf\n", 1 - (double)tot / pre);
	}
	return 0;
}
