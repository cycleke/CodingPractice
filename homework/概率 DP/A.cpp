#include <cstdio>

double f[1010][1010];

int main() {
	int N, M, S;
	scanf("%d%d", &N, &M);
	S = N * M;
	f[N][M] = 0;
	for (int i = N; ~i; --i)
	for (int j = M; ~j; --j) 
	if (i^N || j ^ M) 
		f[i][j] = ((double)(N-i)*j/S*f[i+1][j]+(double)(M-j)*i/S*f[i][j+1]+(double)(N-i)*(M-j)/S*f[i+1][j+1]+1)/(1-(double)i*j/S);
	printf("%.4lf", f[0][0]);
	return 0;
}
