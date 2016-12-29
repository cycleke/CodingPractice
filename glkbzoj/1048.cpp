#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
int A[12][12], sum[12][12];
double dp[12][12][12][12][12], ave;
const double INF = 1 << 30;
double Work(const int& a,const int& b,const int& c,const int& d,const int& cur) {
	double &tmp = dp[a][b][c][d][cur];
	if (tmp > -1) return tmp;
	if (cur == 1) {
		tmp = sum[c][d] - sum[a-1][d] - sum[c][b-1] + sum[a-1][b-1];
		tmp = (tmp - ave) * (tmp - ave);
		return tmp;
	}
	if ((c - a + 1) * (d - b + 1) < cur) return tmp = INF;
	tmp = INF;
	for (int i = a; i < c; ++i)
		for (int j = 1; j < cur; ++j)
			tmp = min(tmp,Work(a,b,i,d,j) + Work(i+1,b,c,d,cur - j));
	for (int i = b; i < d; ++i)
		for (int j = 1; j < cur; ++j)
			tmp = min(tmp,Work(a,b,c,i,j) + Work(a,i+1,c,d,cur - j));
	return tmp;
}

int main() {
	int N, a, b;
	scanf("%d%d%d", &a, &b, &N);
	for (int i = 1, j; i <= a; ++i)
		for (j = 1; j <= b; ++j) {
			scanf("%d" ,&A[i][j]);
			sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + A[i][j];
		}
	memset(dp, -1, sizeof(dp));
	ave = (double)sum[a][b] / N;
	printf("%.2lf", sqrt(Work(1,1,a,b,N) / N));
	return 0;
}
