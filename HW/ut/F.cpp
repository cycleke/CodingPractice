#include <queue>
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;

vector<int> val[100010];
priority_queue<int>pq;
int a[100010];

int main() {
	int n, m = 0, v;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", a + i), m = max(m, a[i]);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &v);
		val[a[i]].push_back(v);
	}
	int ans = 0;
	for (int i = m; i; --i) {
		for (int j = 0; j < val[i].size(); ++j) pq.push(val[i][j]);
		if (!pq.empty()) {
			ans += pq.top(); 
			pq.pop();
		}
	}
	printf("%d", ans);
	return 0;
}
