#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

double f[100010];
bool vis[100010];
struct edge {
	int to; edge *next;
}E[1010], *head[100010];
int totE;

void adde(const int &a, const int &b) {
	edge *ne = E + (++totE);
	ne->to = b; ne->next = head[a];
	head[a] = ne;
}

int main() {
	int N, M, a, b; double tmp;
	while (scanf("%d%d", &N, &M) == 2) {
		if (!N && !M) break;
		totE = -1; memset(f, 0, sizeof f);
		memset(head, 0, sizeof head); memset(vis, 0, sizeof vis);
		while (M--) {
			scanf("%d%d", &a, &b); adde(b, a);
		}
		vis[N] = 1;
		for (int i = N; ~i; --i) {
			if (!vis[i]) {
				vis[i] = 1;
				tmp = 0;
				for (int j = 1; j <= 6; ++j)
				tmp += f[i+j];
				tmp /= 6.;
				f[i] = tmp + 1;
			} 
			for (edge *it = head[i]; it; it = it->next) {
				vis[it->to] = 1;
				f[it->to] = f[i];
			}
		}
		printf("%.4lf\n", f[0]);
	}	
	return 0;
}
