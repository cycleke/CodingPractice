#include <cstdio>
#include <algorithm>

#define N 50003

struct query {
	int l, r, _l, id;
	bool operator < (const query &a) const {
		return (_l ^ a._l) ? _l < a._l : r < a.r;
	}
}q[N];

int tr[N], ha[N], a[N], trend;

void add(int x, const int &delta) {
	for (; x < trend; x += x & -x)
	  tr[x] += delta;
}

int sum(int x) {
	static int r;
	for (r = 0; x; x ^= x & -x)
	  r += tr[x];
	return r;
}

int main() {
	int n, _q, i, l, r, blo, _l, _r, ct = 0, *end;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		ha[i] = a[i];
	}
	std::sort(ha + 1, ha + n + 1);
	end = std::unique(ha + 1, ha + n + 1);
	trend = end - ha;
	for (i = 1; i <= n; ++i)
	  a[i] = std::lower_bound(ha + 1, end, a[i]) - ha;
	for (blo = 1; blo * blo <= n; ++blo);
	scanf("%d", &_q);
	for (i = 0; i < _q; ++i) {
		scanf("%d%d", &l, &r);
		q[i] = (query) {l, r, l / blo, i};
	}
	std::sort(q, q + _q);
	l = 1, r = 0;
	for (i = 0; i < _q; ++i) {
		_l = q[i].l, _r = q[i].r;
		while (l < _l) {
			add(a[l], -1);
			ct -= sum(a[l] - 1);
			++l;
		}
		while (_r < r) {
			add(a[r], -1);
			ct -= r - l - sum(a[r]);
			--r;
		}
		while (_l < l) {
			--l;
			add(a[l], 1);
			ct += sum(a[l] - 1);
		}
		while (r < _r) {
			++r;
			add(a[r], 1);
			ct += r - l + 1 - sum(a[r]);
		}
		ha[q[i].id] = ct;
	}
	for (i = 0; i < _q; ++i)
	  printf("%d\n", ha[i]);
	return 0;
}
