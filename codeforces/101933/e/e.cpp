// by OwenCreeper
#include "bits/stdc++.h"
#define Base 131
#define SZ 10007
#define MAX 5000000
using namespace std;
vector <unsigned int> V[SZ];
vector <int> G[SZ];
int pcnt = 0;
double dp[MAX + 5];
unsigned int HS(int A[], int n, int B[], int m, int d) {
	unsigned int has = 0;
	has *= Base, has += n;
	for (int i = 1; i <= n; i++)
		has *= Base, has += A[i];
	has *= Base, has += m;
	for (int i = 1; i <= m; i++)
		has *= Base, has += B[i];
	has *= Base, has += d;
	return has;
}
bool cmp(int x, int y) { return x > y; }
int check(unsigned int has) {
	int pos = has % SZ;
	for (int i = 0; i < V[pos].size(); i++) 
		if (V[pos][i] == has)
			return G[pos][i];
	return 0;
}
int getNew(unsigned int has) {
	int pos = has % SZ, p = ++pcnt;
	V[pos].push_back(has);
	G[pos].push_back(p);
	dp[p] = 0;
	return p;
}
double solve(int A[], int n, int B[], int m, int d, int sm1, int sm2) {
	if (d >= sm1) return 1;
	if (d < sm2) return 0;
	int AA[6] = {0}, BB[6] = {0};
	for (int i = 1; i <= n; i++) AA[i] = A[i];
	for (int i = 1; i <= m; i++) BB[i] = B[i];
	sort(AA + 1, AA + 1 + n, cmp), sort(BB + 1, BB + 1 + m, cmp);
	while (!AA[n] && n) n--;
	while (!BB[m] && m) m--;
	if (m == 0) return 1;
	int tmp;
	unsigned int has = HS(AA, n, BB, m, d);
	if (tmp = check(has)) return dp[tmp];
	tmp = getNew(has);
	for (int i = 1; i <= n; i++)
		AA[i]--, dp[tmp] += solve(AA, n, BB, m, d - 1, sm1 - 1, sm2) / (n + m), AA[i]++;
	for (int i = 1; i <= m; i++)
		BB[i]--, dp[tmp] += solve(AA, n, BB, m, d - 1, sm1 - 1, sm2 - 1) / (n + m), BB[i]++;
	// printf("d = %d\n", d);
	// for (int i = 1; i <= n; i++) printf("%d ", AA[i]); puts("");
	// for (int i = 1; i <= m; i++) printf("%d ", BB[i]); puts("");
	// printf("%.2f\n", dp[tmp]);
	return dp[tmp];
}
int a[6], b[6];
int main(int argc, char const *argv[]) {
	int n, m, d, sm1 = 0, sm2 = 0;
	scanf("%d%d%d", &n, &m, &d);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), sm1 += a[i];
	for (int i = 1; i <= m; i++) scanf("%d", b + i), sm1 += b[i], sm2 += b[i];
	printf("%.8f\n", solve(a, n, b, m, d, sm1, sm2));
	return 0;
}
