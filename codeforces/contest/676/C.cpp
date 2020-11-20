#include <bits/stdc++.h>
using namespace std;
char s[100005];
int n, k;
int p[100005];

int cal(char ch) {
	for (int i = 1; i <= n; ++i) {
		p[i] = p[i-1];
		if (s[i]^ch) ++p[i];
	}
	int ret = 0;
	for (int i = 1; i <= n; ++i) {
		int l = 1, r = i, mid, ans = r;
		while (l <= r) {
			mid = l + r >> 1;
			if (p[i] - p[mid - 1] <= k) r = (ans = mid) - 1;
			else l = mid + 1;
		}
		if (p[i] - p[ans-1] <= k) ret = max(ret, i - ans + 1);
	}
	return ret;
}

int main() {
	scanf("%d%d\n%s", &n, &k, s + 1);
	printf("%d\n", max(cal('a'), cal('b')));
	return 0;
}
