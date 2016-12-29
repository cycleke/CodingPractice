#include <cstdio>
#include <cstring>

const int N = 2e5 + 5, M = N * 50;
int totNode, root[N], ls[M], rs[M], siz[M];

int ina; bool insign; char inc;
inline int geti() {
	insign = 0; while ((inc = getchar()) < '0' || inc > '9') insign |= inc == '-'; ina = inc - '0';
	while ((inc = getchar()) >= '0' && inc <= '9') ina = (ina << 3) + (ina << 1) + inc - '0';
	return insign ? -ina : ina;
}

void Update(int l, int r, int last, int &cur, int val) {
	cur = ++totNode;
	ls[cur] = ls[last]; rs[cur] = rs[last]; siz[cur] = siz[last] + 1;
	if (l == r) return;
	int mid = l + r >> 1;
	if (val <= mid) Update(l, mid, ls[last], ls[cur], val);
	else Update(mid + 1, r, rs[last], rs[cur], val);
}

bool Query(int l, int r, int last, int cur, int x, int y) {
	if (!(siz[cur] - siz[last])) return false;
	if (x <= l && r <= y) return true;
	int mid = l + r >> 1;
	if (y <= mid) return Query(l, mid, ls[last], ls[cur], x, y);
	else if (x > mid) return Query(mid + 1, r, rs[last], rs[cur], x, y);
	else return Query(l, mid, ls[last], ls[cur], x, mid) || Query(mid + 1, r, rs[last], rs[cur], mid + 1, y);
}

int main() {
	int n, m, b, l, r, x, L, R, i, mid;
	n = geti(), m = geti();
	for (x = 1; x <= n; ++x) 
	  Update(0, N, root[x - 1], root[x], geti());
	while (m--) {
		b = geti(), x = geti(), l = geti(), r = geti();
		L = 0, R = (1 << 19) - 1;
		for (i = 18; ~i; --i) {
			mid = L + R >> 1;
			if (b & (1 << i)) Query(0, N, root[l - 1], root[r], L - x, mid - x) ? (R = mid) : (L = mid + 1);
			else Query(0, N, root[l - 1], root[r], mid - x + 1, R - x) ? (L = mid + 1) : (R = mid);
		}
		printf("%d\n", b ^ L);
	}
	return 0;
}
