#include <map>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int ina; char inc, inb[1<<16], *ins = inb, *ine = inb; bool insign;
inline char getc() {
	if (ins == ine) ine = (ins = inb) + fread(inb, 1, 1 << 16, stdin);
	return (ins == ine) ? EOF : *ins++;
}
inline int geti() {
	insign = false;
	while ((inc = getc()) < '0' || inc > '9') insign |= inc == '-'; ina = inc - '0';
	while ((inc = getc()) >= '0' && inc <= '9') ina = (ina << 3) + (ina << 1) + inc - '0'; 
	return insign ? -ina : ina;
}

const int N = 105, inf = 0x7f7f7f7f;
bool vis[N<<1][N<<1], mp[N][N][4][4];
map<int, int>mpx, mpy;
int cnx, cny, n, hasx[N << 1], hasy[N << 1];
struct D {
	int x, y;
	void Read() {
		x = geti() << 1, y = geti() << 1;
	}
}st, en, re[60][2];

#define fun(a,b) (a^=b^=a^=b)

bool init() {
	st.Read(), en.Read();
	if (!(st.x|st.y|en.x|en.y)) return false;
	re[0][0] = st, re[0][1] = en; n = geti() + 1;
	for (int i = 1; i < n; ++i) {
		re[i][0].Read(), re[i][1].Read();
		if (re[i][0].x > re[i][1].x) fun(re[i][0].x, re[i][1].x);
		if (re[i][0].y > re[i][1].y) fun(re[i][0].y, re[i][1].y);
	}
	mpx.clear(), mpy.clear();
	memset(mp, 0, sizeof mp);
	cnx = cny = 0;
	for (int i = 0; i < n; ++i) {
		hasx[cnx++] = re[i][0].x;
		hasx[cnx++] = re[i][1].x;
		hasx[cnx++] = re[i][0].x+1;
		hasx[cnx++] = re[i][1].x+1;
		hasy[cny++] = re[i][0].y;
		hasy[cny++] = re[i][1].y;
		hasy[cny++] = re[i][0].y+1;
		hasy[cny++] = re[i][1].y+1;
	}
	sort(hasx, hasx + cnx); sort(hasy, hasy + cny);
	int tx, ty;
	mpx[hasx[0]] = tx = 0;
	mpy[hasy[0]] = ty = 0;
	for (int i = 1; i < cnx; ++i) 
	if (hasx[i] ^ hasx[tx]) {
		hasx[++tx] = hasx[i];
		mpx[hasx[tx]] = tx;
	}
	for (int i = 1; i < cny; ++i) 
	if (hasy[i] ^ hasy[ty]) {
		hasy[++ty] = hasy[i];
		mpy[hasy[ty]] = ty;
	}
	cnx = tx + 1, cny = ty + 1;
	memset(vis, true, sizeof vis);
	for (int i = 1; i < n; ++i) {
		int lx = mpx[re[i][0].x] + 1, ly = mpy[re[i][0].y] + 1;
		int rx = mpx[re[i][1].x], ry = mpy[re[i][1].y];
		for (int j = lx; j <= rx; ++j)
		  for (int k = ly; k <= ry; ++k)
			vis[j][k] = false;
	}
	cnx >>= 1, cny >>= 1;
	for (int i = 0; i < cnx; ++i)
	  for (int j = 0; j < cny; ++j) {
		  if((vis[i<<1][j<<1]&&vis[i<<1][j<<1|1])||(vis[i<<1|1][j<<1]&&vis[i<<1|1][j<<1|1]))
			mp[i][j][3][3] = mp[i][j][1][1] = 1;
		  if((vis[i<<1][j<<1]&&vis[i<<1|1][j<<1])||(vis[i<<1][j<<1|1]&&vis[i<<1|1][j<<1|1]))
			mp[i][j][2][2] = mp[i][j][0][0] = 1;
		  if(vis[i<<1][j<<1])
			mp[i][j][2][3] = mp[i][j][1][0] = 1;
		  if(vis[i<<1][j<<1|1])
			mp[i][j][2][1] = mp[i][j][3][0] = 1;
		  if(vis[i<<1|1][j<<1])
			mp[i][j][0][3] = mp[i][j][1][2] = 1;
		  if(vis[i<<1|1][j<<1|1])
			mp[i][j][0][1] = mp[i][j][3][2] = 1;
		  if(vis[i<<1][j<<1]&&vis[i<<1][j<<1|1]&&vis[i<<1|1][j<<1])
			mp[i][j][0][1] = mp[i][j][3][2] = 1;
		  if(vis[i<<1][j<<1]&&vis[i<<1][j<<1|1]&&vis[i<<1|1][j<<1|1])
			mp[i][j][1][2] = mp[i][j][0][3] = 1;
		  if(vis[i<<1][j<<1]&&vis[i<<1|1][j<<1]&&vis[i<<1|1][j<<1|1])
			mp[i][j][2][1] = mp[i][j][3][0] = 1;
		  if(vis[i<<1][j<<1|1]&&vis[i<<1|1][j<<1]&&vis[i<<1|1][j<<1|1])
			mp[i][j][1][0] = mp[i][j][2][3] = 1;
	  }
	for (int i = 0; i < cnx; ++i)
	  for (int j = 0; j < cny; ++j, puts(""))
		for (int x = 0; x < 4; ++x)
		  for (int y = 0; y < 4; ++y)
			printf("%d ", mp[i][j][x][y]);
	return true;
}

bool inside(int i, int j) {
	if (i < 0 || i >= cnx) return 0;
	if (j < 0 || j >= cny) return 0;
	return 1;
}
int dis[N][N][4];
bool inq[N][N][4];
queue<int>q;
const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

void Work() {
	memset(inq, 0, sizeof inq);
	memset(dis, 127, sizeof dis);
	while (!q.empty()) q.pop();
	int stx = mpx[st.x] >> 1, sty = mpy[st.y] >> 1, enx = mpx[en.x] >> 1, eny = mpy[en.y] >> 1;
	for (int i = 0; i < 4; ++i) {
		q.push((stx<<12)|(sty<<2)|i);
		dis[stx][sty][i] = 0;
	}
	while (!q.empty()) {
		int p = q.front(); q.pop();
		int ed, ex, ey;
		ed = p & 3; p >>= 2; ey = p & 1023; p >>= 10; ex = p;
		inq[ex][ey][ed] = false;
		for (int i = 0; i < 4; ++i) {
			int _x = ex + dx[i], _y = ey + dy[i];
			if (i==ed&&inside(_x,_y)&&mp[ex][ey][ed][i]&&dis[_x][_y][i]>dis[ex][ey][ed]) {
				dis[_x][_y][i] = dis[ex][ey][ed];
				if (!inq[_x][_y][i]) q.push((_x<<12)|(_y<<2)|i), inq[_x][_y][i] = true;
			} else if (i!=ed&&inside(_x,_y)&&mp[ex][ey][ed][i]&&dis[_x][_y][i]>dis[ex][ey][ed]+1) {
				dis[_x][_y][i]=dis[ex][ey][ed]+1;
				if (!inq[_x][_y][i]) q.push((_x<<12)|(_y<<2)|i), inq[_x][_y][i] = true;
			}
		}
	}
	int ans = inf;
	for (int i = 0; i < 4; ++i)
	  ans = min(ans, dis[enx][eny][i]);
	if (ans < inf) printf("%d\n", ans);
	else puts("-1");
}

int main() {
	freopen("T.in", "r", stdin);
	freopen("T.out","w",stdout);
	while (init()) Work();
	return 0;
}

