#include <cstdio>
typedef unsigned long long u64;
const u64 mod = 1000000007;
struct D {
	u64 x, y;
	D(u64 x = 0ULL, u64 y = 0ULL) :
		x(x), y(y) {}
}x, y, z;
D operator * (const D &a, const D &b) {
	return D(a.x * b.x % mod, (a.x * b.y + a.y) % mod);
}
inline D pow(D a, u64 b) {
	static D r;
	for (r = a; b; b >>= 1, a = a * a)
	  if (b & 1) r = r * a;
	return r;
}
char n[1001000], m[1001000];
inline u64 StringToNum(const char *s, const u64 &mod) {
	static u64 r;
	static const char *i;
	for (i = s, r = 0; *i; ++i)
	  r = (r * 10 + *i - '0') % mod;
	return r;
}
int main() {
	u64 a, b, c, d, t, p;
	scanf("%s%s%llu%llu%llu%llu", n, m, &a, &b, &c, &d);
	p = mod - 1 + (a == 1);
	t = StringToNum(m, p);
	if (t < 2) t += p;
	x = pow(D(a, b), t - 2);
	y = D(c, d);
	z = y * x;
	p = mod - 1 + (z.x == 1);
	t = StringToNum(n, p);
	if (t < 2) t += p;
	z = pow(z, t - 2);
	x = x * z;
	printf("%llu\n", (x.x + x.y) % mod);
	return 0;
}
