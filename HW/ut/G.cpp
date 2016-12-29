#include <bits/stdc++.h>
using namespace std;

const int Maxn = 100010;
struct data {
	int x, y1, y2, v;
	data(int a = 0, int b = 0, int c = 0, int d = 0) : x(a), y1(b), y2(c), v(d) {}
	bool operator < (const data &A) const {
		return x < A.x;
	}
};
vector <int> Y;
vector <data> op[2];
int N, K, C;

class Sgtree {
protected:
	int dl[Maxn << 3], dr[Maxn << 3], Cover[Maxn << 3], len[Maxn << 3][13];
public:
	void Up(const int &u) {
		int l = dl[u], r = dr[u];
		memset(len[u], 0, sizeof len[u]);
		if (r - l == 1) {
			len[u][min(K + 1, Cover[u])] = Y[r] - Y[l];
		} else {
			int val = Cover[u];
			for (int i = 0; i <= K + 1; ++i)
				len[u][min(val + i, K + 1)] = len[u << 1][i] + len[u << 1 | 1][i];
		}
	}
	
	void Build(int u, int l, int r) {
		dl[u] = l, dr[u] = r, Cover[u] = 0;
		memset(len[u], 0, sizeof len[u]);
		len[u][0] = Y[r] - Y[l];
		if (r - l > 1) {
			int mid = (l + r) >> 1;
			Build(u << 1, l, mid);
			Build(u << 1 | 1, mid, r);
		}
	}
	
	void Update(int u, int x, int y, const int &val) {
		if (x == y) return;
		int l = dl[u], r = dr[u];
		if (x <= l && y >= r) Cover[u] += val;
		else {
			int mid = (l + r) >> 1;
			if (x < mid) Update(u << 1, x, y, val);
			if (y > mid) Update(u << 1 | 1, x, y, val);
		}
		Up(u);
	}
	
	int Query() {
		return len[1][K];
	}
}St;

inline int Rank(const int &v) {
	return lower_bound(Y.begin(), Y.end(), v) - Y.begin();
}

long long Solve(const vector<data> &T) {
	long long ret = 0;
	if (T.size() == 0) return 0LL;
	St.Build(1, 0, C - 1);
	int last = T[0].x, len;
	for (int i = 0; i < T.size(); ++i) {
		len = T[i].x - last;
		ret += (long long)len * St.Query();
		St.Update(1, Rank(T[i].y1), Rank(T[i].y2), T[i].v);
		last = T[i].x;
	}
	return ret;
}

int main() {
	int x1, x2, y1, y2, z1, z2;
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
		if (z2 - z1 >= 1) {
			Y.push_back(y1); Y.push_back(y2);
			for (int j = z1; j < z2; ++j) {
				op[j - 1].push_back(data(x1, y1, y2, 1));
				op[j - 1].push_back(data(x2, y1, y2, -1));
			}
		}
	}
	sort(Y.begin(), Y.end());
	Y.erase(unique(Y.begin(), Y.end()), Y.end());
	C = Y.size();
	long long ans = 0;
	for (int i = 0; i < 2; ++i) {
		sort(op[i].begin(), op[i].end());
		ans += Solve(op[i]);
	}
	cout << ans << endl;
	return 0;
}


