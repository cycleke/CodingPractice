#include <queue>
#include <cstdio>


inline void cmax(int &a, const int &b) {
	if (a < b) a = b;
}

struct data {
	long long cnt;
	int len;
	data(long long cnt, int len) :
		cnt(cnt), len(len) {}
};

bool operator < (const data &a, const data &b) {
	return (a.cnt ^ b.cnt) ? a.cnt > b.cnt : a.len > b.len;
}

int main() {
	static int n, k, cnt, len;
	static long long x, ans = 0, tmp;
	static std::priority_queue<data> heap;

	scanf("%d%d", &n, &k);

	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &x);
		heap.push(data(x, 1));
	}

	cnt = n;
	if ((n - 1) % (k - 1))
		cnt += k - 1 - (n - 1) % (k - 1);

	for (int i = n + 1; i <= cnt; ++i)
		heap.push(data(0, 1));

	while (cnt > 1) {
		tmp = len = 0;
		for (int _ = 0; _ < k; ++_) {
			tmp += heap.top().cnt;
			cmax(len, heap.top().len);
			heap.pop();
		}
		ans += tmp;
		heap.push(data(tmp, len + 1));
		cnt = cnt - k + 1;
	}

	printf("%lld\n%d\n", ans, heap.top().len - 1);
	return 0;
}
