#include <cstdio>
#include <cstring>
#include <cmath>

int ina; char inc, inb[1<<16], *ins = inb, *ine = inb; bool insign;
inline char getc() {
	if (ins == ine) ine = (ins = inb) + fread(inb, 1, 1 << 16, stdin);
	return (ins == ine) ? EOF : *ins++;
}
inline int geti() {
	insign = false;
	while ((inc = getc()) < '0' || inc > '9') insign |= inc == '-'; ina = inc - '0';
	while ((inc = getc()) >= '0' && inc <= '9') ina = (ina << 3) + (ina << 1) + inc - '0'; return insign ? -ina : ina;
}

const int N = 105;
double dis[N][N];
int X[N], Y[N], Z[N], R[N];
template<class T>
void SelfMin(T &a, T b) { if (b < a) a = b;}

double p2(double a) { return a * a;}

double dist(const int &i, const int &j) { return sqrt(p2(X[i]-X[j]) + p2(Y[i]-Y[j]) + p2(Z[i]-Z[j])); }

int main() {
	freopen("T.in", "r", stdin); freopen("T.out", "w", stdout);
	int n, i, j, k, Case = 0; double d;
	while (~(n = geti())) {
		for (i = 1; i <= n; ++i)
		  X[i] = geti(), Y[i] = geti(), Z[i] = geti(), R[i] = geti();
		for (i = 1; i <= 2; ++i)
		  X[i+n] = geti(), Y[i+n] = geti(), Z[i+n] = geti(), R[i+n] = 0;
		n += 2;
		for (i = 1; i <= n; ++i)
		  for (j = 1; j <= n; ++j) 
			if (i ^ j){
				d = dist(i, j);
				if (d <= R[i] + R[j]) dis[i][j] = 0.;
				else dis[i][j] = d - (R[i] + R[j]);
			} else dis[i][j] = 0.;		
		for (k = 1; k <= n; ++k)
		  for (i = 1; i <= n; ++i)
			for (j = 1; j <= n; ++j)
			  SelfMin(dis[i][j], dis[i][k] + dis[k][j]);
		printf("Cheese %d: Travel time = %.0lf sec\n", ++Case, dis[n-1][n] * 10);
	}
	return 0;
}
