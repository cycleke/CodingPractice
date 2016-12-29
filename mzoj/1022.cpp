#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define N 100005
#define SN 1005
int t[N << 1], n, m, blo, top;
vector<int>d[SN];

pair<int, int> query(int k) {
	int x = 1;
	while (k>d[x].size())
	  k -= d[x].size(), ++x;
	return make_pair(x, k - 1);
}

void rebuild() {
	top = 0;
	for (int i = 1; i <= m; ++i) {
		for (vector<int>::iterator it = d[i].begin(); it != d[i].end(); ++it)
		  t[++top] = *it;
		d[i].clear();
	}
	int _blo = sqrt(top);
	for (int i = 1; i <= n; ++i)
	  d[(i-1)/_blo+1].push_back(t[i]);
	m = (top - 1) / _blo + 1;
}

void insert(int a, int b) {
	pair<int, int> p = query(a);
	d[p.first].insert(d[p.first].begin()+p.second,b);
	if (d[p.first].size() > 15 * blo)
	  rebuild();
}

int main() {
	scanf("%d", &n); blo = sqrt(n);
	for (int i = 1; i <= n; ++i) scanf("%d", t + i);
	for (int i = 1; i <= n; ++i)
	  d[(i-1)/blo+1].push_back(t[i]);
	m = (n - 1) / blo + 1;
	int f, a, b, c; pair<int, int>p;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d%d", &f, &a, &b, &c);
		if (f) p = query(b), printf("%d\n", d[p.first][p.second]);
		else insert(a,b);
	}
	return 0;
}
