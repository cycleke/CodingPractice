#include <map>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
struct D {
	int b[3],step;
};
using namespace std;
map< vector<int>,int >mp;
queue<D>q;
vector<int>v;
int a[3][30];

int main() {
	int n, mx,t; D st, p, _p;
	scanf("%d%d%d%d", &n,st.b,st.b+1,st.b+2);
	for (int i = 0; i < n; ++i)
	  for (int j = 0; j < 3; ++j)
		scanf("%d", a[j] + i);
	st.step = 0;
	mx = n >> 1; q.push(st);
	v.resize(3);
	while (!q.empty()) {
		p = q.front(); q.pop();
		if (p.step==mx) break;
		for (int j = 0; j < 3; ++j) {
			_p = p; ++_p.step;
			_p.b[j] += a[j][p.step];
			if (_p.step==mx) {
				v[0]=_p.b[0];
				v[1]=_p.b[1];
				v[2]=_p.b[2];
				mp[v] = 1;
			}
			else q.push(_p);
		}
	}
	while (!q.empty()) q.pop();
	memset(&st, 0, sizeof st);
	mx = n - mx; q.push(st);

	while (!q.empty()) {
		p = q.front(); q.pop();
		if (p.step>mx) break;
		for (int j = 0; j < 3; ++j) {
			_p = p; ++_p.step;
			_p.b[j] -= a[j][n-p.step-1];
			if (_p.step==mx) {
				v[0]=_p.b[0];
				v[1]=_p.b[1];
				v[2]=_p.b[2];
				if (mp.count(v))
				  return puts("YES"), 0;
			} else q.push(_p);
		}
	}
	puts("NO");
	return 0;
}
