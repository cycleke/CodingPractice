// by OwenCreeper
#include "bits/stdc++.h"
using namespace std;
void solve(int n, int m, int &x, int &y) {
	if (n == 1) {
		x = 1, y = 1;
		return ;
	}
	if ((m - 1) / (n * n / 4) == 0) solve(n / 2, m, y, x); else
	if ((m - 1) / (n * n / 4) == 1) solve(n / 2, m - (n * n / 4), x, y), y += n / 2; else
	if ((m - 1) / (n * n / 4) == 2) solve(n / 2, m - 2 * (n * n / 4), x, y), x += n / 2, y += n / 2; else
	if ((m - 1) / (n * n / 4) == 3) solve(n / 2, m - 3 * (n * n / 4), y, x), x = n - x + 1, y = n / 2 - y + 1; 
	// printf("solve %d %d = %d %d\n", n, m, x, y);
}
int main(int argc, char const *argv[]) {
	int n, m;
	scanf("%d%d", &n, &m);
	int x1, y1;
	solve(n, m, x1, y1);
	printf("%d %d\n", x1, y1);
	return 0;
}
