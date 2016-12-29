#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1e5 + 10;
struct edge {
	int to; edge *next;
}EE[Maxn << 1], *head[Maxn];
int totEE = -1;
void adde(const int &a, const int &b) {
	edge *ne = EE + (++totEE);
	ne->to = b; ne->next = head[a];
	head[a] = ne;
}
long long ans = 0;
map<int, int> MS[Maxn], *pre[Maxn];
typedef map<int, int> *mpt;
void Union(mpt &a,mpt &b) {
	if (a->size() > b->size()) swap(a, b);
	while (a->size()) {
		map<int,int>::iterator it = a->begin();
		(*b)[it->first] += it->second;
		a->erase(it);
	}
}

void dfs(int u, int val, int fa) {
	++(*pre[u])[val];
	for (edge *it = head[u]; it; it = it->next) {
		if (it->to == fa) continue;
		int v = it->to;
		dfs(v, val ^ v, u);
		for (map<int,int>::iterator itt = pre[v]->begin(); itt != pre[v]->end(); ++itt) {
			int t = (itt->first) ^ u;
			if (pre[u]->count(t)) ans += (long long)(itt->second) * ((*pre[u])[t]);
		}
		Union(pre[v], pre[u]);
	}
}

int main() {
	int n, u, v;
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		adde(u, v); adde(v, u);
	}
	for (int i = 1; i <= n; ++i) pre[i] = MS + i;
	dfs(1, 1, 0);
	cout << ans << endl;
	return 0;
}
