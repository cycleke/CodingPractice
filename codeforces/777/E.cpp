#include <bits/stdc++.h>
using namespace std;

struct ring {
	int a, b, h;
	bool operator < (const ring &x) const {
		return (b ^ x.b) ? b > x.b : a > x.a;
	}
}r[100005];

stack<int> s;
	
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	long long ans = 0LL, cur = 0LL;

	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> r[i].a >> r[i].b >> r[i].h;

	sort(r, r + n);

	for (int i = 0; i < n; ++i) {
		while (!s.empty() && r[s.top()].a >= r[i].b) {
			cur -= r[s.top()].h;
			s.pop();
		}
		s.push(i);
		cur += r[i].h;
		ans = max(ans, cur);
	}

	cout << ans << endl;
	
	return 0;
}











