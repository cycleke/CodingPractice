#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
using namespace std;

int ans[12], tmp[12], dep;
typedef long long LL;
inline LL gcd(LL a, LL b) {
	while (b) {
		a %= b; a ^= b ^= a ^= b;
	}
	return a;
}

bool dfs(const LL& a, const LL& b, const int& d) {
	if (d > dep) return false;
	if (!(b % a) && b / a > tmp[d-1]) {
		tmp[d] = b / a;
		if (!ans[1] || tmp[d] < ans[d]) 
			memcpy(ans, tmp ,sizeof tmp);
		return true;
	}
	int s = b / a; 
	if (s <= tmp[d-1]) s = tmp[d-1]+1;
	int e = (LL)(dep - d + 1) * b / a; 
	if (e > 30000) e = 30000;
	if (ans[1] && e >= ans[dep]) e = ans[dep] - 1;
	bool ok = false; LL g;
	for (int i = s; i <= e; ++i) {
		tmp[d] = i;
		g = gcd(a * i - b,b * i);
		ok |= dfs((a * i - b) / g , (b * i) / g,d + 1);
	}
	return ok;
}

int main() {
	int a, b;
	scanf("%d%d", &a, &b);
	dep = 1; tmp[0] = 1;
	while (!dfs(a,b,1)) 
		++dep;
	for (int i = 1; i <= dep; ++i) 
	printf("%d ", ans[i]);
	return 0;
}
