#include <cstdio>
const int N = 300003;
char s[N];
int fa[N], l[N], cnd, ch[26][N], siz[N], last;
long long ans;
void ca(const long long &t) {
	if (ans < t) ans = t;
}
int main() {
	gets(s+1);
	//scanf("%s", s+1);
	fa[0] = fa[1] = 1;
	l[1] = -1;
	cnd = 1;
	for (int i = 1, v, k; s[i]; ++i) {
		int &u = last;
		while (s[i - l[u] - 1] ^ s[i]) u = fa[u];
		if (!ch[s[i] - 'a'][u]) {
			v = ++cnd;
			k = fa[u];
			l[v] = l[u] + 2;
			while (s[i - l[k] - 1] ^ s[i]) k = fa[k];
			fa[v] = ch[s[i] - 'a'][k];
			ch[s[i] - 'a'][u] = v;
		}
		u = ch[s[i] - 'a'][u];
		++siz[u];
	}
	for (int i = cnd; i; --i) {
		siz[fa[i]] += siz[i];
		ca((long long)siz[i] * l[i]);
	}
	printf("%lld\n", ans);
}
