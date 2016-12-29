#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int>pii;
#define fir first
#define sec second
char mp[20][20];
pii p[11];
struct D {
	int x, y, sta, d;
	D() {}
	D(int _x,int _y,int _sta,int _d):x(_x),y(_y),sta(_sta),d(_d){}
};
int vis[70000][20][20];
int ex, ey, len, n, m, Tim;
const int dx[]={1,0,0,-1};
const int dy[]={0,1,-1,0};

bool check(int sta) {
	int k = len, x = 0, y = 0;
	while (k--) {
		x += dx[sta&3];
		y += dy[sta&3];
		if (x==0&&y==0) return false;
		sta >>= 2;
	}
	return true;
}

int pre() {
	int sta = 0, t = 0, k;
	for (int i = 1; i < len; ++i) {
		int x = p[i].fir, y = p[i].sec;
		int _x = p[i+1].fir, _y = p[i+1].sec;
		if (_x < x) k = 3;
		else if (_x > x) k = 0;
		else if (_y < y) k = 2;
		else if (_y > y) k = 1;
		k <<= t; t += 2;
		sta |= k;
	}
	return sta;
}

#define inside(a,b) (a>0&&a<=n&&b>0&&b<=m)

queue<D>q;

int bfs() {
	int t = pre(); ++Tim;
	while (!q.empty()) q.pop();
	vis[t][p[1].fir][p[1].sec] = Tim;
	q.push(D(p[1].fir,p[1].sec,t,0));
	t = (1<<(len-1)*2)-1;
	while (!q.empty()) {
		D p = q.front(); q.pop();
		if (p.x==ex&&p.y==ey) return p.d;
		for (int i = 0; i < 4; ++i) {
			int _x = p.x + dx[i], _y = p.y + dy[i];
			if (!inside(_x,_y)||mp[_x][_y]=='#') continue;
			int _sta = p.sta << 2;
			_sta |= (3-i); _sta &= t;
			if (vis[_sta][_x][_y]==Tim|| !check(_sta)) continue;
			vis[_sta][_x][_y] = Tim;
			q.push(D(_x,_y,_sta,p.d+1));
		}

	}
	return -1;
}

int main() {
	int Case = 0;
	while (scanf("%d%d",&n,&m)^EOF) {
		len = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", mp[i]+1);
			for (int j = 1; j <= m; ++j)
			  if (mp[i][j]=='@') ex = i, ey = j;
			  else if (mp[i][j] > '0' && mp[i][j] <= '9') {
				  int t = mp[i][j] - '0';
				  p[t] = make_pair(i,j);
				  if (len < t) len = t;
			  }
		}
		printf("Case #%d: %d\n", ++Case, bfs());
	}
	return 0;
}
