#include <bits/stdc++.h>
using namespace std;

vector< vector<int> > a;
int x[100005];

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> t(m, 0);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			cin >> t[j];
		a.push_back(t);
	}
	for (int i = 0; i < m; ++i) {
	    for (int j = 0, k; j < n; j = k + 1) {
			for (k = j; k < n; ++k)
				if (k + 1 < n && a[k][i] > a[k + 1][i]) break;
			for (int u = j; u <= k; ++u)
				x[u] = max(x[u], k);
		}
	}
	int q, l, r;
	cin >> q;
	while (q--) {
		cin >> l >> r;
		--l, --r;
		if (x[l] >= r)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}
