#include <cstdio>
#include <cstring>

#define N 1000005
#define mo 1000000007

int v[N], phi[N];

int main() {
	int n, ans;
	scanf("%d", &n);
	for (int i = 2; i <= n; ++i)
		if (!v[i]) for (int j = i; j <= n; j += i)
			v[j] = i;
	phi[1] = 1;
	for (int i = 2; i <= n; ++i)
		if (v[i] ^ v[i / v[i]])
			phi[i] = phi[i / v[i]] * (v[i] - 1);
		else
			phi[i] = phi[i / v[i]] * v[i];
	ans = 1;
	for (int i = 2; i <= n; ++i)
		ans = (long long)ans * phi[i] % mo;
	printf("%d\n", ans);
	return 0;
}
