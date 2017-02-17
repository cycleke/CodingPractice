#include <cstdio>
#include <algorithm>

#define N 50003

int tr[2][N], trend, a[N], ha[N], _tr;
int f[230][N], bel[N];

void add(int x) {
	for (; x < trend; x += x & -x) {
		if (tr[0][x] ^ _tr) {
			tr[0][x] = _tr;
			tr[1][x] = 0;
		}
		++tr[1][x];
	}
}

int sum(int x) {
	static int r;
	for (r = 0; x; x ^= x & -x) 
	  if (tr[0][x] >= _tr)
		r += tr[1][x];
	return r;
}

struct node {
	int sum;
	node *ls, *rs;
} mset[N * 20], *nodeit = mset, *rt[N];

void Insert(node *x, node * &y, int l, int r, const int &p) {
	*(y = ++nodeit) = *x;
	++y->sum;
	if (l >= r) return;
	int m = (l + r) >> 1;
	if (p <= m)
	  Insert(x->ls, y->ls, l, m, p);
	else
	  Insert(x->rs, y->rs, m + 1, r, p);
}

void Query(node *x, node * &y, int l, int r, const int &p, int &v) {
	if (r < p)
	  return (void)(v += y->sum - x->sum);
	int m = (l + r) >> 1;
	if (m + 1 < p)
	  Query(x->rs, y->rs, m + 1, r, p, v);
	Query(x->ls, y->ls, l, m, p, v);
}

int main() {
	//freopen("t.in", "r", stdin);

	int n, m, l, r, i, j, *end, blo, ans = 0;
	scanf("%d", &n);
	for (blo = 1; blo * blo <= n; ++blo);
	//blo = 28;
	for (i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		bel[i] = (i - 1) / blo + 1;
		ha[i] = a[i];
	}
	std::sort(ha + 1, ha + n + 1);
	end = std::unique(ha + 1, ha + n + 1);
	trend = end - ha;

	*rt = mset;
	**rt = (node) {0, *rt, *rt};

	for (i = 1; i <= n; ++i) {
		a[i] = std::lower_bound(ha + 1, end, a[i]) - ha;
		Insert(rt[i - 1], rt[i], 1, trend - 1, a[i]);
	}

	for (i = 1; i <= bel[n]; ++i) {
		++_tr;
		for (j = (i - 1) * blo + 1; j <= n; ++j) {
			f[i][j] = f[i][j - 1] + sum(trend - 1) - sum(a[j]);
			add(a[j]);
		}
	}

	scanf("%d", &m);

	while (m--) {
		scanf("%d%d", &l, &r);
		//printf("%d\n", m);
		l ^= ans, r ^= ans;
		if (bel[l] ^ bel[r]) {
			ans = f[bel[l] + 1][r];
			for (i = l, j = bel[l] * blo + 1; i < j; ++i) 
			  if (a[i] > 1) Query(rt[i], rt[r], 1, trend - 1, a[i], ans);
		} else {
			ans = 0;
			++_tr;
			for (i = l; i <= r; ++i) {
				ans += sum(trend - 1) - sum(a[i]);
				add(a[i]);
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}
