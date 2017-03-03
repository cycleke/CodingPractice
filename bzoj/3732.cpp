#include <cstdio>

const int MaxN = 100003, MaxM = 200003, MaxQ = 100003;

struct ask {
	int id, s[4], size;
	void read(const int &id) {
		this->id = id;
		scanf("%d", &size);
		for (int i = 0; i < size; ++i)
		  scanf("%d", s + i);
	}
	const int & operator [] (const int &i) const {
		return s[i];
	}
}q[MaxQ];

struct edge {
	int u, v;
	void read() {
		scanf("%d%d", &u, &v);
	}
}e[MaxM];

int f[MaxN], stk[MaxM * 10], *top = stk, ans[MaxQ], mark[MaxM], _mark;

int gf(int u) {
	if (f[u] == u) return u;
	*top++ = u, *top++ = f[u];
	return f[u] = gf(f[u]);
}

void uni(int u, int v) {
	if (gf(u) == gf(v)) return;
	*top++ = f[v], *top++ = f[f[v]];
	f[f[v]] = f[u];
}

void divide(int l, int r) {
	int *ctop = top, mid = (l + r) >> 1, i, j;
	if (l == r) {
		int t = 1;
		for (int i = 0; i < q[l].size; ++i)
		  if (gf(e[q[l][i]].u) ^ gf(e[q[l][i]].v)) {
			  t = 0;
			  break;
		  }
		ans[q[l].id] = t;
		for (; top > ctop; top -= 2)
		  f[top[-2]] = top[-1];
		return;
	}

	++_mark;
	for (i = l; i <= mid; ++i)
	  for (j = 0; j < q[i].size; ++j)
		mark[q[i][j]] = _mark;
	for (i = mid + 1; i <= r; ++i)
	  for (j = 0; j < q[i].size; ++j)
		if (mark[q[i][j]] ^ _mark) uni(e[q[i][j]].u, e[q[i][j]].v);
	divide(l, mid);
	for (; top > ctop; top -= 2)
	  f[top[-2]] = top[-1];

	++_mark;
	for (i = mid + 1; i <= r; ++i)
	  for (j = 0; j < q[i].size; ++j)
		mark[q[i][j]] = _mark;
	for (i = l; i <= mid; ++i)
	  for (j = 0; j < q[i].size; ++j)
		if (mark[q[i][j]] ^ _mark) uni(e[q[i][j]].u, e[q[i][j]].v);
	divide(mid + 1, r);
	for (; top > ctop; top -= 2)
	  f[top[-2]] = top[-1];
}

int main() {
	//freopen("t.in", "r", stdin);
	int n, m, k;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
	  e[i].read();

	scanf("%d", &k);
	for (int i = 0; i < k; ++i) q[i].read(i);

	++_mark;
	for (int i = 0, j; i < k; ++i)
	  for (j = 0; j < q[i].size; ++j)
		mark[q[i][j]] = _mark;

	for (int i = 1; i <= n; ++i)
	  f[i] = i;

	for (int i = 1; i <= m; ++i)
	  if (!mark[i]) uni(e[i].u, e[i].v);

	divide(0, k - 1);
	for (int i = 0; i < k; ++i)
	  puts(ans[i] ? "Connected" : "Disconnected");
	return 0;
}
