#include <cstdio>

typedef long long ll;
const int Maxn = 100005;
ll dp[Maxn], f[Maxn], a[Maxn], c;
ll q[Maxn];
inline ll S(const int& a,const int& b) {
	return (f[a] - f[b]) << 1;
}

inline ll G(const int& a,const int& b) {
	return dp[a] - dp[b] + (f[a] - f[b]) * (f[a] + f[b] + (c << 1));
}

inline void work(const int& N) {
	int head, tail;
	head = tail = 1;
	q[1] = 0;
	for (int i = 1,j; i <= N; ++i) {
		while (head < tail && G(q[head + 1],q[head]) <= S(q[head + 1],q[head]) * f[i]) ++head;
		j = q[head];
		dp[i] = dp[j] + (f[i] - f[j] - c) * (f[i] - f[j] - c);
		while (head < tail && G(i,q[tail]) * S(q[tail],q[tail - 1]) <= G(q[tail],q[tail - 1]) * S(i,q[tail])) --tail;
		q[++tail] = i;
	}
	printf("%lld",dp[N]);
}

int main() {
	int N,L;
	scanf("%d%d", &N, &L);
	c = L + 1;
	for (int i = 1; i <= N; ++i) {
		scanf("%lld", a + i);
		f[i] = f[i - 1] + a[i];
	}
	for (int i = 1; i <= N; ++i) f[i] += i;
	work(N);
	return 0;
}
