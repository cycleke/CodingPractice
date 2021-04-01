#include <cstdio>
#include <cstring>

//input
const int buffer_size = (1 << 16) ^ 1;
char buffer[buffer_size], *cbuf(buffer), *ebuf(buffer);
inline char get_char() {
	if (cbuf == ebuf) {
		cbuf = buffer;
		ebuf = buffer + fread(buffer, 1, buffer_size, stdin);
	}
	return (cbuf == ebuf) ? EOF : *cbuf++;
}
inline void getusint(int &a) {
	register char c;
	while (c = get_char(), c < '0');
	a = c - '0';
	while (c = get_char(), '-' < c)
		a = (a << 3) + (a << 1) + c - '0';
}

//main
const int N = 3e5 + 7, pool_size = N * 50;
int n, m, q, cur, count[N];
struct seg_node {
	int size;
	long long value;
	seg_node *ls, *rs;
	inline void get_size(int l, int r) {
		if (cur == n + 1) {
			if (r <= n) size = r - l + 1;
			else if (l <= n) size =  n - l + 1;
			else size = 0;
		} else {
			if (r < m) size = r - l + 1;
			else if (l < m) size = m - l;
			else size = 0;
		}
	}
} pool[pool_size], *cp(pool), *rt[N];

long long Query(seg_node *(&u), int x, int l, int r) {
	if (u == NULL) {
		u = cp++;
		u->get_size(l, r);
		if (l == r) {
			if (cur <= n) u->value = 1ll * (cur - 1) * m + l;
			else u->value = 1ll * l * m;
		}
	}
	--u->size;
	if (l == r)
		return u->value;
	int mid = (l + r) >> 1;
	if ((u->ls == NULL && x <= (mid - l + 1)) || (x <= (u->ls == NULL ? 0 : u->ls->size)))
		return Query(u->ls, x, l, mid);
	x -= u->ls == NULL ? (mid - l + 1) : u->ls->size;
	return Query(u->rs, x, mid + 1, r);
}

void Modify(seg_node *(&u), const int &x, const long long &v, int l, int r) {
	if (u == NULL) {
		u = cp++;
		u->get_size(l, r);
		if (l == r) u->value = v;
	}
	++u->size;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (x <= mid) Modify(u->ls, x, v, l, mid);
	else Modify(u->rs, x, v, mid + 1, r);
}

int main() {
	freopen("phalanx.in", "r", stdin);
	freopen("phalanx.out", "w", stdout);
	getusint(n);
	getusint(m);
	getusint(q);
	int ml = (n < m ? m : n) + q;
	while (q--) {
		int x, y;
		long long z;
		getusint(x);
		getusint(y);
		if (y == m) {
			cur = n + 1;
			z = Query(rt[cur], x, 1, ml);
		} else {
			cur = x;
			z = Query(rt[cur], y, 1, ml);
		}
		printf("%lld\n", z);
		cur = n + 1;
		Modify(rt[n + 1], n + (++count[n + 1]), z, 1, ml);
		if (y != m) {
			cur = n + 1;
			z = Query(rt[cur], x, 1, ml);
			cur = x;
			Modify(rt[x], m - 1 + (++count[x]), z, 1, ml);
		}
	}
	return 0;
}
