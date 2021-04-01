#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 20005
#define SIZE 150

int ina; char inc, inb[1<<16], *ins = inb, *ine = inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while ((inc = getc()) < '0' || inc > '9'); ina = inc - '0';
	while ((inc = getc()) >= '0' && inc <= '9') ina = (ina << 3) + (ina << 1) + inc - '0';
	return ina;
}

int pre[N], C[140][N], h[N], r[N];
void Add(int *tre, int x, int val) {
	for (; x < N; x += x & -x)
	  tre[x] += val;
}

int Sum(int *tre, int x) {
	int ret = 0;
	for (; x > 0; x -= x & -x)
	  ret += tre[x];
	return ret;
}

bool cmp(const int &a, const int &b) { return h[a] < h[b]; }

int main() {
	int n, i, j, ans = 0, m, id, la, x, y, idx, idy;
	for (n = geti(), i = 1; i <= n; ++i) h[i] = geti(), r[i] = i;
	std::sort(r + 1, r + n + 1, cmp);
	la = h[r[1]]; h[r[1]] = id = 1;
	for (i = 2; i <= n; ++i) {
		if (h[r[i]] ^ la) la = h[r[i]], ++id;
		h[r[i]] = id;
	}
	for (i = n; i; --i) 
		ans += Sum(pre, h[i] - 1), Add(pre, h[i], 1);
	for (i = 1; i <= n; ++i) Add(C[(i-1)/SIZE], h[i], 1);
	printf("%d\n", ans);
	for (m = geti(); m; --m) {
		x = geti(), y = geti();
		if (x > y) x ^= y ^= x ^= y;
		idx = (x-1) / SIZE + 1, idy = (y-1) / SIZE - 1;
		if (idx <= idy) {
			for (i = idx; i <= idy; ++i) {
				ans -= Sum(C[i], h[x]-1);
				ans += Sum(C[i], n) - Sum(C[i], h[x]);
				ans += Sum(C[i], h[y]-1);
				ans -= Sum(C[i], n) - Sum(C[i], h[y]);
			}
			for (i = x + 1, j = idx * SIZE; i <= j; ++i) {
				ans -= h[i] < h[x];
				ans += h[i] > h[x];
				ans += h[i] < h[y];
				ans -= h[i] > h[y];
			}
			for (i = (idy+1)*SIZE+1; i < y; ++i) {
				ans -= h[i] < h[x];
				ans += h[i] > h[x];
				ans += h[i] < h[y];
				ans -= h[i] > h[y];
			}
		} else {
			for (i = x + 1; i < y; ++i) {
				ans -= h[i] < h[x];
				ans += h[i] > h[x];
				ans += h[i] < h[y];
				ans -= h[i] > h[y];
			}
		}
		if (h[x] < h[y]) ++ans;
		else if (h[x] > h[y]) --ans;
		printf("%d\n", ans);
		Add(C[(x-1)/SIZE], h[x], -1); Add(C[(y-1)/SIZE], h[y], -1);
		h[x] ^= h[y] ^= h[x] ^= h[y];
		Add(C[(x-1)/SIZE], h[x], 1); Add(C[(y-1)/SIZE], h[y], 1);
	}
	return 0;
}
