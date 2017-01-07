#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const char *NO = "Orz, I cannot find x!";
void exgcd(ll a, ll b, ll &x, ll &y, ll &g) {
	if (!b) x = 1, y = 0, g = a;
	else {
		exgcd(b, a%b, y, x, g);
		y -= a / b * x;
	}
}
ll pw(ll a, ll b, ll p) {
	static ll r;
	for (r = 1; b; b >>= 1, a = a * a % p)
		if (b & 1) r = r * a % p;
	return r;
}
map < ll, ll > hash;
#define WW while(__--)
int main() {
	ll y, z, p, i, j, g, x, m, inv, e;
	int __, type;
	scanf("%d%d", &__, &type);
	if (type == 1) WW {
		scanf("%lld%lld%lld", &y, &z, &p);
		printf("%lld\n", pw(y, z, p));
	} else if (type == 2) WW {
		scanf("%lld%lld%lld", &y, &z, &p);
		exgcd(y, p, i, j, g);
		if (z % g) puts(NO);
		else {
			x = z / g * i, p /= g;
			printf("%lld\n", (x % p + p) % p);
		}
	} else WW {
		scanf("%lld%lld%lld", &y, &z, &p);
		y %= p, z %= p;
		if (!y && !z) puts("1");
		else if (!y) puts(NO);
		else {
			m = sqrt(p);
			inv = pw(y, p - m - 1, p);
			e = 1LL;
			hash.clear();
			hash[1] = m + 1;
			for (i = 1; i <= m; ++i) {
				e = e * y % p;
				hash[e] = i;
			}
			for (x = -1, i = 0; i < m && x < 0; ++i) {
				if (j = hash[z]) {
					if (m < j) 
						j = 0;
					x = i * m + j;
				}
				z = z * inv % p;
			}
			if (~x) 
				printf("%lld\n", x);
			else puts(NO);
		}
	}
	return 0;
}
