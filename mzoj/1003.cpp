#include <cstdio>
#include <cstring>

const int N = 1e6 + 5;
int Link[N], vis[N], Tim;
int To[N << 1], nxt[N << 1], head[N], totE;

#define Adde(a,b) (To[totE] = b, nxt[totE] = head[a], head[a] = totE++)

bool find(int u) {
	for (int i = head[u]; ~i; i = nxt[i]) 
	if (vis[To[i]] ^ Tim){
		vis[To[i]] = Tim;
		if (!Link[To[i]] || find(Link[To[i]])) return Link[To[i]] = u;
	}
	return false;
}

int main() {
	int n, i, j;
	memset(head, -1, sizeof head);
	for (scanf("%d", &n), i = 1; i <= n; ++i) {
		scanf("%d", &j); Adde(j, i);
		scanf("%d", &j); Adde(j, i);
	}
	for (Tim = 1; Tim < N; ++Tim) if (!find(Tim)) break;
	printf("%d\n", Tim - 1);
	return 0;
}
