#include <cstdio>
#include <algorithm>

#define N 50005
#define Max_Num 1000005

struct ask {
	int l, r, t, id, _l, _r;
	bool operator < (const ask &a) const {
		return (_l ^ a._l) ? (_l < a._l) : ((_r ^ a._r) ? _r < a._r : t < a.t);
	}
}q[N];

struct chg {
	int x, y, pre;
}p[N];

int cnt[Max_Num], a[N], _a[N], ans[N];

#define ins(x) (!cnt[x]++) ? ++now : 0
#define del(x) (!--cnt[x]) ? --now : 0

int main() {
	int n, m, l, r, _l, _r, blo, ct = 0, _q = 0, _p = 0, now = 0;
	char ops[3];
	scanf("%d%d", &n, &m);
	for (blo = 1; blo * blo * blo <= n; ++blo);
	blo *= blo;
	for (int i = 0; i < n; ++i)
	  scanf("%d", a + i), _a[i] = a[i];
	for (int i = 1; i <= m; ++i) {
		scanf("%s%d%d", ops, &l, &r);
		if (*ops == 'Q') {
			--r;
			q[_q] = (ask){l, r, _p, _q, l / blo, r / blo};
			++_q;
		}
		else {
			p[++_p] = (chg){l, r, _a[l]};
			_a[l] = r;
		}
	}
	std::sort(q, q + _q);
	l = 1, r = 0;
	for (int i = 0; i < _q; ++i) {
		_l = q[i].l, _r = q[i].r;
		while (ct < q[i].t) {
			++ct;
			if (p[ct].x >= l && p[ct].x <= r) {
				del(a[p[ct].x]);
				ins(p[ct].y);
			}
			a[p[ct].x] = p[ct].y;
		}
		while (q[i].t < ct) {
			if (p[ct].x >= l && p[ct].x <= r) {
				del(a[p[ct].x]);
				ins(p[ct].pre);
			}
			a[p[ct].x] = p[ct].pre;
			--ct;
		}
		while (l < _l) del(a[l]), ++l;
		while (_l < l) --l, ins(a[l]);
		while (r < _r) ++r, ins(a[r]);
		while (_r < r) del(a[r]), --r;
		ans[q[i].id] = now;
	}
	for (int i = 0; i < _q; ++i)
	  printf("%d\n", ans[i]);
	return 0;
}
