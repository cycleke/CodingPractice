#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 3;
int a[maxn], b[maxn];
long long s[maxn], t[maxn];
double p[maxn];
vector<int> g[maxn * 2];
map<long long, double> f[maxn];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	long long k;
	vector<pair<long long, int> > eve;
	cin >> m >> n >> k;
	for (int i = 0; i < m; i++) {
		cin >> a[i] >> b[i] >> s[i] >> t[i] >> p[i];
		if (a[i] == 1 || t[i] > k) {
			i--;
			m--;
			continue;
		}
		eve.emplace_back(s[i], a[i]);
		eve.emplace_back(t[i], b[i]);
	}
	eve.emplace_back(k + 1, 1);
	sort(eve.begin(), eve.end());
	eve.erase(unique(eve.begin(), eve.end()), eve.end());
	for (int i = 0; i < m; i++) {
		int x = lower_bound(eve.begin(), eve.end(), make_pair(s[i], a[i]))
			- eve.begin();
		g[x].push_back(i);
	}
	map<long long, double>::iterator it;
	for (int i = eve.size() - 1; i >= 0; i--) {
		int pos = eve[i].second;
		long long cur_time = eve[i].first;
		double _p = (pos == 1) ? 1 : 0;
		if (pos != 1) {
			it = f[pos].upper_bound(cur_time);
			if (it != f[pos].end()) _p = it->second;
		}
		double x = _p;
		for (int y : g[i]) {
			it = f[b[y]].upper_bound(t[y]);
			if (it == f[b[y]].end()) continue;
			x = max(x, p[y] * it->second + (1 - p[y]) * _p);
		}
		f[pos][cur_time] = x;
	}
	cout << f[0].begin()->second << endl;
	return 0;
}
