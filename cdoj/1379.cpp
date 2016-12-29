#include <bits/stdc++.h>
using namespace std;
#define N 55
struct D {
	int x, y, z,d;
	D() {}
	D(int _x,int _y,int _z,int _d):x(_x),y(_y),z(_z),d(_d){}
};
queue<D>q;
int sx, sy, sz, ex, ey, ez, n, l, r;
char vis[N][N][N],mp[N][N][N];

const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};

int bfs() {
	while (!q.empty()) q.pop();
	q.push(D(sx,sy,sz,0)); 
	vis[sx][sy][sz]=1;

	while (!q.empty()) {
		D p = q.front(); q.pop();
		int x = p.x, y = p.y, z = p.z, d = p.d;
		if (x==ex&&y==ey&&z==ez) return d;
		if (mp[z][x][y]=='U'&&!vis[x][y][z+1]&&mp[z+1][x][y]!='x')
		  q.push(D(x,y,z+1,d+1)),vis[x][y][z+1]=1;
		if (mp[z][x][y]=='D'&&!vis[x][y][z-1]&&mp[z-1][x][y]!='x')
		  q.push(D(x,y,z-1,d+1)),vis[x][y][z-1]=1;

		for (int i = 0; i < 4; ++i) {
			int _x = x + dx[i], _y = y + dy[i];
			if(vis[_x][_y][z]||mp[z][_x][_y]=='x') continue;
			vis[_x][_y][z]=1;
			q.push(D(_x,_y,z,d+1));
		}
	}
	
	return -1;
}

int main() {
	while (scanf("%d%d%d",&n,&l,&r)^EOF) {
		memset(vis, 0, sizeof vis);
		memset(mp, 'x', sizeof mp);
		for (int i = 1; i <= n; ++i) 
		  for (int j = 1; j <= l; ++j) {
			  scanf("%s", mp[i][j]+1);
			  mp[i][j][r+1]='x';
			  for (int k = 1; k <= r; ++k)
				if (mp[i][j][k]=='X') sx = j, sy = k, sz = i;
				else if (mp[i][j][k]=='Y') ex = j, ey = k, ez = i;
		  }
		printf("%d\n", bfs());
	}
	return 0;
}
