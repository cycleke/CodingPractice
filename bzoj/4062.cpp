#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 200003
typedef int arr[N];

arr tr, hx;
set<int> s[N];
struct node {
	int x, y, c;
	void Input() {
		scanf("%d%d%d", &x, &y, &c);
	}
	bool operator < (const node &a) const {
		return y < a.y;
	}
}a[N];

int trn;

void add(int x) {
	for (; x < trn; x += x & -x)
		++tr[x];
}

int sum(int x) {
	static int r;
	for (r = 0; x; x ^= x & -x)
		r += tr[x];
	return r;
}

int main() {
	//freopen("t.in", "r", stdin);
	int _, n, k, ans, hcnt, x, y, c, l, r;
	scanf("%d", &_);
	while (_--) {
		scanf("%d%d", &n, &k);
		for (int i = 0; i < n; ++i) {
			a[i].Input();
			hx[i] = a[i].x;
		}
		sort(hx, hx + n);
		hcnt = unique(hx, hx + n) - hx;
		trn = hcnt + 1;
		for (int i = 0; i < n; ++i)
			a[i].x = lower_bound(hx, hx + hcnt, a[i].x) - hx + 1;
		for (int i = 1; i <= k; ++i) {
			s[i].clear();
			s[i].insert(0);
			s[i].insert(hcnt + 1);
		}
		ans = 0;
		memset(tr, 0, sizeof tr);
		
		sort(a, a + n);
		a[n].y = 0x3fffffff;
		for (int i = 0; i < n; ++i) {
			x = a[i].x, y = a[i].y, c = a[i].c;
			if (s[c].find(x) == s[c].end()) {
				set<int>::iterator it = s[c].upper_bound(x);
				r = *it - 1, l = *--it;
				ans = max(ans, sum(r) - sum(l));
			}
			if (y ^ a[i + 1].y) {
				for (int j = i; (~j) && !(a[j].y ^ y); --j) {
					s[a[j].c].insert(a[j].x);
					add(a[j].x);
				}
			}
		}
		for (int i = 1; i <= k; ++i)
			for (set<int>::iterator i1 = s[i].begin(), i2; ; ++i1) {
				if (++(i2 = i1) == s[i].end())
					break;
				ans = max(ans, sum(*i2 - 1) - sum(*i1));
			}
		printf("%d\n", ans);
	}
	return 0;
}
