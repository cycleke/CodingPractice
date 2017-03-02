#include <cstdio>
#include <cstring>

const int MaxN = 5e4 + 10;

int mu[MaxN];

inline void Init() {
	static int pri[5200], *end = pri;
	static bool vis[MaxN];
	mu[1] = 1;
	for (int i = 2, *j, t; i < MaxN; ++i) {
		if (!vis[i])
		  mu[*end++ = i] = -1;
		for (j = pri; (t = i * *j) < MaxN; ++j) {
			vis[t] = true;
			if (i % *j)
			  mu[t] = -mu[i];
			else {
				mu[t] = 0;
				break;
			}
		}
	}
	//printf("%d\n", end - pri);
}

inline int rank(const int &x) {
	int rk = 0;
	for (int i = 1;i * i <= x; ++i)
	  if (mu[i] < 0)
		rk -= x / i / i;
	  else if (0 < mu[i])
		rk += x / i / i;
	return rk;
}

int main() {
	int _, k, l, r, mid;
	scanf("%d", &_);
	Init();
	while (_--) {
		scanf("%d", &k);
		for (l = 1, r = k << 1; l <= r;) {
			mid = ((long long)l + r) >> 1;
			if (rank(mid) >= k) r = mid - 1;
			else l = mid + 1;
		}
		printf("%d\n", r + 1);
	}
	return 0;
}
