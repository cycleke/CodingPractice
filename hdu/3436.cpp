#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 200005

typedef int arr[N];

arr a, ha, now, pos, tr, opt;
int n, q, trn;

int sum(int x) {
	static int r;
	for (r = 0; x; x ^= x & -x)
	  r += tr[x];
	return r;
}

void add(int x, const int &delta) {
	for (; x <= trn; x += x & -x)
	  tr[x] += delta;
}

void init_bit(const int &n) {
	::trn = n;
	memset(tr, 0, (n + 2) * sizeof(int));
}

int kth(int k) {
	int pos = 0;
	for (int i = 17; ~i; --i) {
		pos ^= 1 << i;
		if (pos >= trn || tr[pos] >= k) pos ^= 1 << i;
		else k -= tr[pos];
	}
	return pos + 1;
}

int main() {
	int _, hcnt, top, idx;
	char ops[11];
	scanf("%d", &_);
	for (int __ = 1; __ <= _; ++__) {
		printf("Case %d:\n", __);
		scanf("%d%d", &n, &q);
		hcnt = 0;
		for (int i = 1; i <= q; ++i) {
			scanf("%s%d", ops, a + i);
			if (*ops == 'T') opt[i] = 1;
			else if (*ops == 'Q') opt[i] = 2;
			else opt[i] = 3;
			if (*ops ^ 'R') ha[++hcnt] = a[i];
		}
		ha[++hcnt] = n;
		std::sort(ha + 1, ha + hcnt + 1);
		n = std::unique(ha + 1, ha + hcnt + 1) - ha - 1;
		init_bit(q << 1);
		for (int i = 1; i <= n; ++i) {
			add(q + i, ha[i] - ha[i - 1]);
			now[q + i] = ha[i];
			pos[i] = q + i;
		}
		top = q;
		for (int i = 1; i <= q; ++i) {
			if (opt[i] ^ 3)
			  idx = std::lower_bound(ha + 1, ha + n + 1, a[i]) - ha;
			if (opt[i] < 2) {
				add(pos[idx], -1);
				--now[pos[idx]];
				pos[idx] = top;
				add(top, 1);
				now[top--] = a[i];
			} else if (~opt[i] & 1) {
				printf("%d\n", sum(pos[idx]));
			} else {
				int p = kth(a[i]);
				int rk = sum(p);
				printf("%d\n", now[p] - (rk - a[i]));
			}
		}
	}
	return 0;
}
