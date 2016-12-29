#include <bits/stdc++.h>
using namespace std;
#define inf 0x7f7f7f7f
char tmpS[10];
int a[100005];

typedef long long ll;
const ll prime[] = {38833LL, 998244353LL, 1000000007LL, 1000000009LL};

int main() {
	int n, k, cnt = 0;
	scanf("%d%d", &n, &k);
	for (int i = 0; i <= n; ++i) {
		scanf("%s", tmpS);
		if (*tmpS ^ '?') sscanf(tmpS, "%d", a + i), ++cnt;
		else a[i] = inf;
	}
	if (!k) {
		if (a[0] == inf) puts((cnt&1)?"Yes":"No");
		else if (a[0]) puts("No");
		else puts("Yes");
	} else {
		if (cnt <= n) puts((n&1)?"Yes":"No");
		else {
			bool flag = true;
			for (int t = 0; t < 4 && flag; ++t) {
				ll v = a[n];
				for (int i = n - 1; ~i; --i)
				  v = (v * k + a[i]) % prime[t];
				if (v) flag = false;
			}
			puts(flag?"Yes":"No");
		}
	}
	return 0;
}
