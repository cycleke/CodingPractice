#include <cstdio>
#include <algorithm>
using namespace std;

struct Line {
	int x, y;
	Line(int a = 0, int b = 0) : x(a), y(b) {}
	bool operator < (const Line &a) const {
		if (x ^ a.x) return x < a.x;
		return y < a.y;
	}
}edge[1000010];

inline int geti(int &a) {
	a = 0; char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		a = (a << 3) + (a << 1) + c - '0';
		c = getchar();
	}
	return a;
}

int C[10010], Tim[10010];

void Add(int x, const int &T) {
	while (x < 10010) {
		if (Tim[x] ^ T) Tim[x] = T, C[x] = 0;
		++C[x]; x += x & -x;
	}
}

int Sum(int x, const int &T) {
	int s = 0;
	while (x) {
		if (Tim[x] ^ T) Tim[x] = T, C[x] = 0;
		s += C[x]; x -= x & -x;
	}
	return s;
}

int main() {
	int T, a, b, N, M, K; geti(T);
	long long ans;
	for (int Case = 1; Case <= T; ++Case) {
		printf("Test case %d: ", Case);
		geti(N); geti(M); geti(K);
		for (int i = 0; i < K; ++i) {
			geti(a); geti(b);
			edge[i] = Line(a, b);
		}
		sort(edge, edge + K);
		ans = 0;
		for (int i = 0; i < K; ++i) {
			ans += i - Sum(edge[i].y, Case);
			Add(edge[i].y, Case);

		}
		printf("%I64d\n", ans);
	}
}
