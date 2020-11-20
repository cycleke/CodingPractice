#include <cstdio>
#include <cstring>

int a[10][3];

int main() {
	a[0][0] = 0;
	a[0][1] = 1;
	a[0][2] = 2;
	for (int i = 0; i < 6; ++i)
			if (i & 1) {
				a[i + 1][0] = a[i][0];
				a[i + 1][1] = a[i][2];
				a[i + 1][2] = a[i][1];
			} else {
				a[i + 1][0] = a[i][1];
				a[i + 1][1] = a[i][0];
				a[i + 1][2] = a[i][2];
			}
	int n, x;
	scanf("%d%d", &n, &x);
	printf("%d\n", a[n % 6][x]);
	return 0;
}
