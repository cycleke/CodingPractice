#include <cstdio>
#include <algorithm>

int a[12];
double B[2][2];
int N; double p, ans;
double tmp[2][2], s[2];

double Cal(int n) {
	B[1][0] = 1, B[1][1] = 0;
	B[0][0] = p; B[0][1] = 1 - p;
	s[0] = 1; s[1] = 0;
	while (n) {
		if (n & 1) {
			for (int i = 0; i < 2; ++i) {
				tmp[0][i] = 0;
				for (int j = 0; j < 2; ++j)
				tmp[0][i] += B[i][j] * s[j];
			}
			for (int i = 0; i < 2; ++i) s[i] = tmp[0][i];
		}
		for (int i = 0; i < 2; ++i) 
			for (int j = 0; j < 2; ++j) {
				tmp[i][j] = 0;
				for (int k = 0; k < 2; ++k)
				tmp[i][j] += B[i][k] * B[k][j];
			}
		for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
		B[i][j] = tmp[i][j];
		n >>= 1;
	}
	return s[0];
}

int main() {
	
	a[0] = 0;
	while (scanf("%d%lf", &N, &p) != EOF) {
		for (int i = 1; i <= N; ++i) scanf("%d", a + i);
		std::sort(a,a+N+1);
		ans = 1;
		for (int i = 0; i < N; ++i)
		ans *= 1 - Cal(a[i+1] - a[i] - 1);
		printf("%.7lf\n", ans);
	}
	return 0;
}
