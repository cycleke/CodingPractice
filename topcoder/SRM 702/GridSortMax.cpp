#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; ++i)

class GridSortMax {
private:
	static const int MaxN = 53;
	int A[MaxN][MaxN];
	int P[MaxN * MaxN];
	bool X[MaxN], Y[MaxN];
public:
	string findMax(int n, int m, vector <int> grid) {
		if (n == 1 || m == 1)
			return string(n * m, '1');
		rep(i, n) rep(j, m) {
			A[i][j] = grid[i * m + j] - 1;
			P[A[i][j]] = (i << 6) | j;
		}
		memset(X, 0, sizeof X);
		memset(Y, 0, sizeof Y);

		rep(i, n) rep(j, m) {
			int rx = P[i * m + j] >> 6;
			int ry = P[i * m + j] & 63;
			if (rx != i && (X[i] || X[rx]))
				continue;
			if (ry != j && (Y[j] || Y[ry]))
				continue;
			if (rx != i) {
				rep (k, m) {
					swap(A[rx][k], A[i][k]);
					P[A[rx][k]] = (rx << 6) | k;
					P[A[i][k]] = (i << 6) | k;
				}
			}
			if (ry != j) {
				rep(k, n) {
					swap(A[k][ry], A[k][j]);
					P[A[k][ry]] = (k << 6) | ry;
					P[A[k][j]] = (k << 6) | j;
				}
			}
			X[i] = Y[j] = true;
		}
		string ret(n * m, '0');
		rep(i, n) rep(j, m) 
			if (A[i][j] == i * m + j) ret[i * m + j] = '1';
		return ret;
	}
};
