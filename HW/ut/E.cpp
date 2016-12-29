#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;

const int Maxn = 100010;
int a[Maxn], b[Maxn];
struct data {
	int i, j, val;
	data() {}
	data(int p, int q) : i(p), j(q), val(a[p] + b[q]) {}
	bool operator < (const data &A) const {
		return val > A.val;
	}
};
priority_queue<data>pq;

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", a + i);
	for (int i = 0; i < n; ++i) scanf("%d", b + i);
	sort(a, a + n); sort(b, b + n);
	for (int i = 0; i < n; ++i)	pq.push(data(0, i));
	data p;
	for (int i = 0; i < n; ++i) {
		p = pq.top(); pq.pop();
		printf("%d\n", p.val);
		if (p.i + 1 < n) pq.push(data(p.i + 1, p.j));
	}
	return 0;
}
