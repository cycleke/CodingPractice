#include <cstdio>
#include <algorithm>

const int MaxN = 100005;

struct edge {
	int to;
	edge *nxt;
}edge_mset[MaxN], *g[MaxN], *cedge = edge_mset;

inline void add_edge(int u, int v) {
	*cedge = (edge) {v, g[u]};
	g[u] = cedge++;
}

struct node {
	int val;
	node *ls, *rs;
	//void pop();
	//int top() const;
} node_mset[MaxN], *root[MaxN];

node *merge(node *x, node *y) {
	if (!x) return y;
	else if (!y) return x;
	if (x->val < y->val)
		std::swap(x, y);
	x->rs = merge(x->rs, y);
	//if (x->rs->dep > x->ls->dep)
	std::swap(x->ls, x->rs);
	//x->dep = x->rs->dep + 1;
	return x;
}

int L[MaxN], size[MaxN], m;
long long ans, sum[MaxN];

void dfs(int u) {
	size[u] = 1;
	sum[u] = root[u]->val;
	for (edge *it = g[u]; it; it = it->nxt) {
		dfs(it->to);
		sum[u] += sum[it->to];
		size[u] += size[it->to];
		root[u] = merge(root[u], root[it->to]);
	}
	while (sum[u] > m) {
		sum[u] -= root[u]->val;
		//root[u]->pop();
		root[u] = merge(root[u]->ls, root[u]->rs);
		--size[u];
	}
	ans = std::max(ans, (long long)size[u] * L[u]);
}

int main() {
	//freopen("t.in", "r", stdin);
	//nil = node_mset;
	//*nil = (node) {0, -1, nil, nil};
	int n, u, i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) {
		root[i] = node_mset + i;
		//node_mset[i] = *nil;
		scanf("%d%d%d", &u, &node_mset[i].val, L + i);
		add_edge(u, i);
		//node_mset[i].dep = 0;
	}
	dfs(1);
	printf("%lld\n", ans);
	return 0;
}
