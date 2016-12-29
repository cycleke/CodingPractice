#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct data {
	int x, y, step;
	data(int a = 0, int b = 0, int c = 0) : x(a), y(b), step(c){} 
};
char vis[310][310];
int d[310][310];
int dx[] = {-2,-1,-2,-1,1,2,1,2};
int dy[] = {-1,-2,1,2,-2,-1,2,1};
#define inside(a) (a>=0 && a < n)
void Work() {
	int n, x1, x2, y1, y2;
	scanf("%d%d%d%d%d", &n, &x1, &y1, &x2, &y2);
	if (!(x1 ^ x2) && !(y1 ^ y2)) {
		puts("0"); return;
	}
	memset(vis, 0, sizeof vis);
	memset(d, 0, sizeof d);
	vis[x1][y1] = 1; vis[x2][y2] = -1;
	queue<data> q;
	q.push(data(x1,y1,0)); q.push(data(x2,y2,0));
	data p; int x, y, _x, _y, s, v;
	while (!q.empty()) {
		p = q.front(); q.pop();
		x = p.x, y = p.y, s = p.step;
		v = vis[x][y];
		for (int i = 0; i < 8; ++i) {
			_x = x + dx[i], _y = y + dy[i];
			if (inside(_x) && inside(_y)) {
				if (!vis[_x][_y]) 
					q.push(data(_x,_y,d[_x][_y] = s + 1)), vis[_x][_y] = v;
				else if (v ^ vis[_x][_y]) {
					printf("%d\n", d[x][y] + d[_x][_y] + 1); return;
				}
			}
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		Work();
	}
	return 0;
}
