#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;

const int Maxn = 10010;
const double eps = 1e-9;

vector<int> edge[Maxn];
double A[Maxn], B[Maxn], C[Maxn], k[Maxn], e[Maxn];

bool dfs(const int &u, const int &fa) {
	int S = edge[u].size(), v;
	double tmp = 0;
	A[u] = k[u]; B[u] = C[u] = 1 - k[u] - e[u];
	B[u] /= S;
	for (int i = 0; i < S; ++i) {
		v = edge[u][i];
		if (v == fa) continue;
		if (!dfs(v, u)) return false;
		A[u] += B[u] * A[v];
		C[u] += B[u] * C[v];
		tmp += B[u] * B[v];
	}
	if (fabs(tmp - 1) < eps) return false;
	tmp = 1 - tmp;
	A[u] /= tmp;
	B[u] /= tmp;
	C[u] /= tmp;
	return true;
}

int main() {
	int T, N = 0, a, b;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		for (int i = 1; i <= N; ++i) edge[i].clear();
		
		scanf("%d", &N);
		for (int i = 1; i < N; ++i) {
			scanf("%d%d", &a, &b);
			edge[a].push_back(b);
			edge[b].push_back(a);
		}
		for (int i = 1; i <= N; ++i) {
			scanf("%d%d", &a, &b);
			k[i] = a / 100., e[i] = b / 100.;
		}
		
		printf("Case %d: ", t);		
		
		if (dfs(1, -1) && fabs(A[1] - 1.) > eps) {
			printf("%.6lf\n", C[1] / (1 - A[1]));
		} else puts("impossible");
	}
	
	return 0;
}
