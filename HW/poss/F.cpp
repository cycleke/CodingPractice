#include <cstdio>
#include <cmath>
#include <cstring>
double f[1010][1010];
double p[1010][1010][3];
const double eps = 1e-9;
int main() {
	int R, C;
	while (scanf("%d%d", &R, &C) == 2) {
		for (int i = 1; i <= R; ++i)
		for (int j = 1; j <= C; ++j)
		for (int k = 0; k < 3; ++k)
		scanf("%lf", &p[i][j][k]);
		memset(f, 0, sizeof f);
		f[R][C] = 0;
		for (int i = R; i; --i)
		for (int j = C; j; --j)
		if (i ^ R || j ^ C) {
			if (p[i][j][0] == 1) continue;
			f[i][j] = (p[i][j][1] * f[i][j+1] + p[i][j][2] * f[i+1][j] + 2) / (1 - p[i][j][0]);
		} 
		printf("%.3lf\n", f[1][1]);
	}
	
	
	
	return 0;
}
