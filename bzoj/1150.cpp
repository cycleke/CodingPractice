#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int N = 200000;
typedef pair < int, int> pr;
int pre[N], nxt[N], totnode, n, k, weight[N];
bool mark[N];
priority_queue<pr>heap;
int main() {
	scanf("%d%d", &n, &k);
	int last, cur;
	scanf("%d", &last);
	for (int i = 1; i < n; ++i) {
		scanf("%d", &cur);
		weight[++totnode] = last - cur;
		heap.push(make_pair(last - cur, totnode));
		last = cur;
	}
	for (int i = 1; i <= totnode; ++i)
		pre[i] = i - 1, nxt[i] = i + 1;
	nxt[totnode] = 0;
	int idx;
	long long ans = 0;
	while (k) {
		pr p = heap.top(); 
		heap.pop();
		if (mark[p.second]) continue;
		--k;
		ans += -p.first;
		idx = p.second;
		mark[idx] = true;
		if (!pre[idx]) {
			mark[nxt[idx]] = true;
			pre[nxt[nxt[idx]]] = 0;
		} else if (!nxt[idx]) {
			mark[pre[idx]] = true;
			nxt[pre[pre[idx]]] = 0;
		} else {
			mark[pre[idx]] = mark[nxt[idx]] = true;
			++totnode;
			if (pre[pre[idx]]) nxt[pre[pre[idx]]] = totnode;
			if (nxt[nxt[idx]]) pre[nxt[nxt[idx]]] = totnode;
			nxt[totnode] = nxt[nxt[idx]];
			pre[totnode] = pre[pre[idx]];
			weight[totnode] = weight[pre[idx]] + weight[nxt[idx]] - weight[idx];
			heap.push(make_pair(weight[totnode], totnode));
		}
	}
	printf("%lld\n", ans);
	return 0;
}
