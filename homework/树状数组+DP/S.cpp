#include <cstdio>
#include <iostream>
using namespace std;

const int Maxn = 500010;
int q[Maxn];
long long dp[Maxn];
long long Sum[Maxn];

inline long long p2(long long a) {
	return a * a;
}

inline long long X(const int &a, const int &b) {
	return (Sum[b] - Sum[a]) << 1;
}

inline long long Y(const int &a, const int &b) {
	return dp[b] + p2(Sum[b]) - (dp[a] + p2(Sum[a]));
}

int main() {
	int N, M, i, a, top, tail;
	while (scanf("%d%d", &N, &M) ^ EOF) {
		for (i = 1; i <= N; ++i) {
			scanf("%d", &a); Sum[i] = Sum[i - 1] + a;
		}
		dp[0] = q[0] = 0; top = 0; tail = 0;
		for (int i = 1; i <= N; ++i) {
			while (top < tail && Y(q[top], q[top + 1]) <= Sum[i] * X(q[top], q[top + 1])) ++top;
			dp[i] = dp[q[top]] + p2(Sum[i] - Sum[q[top]]) + M;
			while (top < tail && Y(q[tail], i) * X(q[tail - 1], q[tail]) <= Y(q[tail - 1], q[tail]) * X(q[tail], i)) --tail;
			q[++tail] = i;
		}
		printf("%lld\n", dp[N]);
	}
}


