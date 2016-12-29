#include <cstdio>
#include <cmath>
long double v[13][13];

int main() {
	int n, t, ans = 0;
	scanf("%d%d", &n, &t);
	while (t--) {
		v[1][1] += 1.;
		for (int i = 1; i <= n; ++i)
		  for (int j = 1; j <= i; ++j) {
			  if (v[i][j] < 1.) continue;
			  long double res = v[i][j] - 1;
			  v[i][j] = 1.;
			  v[i+1][j] += res / 2.;
			  v[i+1][j+1] += res / 2.;
		  }
	}
	for (int i = 1; i <= n; ++i)
	  for (int j = 1; j <= i; ++j)
		if (fabs(v[i][j] - 1.) < 1e-6) ++ans;
	printf("%d\n", ans);
	return 0;
}
