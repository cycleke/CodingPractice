// by OwenCreeper
#include "bits/stdc++.h"
#define Base 131
#define SZ 100
#define MAX 5000000
#define N 100
using namespace std;
typedef long long ll;
int p[N + 5], c[N + 5], t[N + 5], r[N + 5], l, m;
char s[SZ], Name[SZ + 5][SZ + 5];
bool use[SZ + 5];
int main(int argc, char const *argv[]) {
	scanf("%d%d", &l, &m);
	char ch = getchar();
	while (ch != '\n') ch = getchar();
	memset(p, 0, sizeof(p));
	memset(c, 0, sizeof(c));
	memset(t, 0, sizeof(t));
	memset(r, 0, sizeof(r));
	int ans = 1e6, ttt = 0;
	for (int j = 1; j <= m; j++) {
		gets(s);
		// printf("s = %s\n", s);
		int n = strlen(s);
		for (int i = 0; i < n; i++)
			if (s[i] == ',') {
				sscanf(s + i + 1, "%d,%d,%d,%d", p + j, c + j, t + j, r + j);
				s[i] = 0;
				break;
			}
		// printf("%s %d %d %d %d\n", s, p[j], c[j], t[j], r[j]);
		int pr = t[j], pc = t[j] + r[j], T = 10080, flag = 1, cs = 0;
		ll ctot = 0;
		do {
			int stp = min(pr, min(pc, T));
			pr -= stp, pc -= stp, T -= stp;
			if (flag) ctot += c[j] * stp;
			// printf("stp = %d ctot = %d\n", stp, ctot);
			if (!T) {
				T = 10080, cs++;
				if (ctot < l * 1ll * cs) use[j] = 1;
			}
			if (pr == 0) pr = t[j] + r[j], flag = 0;
			if (pc == 0) pc = t[j] + r[j], flag = 1;
		} while (!(pr == t[j] && pc == t[j] + r[j] && T == 10080) && !use[j]);
		if (!use[j]) ans = min(ans, p[j]), ttt++;
		for (int i = 0; i <= strlen(s); i++) Name[j][i] = s[i]; 
	}
	if (!ttt) puts("no such mower");
	for (int i = 1; i <= m; i++)
		if (!use[i] && p[i] == ans)
			printf("%s\n", Name[i]);
	return 0;
}
