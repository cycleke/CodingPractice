#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

typedef pair<int, int>pii;
const int N = 105;
inline int iabs(const int &a) { return a >= 0 ? a : -a; }
//edge
int to[N * N * 5], nxt[N * N * 5], w[N * N * 5], head[N], totE;
void Adde(int a, int b, int c) {
	to[totE] = b; w[totE] = iabs(a-b)*c; nxt[totE] = head[a];
	head[a] = totE++;
}

//dij
priority_queue<pii, vector<pii>, greater<pii> >pq;
int dis[N];
#define mk make_pair
void dij() {
	memset(dis, 127, sizeof dis); *dis = 0;
	pq.push(mk(0, 0));
	int p, d, i;
	while (!pq.empty()) {
		p = pq.top().second, d = pq.top().first; pq.pop();
		if (dis[p] ^ d) continue;
		for (i = head[p]; ~i; i = nxt[i])
		  if (dis[to[i]] > d + w[i] + 60) pq.push(mk(dis[to[i]] = d + w[i] + 60, to[i]));
	}
}

//
int Tim[6], node[N];

int main() {
	int n, t, i, j, k; char ch;
	while (scanf("%d%d", &n, &t) ^ EOF) {
		for (i = 0; i < n; ++i) scanf("%d", Tim + i);
		memset(head, -1, sizeof head);
		for (i = 0; i < n; ++i) {
			for (j = 1, ch = 0; ch ^ '\n'; ++j) {
				scanf("%d%c", node + j, &ch);
				for (k = 1; k < j; ++k)
				  Adde(node[j], node[k], Tim[i]), Adde(node[k], node[j], Tim[i]);
			}
		}
		dij();
		if (!t) puts("0");
		else if (dis[t] ^ 0x7f7f7f7f) printf("%d\n", dis[t] - 60);
		else puts("IMPOSSIBLE");
	}
	return 0;
}
