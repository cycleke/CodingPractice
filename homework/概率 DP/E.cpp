#include <cmath>
#include <cstdio>
#include <iostream>
/*
(i >= j)
f[i][1] = p1 * f[i][1] + p2 * f[i][i] + p4
f[i][j] = p1 * f[i][j] + p2 * f[i][j-1] + p3 * f[i-1][j-1] + p4 | 1 < j <= k
f[i][j] = p1 * f[i][j] + p2 * f[i][j-1] + p3 * f[i-1][j-1]      | k < j <= i

f[i][1] = _p2 * f[i][i] + _p4
f[i][j] = _p2 * f[i][j-1] + _p3 * f[i-1][j-1] + _p4 | 1 < j <= k
f[i][j] = _p2 * f[i][j-1] + _p3 * f[i-1][j-1]       | k < j <= i

c[j] = { _p4					 | j == 1
	   { _p3 * f[i-1][j-1] + _p4 | 1 < j <= k
       { _p3 * f[i-1][j-1]       | k < j <= i

*/
const double eps = 1e-9;
double f[2010][2010], c[2010];
int main() {
	int N, M, K;
	double p1, p2, p3, p4, tmp, p;
	double _p2, _p3, _p4;
	while (scanf("%d%d%d%lf%lf%lf%lf", &N, &M, &K, &p1, &p2, &p3, &p4) == 7) {
		if (p4 < eps) { puts("0.00000"); continue; }
		_p2 = p2 / (1 - p1);
		_p3 = p3 / (1 - p1);
		_p4 = p4 / (1 - p1);
		f[1][1] = p4 / (1 - p1 - p2); 
		for (int i = 2; i <= N; ++i) {
			for (int j = 2; j <= K && j <= i; ++j)
				c[j] = _p3 * f[i-1][j-1] + _p4;
			for (int j = K + 1; j <= i; ++j)
				c[j] = _p3 * f[i-1][j-1];
			tmp = 0; p = 1;
			for (int j = i; j > 1; --j) {
				tmp += c[j] * p;
				p *= _p2;
			}
			f[i][i] = (tmp + p * _p4) / (1 - p * _p2);
			f[i][1] = _p2 * f[i][i] + _p4;
			for (int j = 2; j < i; ++j)
			f[i][j] = _p2 * f[i][j-1] + c[j];
		}
		printf("%.5lf\n", f[N][M]);
	}
		
	return 0;
}
