#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 511111

typedef int arr[N];
typedef char str[7654321];

struct ac_am {
	int tot;
	bool cnt[N];
	queue<int> q;
	arr c[2], fail, tri[2], val;
	inline int newnode() {
		val[tot] = cnt[tot] = 0;
		c[0][tot] = c[1][tot] = 0;
		tri[0][tot] = tri[1][tot] = 0;
		return tot++;
	}
	inline void init() {
		tot = 0;
		newnode();
	}
	bool search(char *s) {
		int now = 0;
		for (char *it = s; *it; ++it)
			if (!(now = tri[*it - '0'][now]))
				return false;
		return cnt[now];
	}
	void insert(char *s) {
		int now = 0;
		for (char *it = s; *it; ++it) {
			if (!tri[*it - '0'][now])
				tri[*it - '0'][now] = newnode();
			now = tri[*it - '0'][now];
		}
		cnt[now] = true;
	}
	void build_fail()  {
		int u = 0, f, e;
		for (int i = 0; i < tot; ++i) fail[i] = 0;
		if (tri[0][u]) {
			q.push(tri[0][u]);
			val[c[0][u] = tri[0][u]] = cnt[tri[0][u]];
		}
		if (tri[1][u]) {
			q.push(tri[1][u]);
			val[c[1][u] = tri[1][u]] = cnt[tri[1][u]];
		}
		while (!q.empty()) {
			u = q.front();
			q.pop();
			if (tri[0][u]) {
				c[0][u] = e = tri[0][u];
				f = fail[u];
				fail[e] = c[0][f];
				val[e] = val[fail[e]] + cnt[e];
				q.push(e);
			} else
				c[0][u] = c[0][fail[u]];
			if (tri[1][u]) {
				c[1][u] = e = tri[1][u];
				f = fail[u];
				fail[e] = c[1][f];
				val[e] = val[fail[e]] + cnt[e];
				q.push(e);
			} else
				c[1][u] = c[1][fail[u]];
		}
	}
	long long getsum(char *s) {
		int now = 0;
		long long ans = 0;
		for (char *it = s; *it; ++it) {
			now = c[*it - '0'][now];
			ans += val[now];
		}
		return ans;
	}
}ac, buf;

void dfs(int u1, int u2) {
	int e1, e2, i;
	for (i = 0; i ^ 2; ++i)
		if (buf.tri[i][u2]) {
			e2 = buf.tri[i][u2];
			if (!ac.tri[i][u1])
				ac.tri[i][u1] = ac.newnode();
			e1 = ac.tri[i][u1];
			ac.cnt[e1] |= buf.cnt[e2];
			dfs(e1, e2);
		}
}
str s, s1;

int main() {
	//freopen("t.in", "r", stdin);
	int _, n, len, i, j;
	long long lastans;
	scanf("%d", &_);
	for (int __ = 0; __ < _ && (printf("Case #%d:\n", ++__), 1); ) {
		ac.init();
		buf.init();
		scanf("%d", &n);
		lastans = 0LL;
		while (n--) {
			scanf("%s", s1);
			len = strlen(s1 + 1);
			*s = *s1;
			for (i = 0; i < len; ++i)
				s[1 + i] = s1[1 + (i + lastans % len + len) % len];
			s[len + 1] = 0;
			if (*s == '+') {
				i = buf.search(s + 1);
				j = ac.search(s + 1);
				if (i || j)
					continue;
				buf.insert(s + 1);
				buf.build_fail();
				if (buf.tot > 2000) {
					dfs(0, 0);
					buf.init();
					ac.build_fail();
				}
			} else {
				lastans = ac.getsum(s + 1) + buf.getsum(s + 1);
				printf("%lld\n", lastans);
			}
		}
	}
	return 0;
}
