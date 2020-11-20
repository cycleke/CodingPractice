#include <bits/stdc++.h>
using namespace std;
int n, m, sx, sy, ex, ey;
bool w[1010][1010][4], vis[1010][1010][4];

struct D {
	int x, y, dir, dis;
	D(int _x=0, int _y=0,int _dir=0,int _dis=0) : x(_x),y(_y),dir(_dir),dis(_dis) {}
};

queue<D>q;
char mp[1010][1010];
#define W w[i][j]
void init() {
	memset(w, false, sizeof w);
	for (int i = 1; i <= n; ++i)
	  for (int j = 1; j <= m; ++j)
		if (mp[i][j]=='+') W[0]=W[1]=W[2]=W[3]=true;
		else if (mp[i][j]=='-') W[1]=W[3]=true;
		else if (mp[i][j]=='|') W[0]=W[2]=true;
		else if (mp[i][j]=='^') W[0]=true;
		else if (mp[i][j]=='>') W[1]=true;
		else if (mp[i][j]=='v') W[2]=true;
		else if (mp[i][j]=='<') W[3]=true;
		else if (mp[i][j]=='L') W[0]=W[1]=W[2]=true;
		else if (mp[i][j]=='R') W[0]=W[2]=W[3]=true;
		else if (mp[i][j]=='U') W[1]=W[2]=W[3]=true;
		else if (mp[i][j]=='D') W[0]=W[1]=W[3]=true;
}

const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};

int bfs() {
	memset(vis, 0, sizeof vis);
	if (mp[sx][sy] == '*' || mp[ex][ey] == '*') return -1;
	if (sx == ex && sy == ey) return 0;
	vis[sx][sy][0] = 1; q.push(D(sx,sy,0,0));
	D p; int x, y, dir, d;
	while (!q.empty()) {
		p = q.front(); q.pop();
		x = p.x, y = p.y, dir = p.dir, d = p.dis;

		if (x==ex&&y==ey) return d;
		
		if (!vis[x][y][(dir+1)%4]) {
			vis[x][y][(dir+1)%4]=true;
			q.push(D(x,y,(dir+1)%4,d+1));
		}

		for (int i = 0; i < 4; ++i) 
		if (w[x][y][(i-dir+4)%4]) {
			int _x = x + dx[i], _y = y + dy[i];
			if (mp[_x][_y]=='*') continue;
			if (w[_x][_y][(i-dir+6)%4] && !vis[_x][_y][dir]) {
				vis[_x][_y][dir] = true;
				q.push(D(_x,_y,dir,d+1));
			}
		}

	}
	return -1;
}

int main() {
	scanf("%d%d", &n, &m);
	memset(mp, '*', sizeof mp);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", mp[i] + 1);
		mp[i][m+1] = '*';
	}
	scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
	init();
	printf("%d\n", bfs());
	return 0;
}
