#include <cstdio>

int l, k, x[100001];

int check(long long n) {
	long long curtenlength = 0;
	int accnt = 0, i;
	for (i = 0; i < l; ++i) {
		curtenlength += x[i];
		if (curtenlength >= n)
		  ++accnt, curtenlength = 0LL;
		if (curtenlength < 0)
		  curtenlength = 0LL;
	}
	return accnt;
}

int main() {
	scanf("%d%d", &l, &k);
	for (int i = 0; i < l; ++i) 
	  scanf("%d", x + i);
	long long l = 1, r = 1LL << 60, mid;
	while (l <= r)
	  if (check(mid = (l + r) >> 1) <= k)
		r = mid - 1;
	  else 
		l = mid + 1;
	if (check(r + 1) ^ k)
	  return puts("-1"), 0;
	printf("%lld ", r + 1);
	l = 1, r = 1LL << 60;
	while (l <= r)
	  if (check(mid = (l + r) >> 1) >= k)
		l = mid + 1;
	  else
		r = mid - 1;
	printf("%lld\n", l - 1);
	return 0;
}
