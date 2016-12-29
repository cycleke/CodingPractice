#include <cstdio>
#include <cstring>
#define MS 4000000
int ch[MS][26], totNode, K, ans;
char s[1520], like[30];

#define init(u) memset(ch[u], 0, sizeof ch[u])

void Search(char *str) {
	int cnt = 0, u = 0; char c;
	while (*str) {
		c = (*str++) - 'a';
		if (like[c]^'1') ++cnt;
		if (K < cnt) break;
		if (!ch[u][c]) {
			++ans; ch[u][c] = ++totNode;
			init(totNode);
		}
		u = ch[u][c];
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		ans = totNode = 0;
		init(0);
		scanf("%s", s); scanf("%s", like);
		scanf("%d", &K);
		for (char *str = s; *str; ++str)
		  Search(str);
		printf("%d\n",ans);
	}
	return 0;
}
