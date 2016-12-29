#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long LL;
LL Ina; bool InSign; char Inc;
inline LL geti() {
	InSign = false; while ((Inc = getchar()) < '0' || Inc > '9') InSign |= Inc == '-'; Ina = Inc - '0';
	while ((Inc = getchar()) >= '0' && Inc <= '9') Ina = (Ina << 3) + (Ina << 1) + Inc - '0'; return InSign ? -Ina : Ina;
}
const int N = 1e6 + 5;
const double OO = 1e9;
struct P{
	LL x, y;
	P(LL a = 0, LL b = 0) : x(a), y(b) {}
	P operator - (const P &a) const { return P(x - a.x, y - a.y); }
	LL operator * (const P &a) const { return x * a.y - y * a.x; }
	bool operator < (const P &a) const { return (x < a.x) || (x == a.x && y < a.y); }
	void Read() { x = geti(), y = geti(); }
}p[N], Stack[N];
//k = -b/a
inline double get(const P &a) { return -sqrt((double)a.y / a.x); }
inline double getk(const P &a, const P &b) { return (a.x ^ b.x) ? ((double)(a.y - b.y) / (double)(a.x - b.x)) : OO; }
inline double Cal(const P &a, const double &k) { return k >= 0 ? OO : (double)a.x + a.y + - k * a.x - a.y / k; }
template <class T>
inline void SelfMin(T &a, const T &b) { if (b < a) a = b; }

int main() {
	int n = geti(), i, j, top = 0;
	for (i = 1; i <= n; ++i) p[i].Read();
	sort(p + 1, p + n + 1);
	Stack[++top] = p[1];
	for (i = 2; i <= n; ++i) {
		while (top >= 2 && (Stack[top] - Stack[top - 1]) * (p[i] - Stack[top - 1]) >= 0) --top;
		Stack[++top] = p[i];
	}
	if (top < 2) return printf("%.4lf\n", Cal(Stack[1], get(Stack[1]))), 0;
	double k, k1, k2, ans = OO;
	k2 = getk(Stack[1], Stack[2]); k = get(Stack[1]);
	if (k >= k2) SelfMin(ans, Cal(Stack[1], k));
	k1 = getk(Stack[top - 1], Stack[top]); k = get(Stack[top]);
	if (k <= k1) SelfMin(ans, Cal(Stack[top], k));
	SelfMin(ans, Cal(Stack[top], k1));
	for (i = 2; i < top; ++i) {
		k1 = getk(Stack[i - 1], Stack[i]), k2 = getk(Stack[i], Stack[i + 1]), k = get(Stack[i]);
		SelfMin(ans, Cal(Stack[i], k1));
		if ((k <= k1) && (k >= k2)) SelfMin(ans, Cal(Stack[i], k));
	}
	return printf("%.4lf\n", ans), 0;
}

