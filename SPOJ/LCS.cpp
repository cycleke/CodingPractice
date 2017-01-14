#include <cstdio>
#include <cstring>

const int N =  2 * 250003;

int last, cnd, ch[N][26], pre[N], step[N];
char s[N];
void insert(char x) {
	static int p, q, np, nq;
	np = ++cnd;
	p = last;
	step[np] = step[p] + 1;
	for (; p && ! ch[p][x]; p = pre[p]) ch[p][x] = np;
	if (!p) pre[np] = 1;
	else {
		q = ch[p][x];
		if (step[q] == step[p] + 1) pre[np] = q;
		else {
			nq = ++cnd;
			step[nq] = step[p] + 1;
			memcpy(ch[nq], ch[q], sizeof ch[nq]);
			pre[nq] = pre[q];
			pre[q] = pre[np] = nq;
			for (; p && ch[p][x] == q; p = pre[p]) ch[p][x] = nq;
		}
	}
	last = np;
}

int main() {
	scanf("%s", s);
	int ans = 0;
	cnd = last = 1;
	for (char *i = s; *i; ++i) insert(*i - 'a');
	int u = 1, len = 0;
	char x;
	scanf("%s", s);
	for (char *i = s; *i; ++i) {
		x = *i - 'a';
		if (ch[u][x]) {
			++len;
			u = ch[u][x];
		} else {
			while (!ch[u][x] && u) u = pre[u];
			if (!u) u = 1, len = 0;
			else len = step[u] + 1,u = ch[u][x];
		}
		if (ans < len) ans = len;
	}
	printf("%d\n", ans);
	return 0;
}
