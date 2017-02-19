#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 60005

int ha[N], K;

struct Line {
	int x, y1, y2, v;
	bool operator < (const Line &a) const {
		return x < a.x;
	}
}line[N];

struct node {
	int l, r, a[12], add;
	int MID() const {
		return (l + r) >> 1;
	}
	void init() {
		memset(a, 0, sizeof a);
	}
	bool notleaf() const {
		return (l + 1) ^ r;
	}
}C[N << 2];

#define ls u << 1
#define rs u << 1 | 1

void Build(int u, int l, int r) {
	C[u].l = l, C[u].r = r;
	C[u].init();
	C[u].a[0] = ha[r] - ha[l];
	C[u].add = 0;
	if ((l + 1)^ r) {
		int m = C[u].MID();
		Build(ls, l, m);
		Build(rs, m, r);
	}
}

void cal(int u) {
	if (C[u].add >= K) {
		int t = C[u].a[0];
		C[u].init();
		C[u].a[0] = C[u].a[K] = t;
	} else if (C[u].add) {
		int cov = C[u].add;
		for (int i = 1; i <= K; ++i)
		  C[u].a[i] = 0;
		C[u].a[cov] = C[u].a[0];
		if (C[u].notleaf()) {
			int sum = 0;
			for (int i = 1; i <= K; ++i) 
			  if (i + cov >= K) C[u].a[K] += C[ls].a[i] + C[rs].a[i];
			  else C[u].a[i + cov] += C[ls].a[i] + C[rs].a[i];
			for (int i = cov + 1; i <= K; ++i)
			  sum += C[u].a[i];
			C[u].a[cov] -= sum;
		}
	} else {
		for (int i = 1; i <= K; ++i) C[u].a[i] = 0;
		if (C[u].notleaf()) 
		  for (int i = 1; i <= K; ++i)
			C[u].a[i] += C[ls].a[i] + C[rs].a[i];
	}
}

void Update(int u, const int &x, const int &y, const int &v) {
	if (x <= C[u].l && C[u].r <= y)
	  C[u].add += v;
	else {
		int m = C[u].MID();
		if (x < m) Update(ls, x, y, v);
		if (y > m) Update(rs, x, y, v);
	}
	cal(u);
}

int main() {
	int _, n, *hcnt;
	Line *end;
	long long ans;
	scanf("%d", &_);
	for (int __ = 1; __ <= _; ++__) {
		scanf("%d%d", &n, &K);
		hcnt = ha, end = line;
		for (int i = 0, x1, y1, x2, y2; i < n; ++i) {
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			++x2, ++y2;
			*end++ = (Line){x1, y1, y2, 1};
			*end++ = (Line){x2, y1, y2, -1};
			*hcnt++ = y1;
			*hcnt++ = y2;
		}
		std::sort(line, end);
		std::sort(ha, hcnt);
		hcnt = std::unique(ha, hcnt);
		Build(1, 0, hcnt - ha - 1);
		ans = 0;
		for (Line *it = line; it < end; ++it) {
			if (line < it) ans += (long long)(it->x - (it - 1)->x) * C[1].a[K];
			int _y1 = std::lower_bound(ha, hcnt, it->y1) - ha;
			int _y2 = std::lower_bound(ha, hcnt, it->y2) - ha;
			Update(1, _y1, _y2, it->v);
		}
		printf("Case %d: %lld\n", __, ans);	
	}
	return 0;
}
