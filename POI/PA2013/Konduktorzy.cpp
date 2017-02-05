#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
#define K 1000005
#define pr pair<long long, int>
priority_queue< pr , vector< pr > , greater< pr > >heap;
int a[K];
long long ans[K];

inline long long Fun(const long long &a, const int &b) {
	static long long ret;
	ret = a / b;
	if (b * ret < a) ++ ret;
	return ret;
}

int main() {

	//freopen("t.in", "r", stdin);
	
	long long n, L, R = 0, Mid, t, Ans;
	int k, i;
	pr p;
	scanf("%lld%d", &n, &k);
	for (i = 0; i < k; ++i) {
		scanf("%d", a + i);
		if (a[i] > R) R = a[i];
	}
	L = R + 1, R *= n;
	Ans = L;
	while (L <= R) {
		Mid = (L + R >> 1);
		t = n;
		for (i = 0; i < k; ++i)
			if ((t -= Fun(Mid , a[i])) < 0) break;
		if (t < 0)
			R = Mid - 1;
		else
			L = (Ans = Mid) + 1;
	}
	
	R = Ans;
	for (i = 0; i < k; ++i)
		R = min(R, max((Ans / a[i] - 1) * a[i], 0LL));
	L = 0;
	for (i = 0; i < k; ++i) {
		t = R / a[i];
		L += t;
		heap.push(make_pair(t * a[i], i));
	}
	while (L < n) {
		p = heap.top();
		heap.pop();
		ans[p.second] = ++L;
		p.first += a[p.second];
		heap.push(p);
	}
	for (i = 0; i < k; ++i)
		printf("%lld ", ans[i]);
	return 0;
}
