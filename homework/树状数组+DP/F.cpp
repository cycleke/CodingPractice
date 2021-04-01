#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
ld A[310][310];
int edge[310];
const ld eps = 1e-9;

int main() {
	int N, M, i, j, k, a, b, r; ld t;
	scanf("%d%d", &N, &M);
	for (i = 0; i < M; ++i) {
		scanf("%d%d", &a, &b);
		edge[a] = b;
	}
	A[N][N] = 6.;
	for (int i = N - 1; i; --i) {
		A[i][i] = 6.;
		if (edge[i]) {
			A[i][edge[i]] = -6.;
		} else {
			for (j = 1; j < 7; ++j)
				if (i + j <= N)
					A[i][i + j] = -1.;
				else 
					A[i][i] -= 1.;
			A[i][N + 1] = 6.;
		}
	}
	for (i = 1; i <= N; ++i) {
		r = i;
		for (j = i + 1; j <= N; ++j)
			if (fabs(A[j][i]) > fabs(A[r][i])) r = j;
		if (r ^ i) for (j = i; j <= N + 1; ++j) swap(A[r][j], A[i][j]);
		
		for (k = i + 1; k <= N; ++k) {
			if (fabs(A[i][i]) < eps) continue;
			t = A[k][i] / A[i][i];
			for (j = i; j <= N + 1; ++j) A[k][j] -= A[i][j] * t;
		}
	
	}
	
	for (i = N; i; --i) {
		for (j = i + 1; j <= N; ++j)
			A[i][N + 1] -= A[j][N + 1] * A[i][j];
		if (fabs(A[i][i]) <= eps && fabs(A[i][N + 1]) > eps) {
			puts("-1"); return 0;
		}
		A[i][N + 1] /= A[i][i];
	}
	printf("%.10lf\n", (double)A[1][N + 1]);
	return 0;
}
