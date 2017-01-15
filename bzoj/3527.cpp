#include <cmath>
#include <cstdio>
#include <algorithm>
#define N 100009
#define LEN 1199999
struct complex {
	double x, i;
	complex(double _x = 0, double _i = 0) : x(_x), i(_i) {}
	complex operator + (const complex &a) {return complex(x + a.x, i + a.i);}
	complex operator - (const complex &a) {return complex(x - a.x, i - a.i);}
	complex operator * (const complex &a) {return complex(x * a.x - i*a.i, x * a.i + i * a.x);}
}a[LEN], b[LEN];
int rev[LEN];
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
	int n, m, len, i, j;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%lf", &a[i].x);
	for (i = 1; i < n; ++i) b[i].x = -1.0 / (n - i) / (n - i), b[i + n].x = 1.0 / i / i;
	m = (n << 1) + n;
	for (n = 1, len = 0; n <= m; n <<= 1) ++len;
	for (i = 0; i < n; ++i) rev[i] = (rev[i>>1]>>1)|((i&1)<<len-1);
	fft(a, n, 1); fft(b, n, 1);
	for (i = 0; i <= n; ++i) a[i] = a[i] * b[i];
	fft(a, n, -1);
	for (i = m / 3, m = i << 1; i < m; ++i) printf("%.3lf\n", a[i].x / n);
	return 0;
}
