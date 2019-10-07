#include "bits/stdc++.h"
#define N 1000000
using namespace std;
typedef long long ll;
inline ll gcd(ll x, ll y) { return y == 0 ? x : gcd(y, x % y); }
ll MOD(ll x, ll mod) { return x < mod ? x : x % mod + mod; }
ll fpow(ll a, ll n, ll mod) {
	ll tmp = a, ans = 1;
	while (n) {
		if (n & 1) ans = MOD(ans * tmp, mod);
		tmp = MOD(tmp * tmp, mod), n >>= 1;
	}
	return ans;
}
ll getPhi(ll x) {
	ll ans = 1;
	for (ll i = 2; i * 1ll * i <= x; i++) 
		if (x % i == 0) {
			ans *= i - 1, x /= i;
			while (x % i == 0) ans *= i, x /= i;
		}
	if (x != 1) ans *= x - 1;
	return ans;
}
ll solve(ll n, ll m) {
	if (m == 1) return 0;
	if (n == 1) return 1;
	ll phi = getPhi(m), tmp = solve(n - 1, phi);
	return fpow(n, tmp, m);
}
int main(int argc, char const *argv[]) {
	ll n, m;
	scanf("%lld%lld", &n, &m);
	printf("%lld\n", solve(n, m) % m);
	return 0;
}
