#include <cstdio>
#include <cstring>
const int N = 1e5 + 3;
char s[N], S[N];
int pre[N], ch[26][N], l[N], cnd, len[N], last, xn, siz[N];
void cmax(int &a, const int &b) {
	if (a < b) a = b;
}
void init() {
	pre[0] = pre[1] = 1;
	l[1] = -1;
	for (int i = 2; i <= cnd; ++i)
		l[i] = 0;
	for (int i = 0; i < 26; ++i)
		for (int j = 0; j <= cnd; ++j)
			ch[i][j] = 0;
	cnd = 1;
	xn = 0;
	*S = -1;
}
int insert(char c) {
	static int v, k;
	S[++xn] = c;
	while (S[xn - l[last] - 1] ^ S[xn])
		last = pre[last];
	if (!ch[c][last]) {
		v = ++cnd;
		l[v] = l[last] + 2;
		k = pre[last];
		while (S[xn - l[k] - 1] ^ S[xn]) k = pre[k];
		pre[v] = ch[c][k];
		ch[c][last] = v;
	}
	last = ch[c][last];
	++siz[last];
	return last;
}
int main() {
	int n = 1, ans = 0;
	scanf("%s", s + 1);
	init();
	for (; s[n]; ++n)
		len[n] = l[insert(s[n] - 'a')];
	init();
	for (int i = n - 1; i; --i)
		cmax(ans, len[i - 1] + l[insert(s[i] - 'a')]);
	printf("%d\n", ans);
	return 0;
}
