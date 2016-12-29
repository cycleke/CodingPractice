#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <cstring>
using namespace std;

struct Sta;
const int INF = 0x7f7f7f7f;
const int fc[] = {1,1,2,6,24,120,720,5040,40320,362820,3628800};
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};
const char goal[9] = {1,2,3,4,5,6,7,8,0};
int dis[370000];

struct Sta {
	char mp[9]; int d;
	Sta() {}
	Sta(const char A[9], int _d) {
		memcpy(mp,A,sizeof mp);
		d = _d;
	}
	int Hash() const {
		int ha = 0, sum;
		for (int i = 0; i < 9; ++i) {
			sum = 0;
			for (int j = i + 1; j < 9; ++j)
			  if (mp[i] > mp[j]) ++sum;
			ha += sum * fc[8 - i];
		}
		return ha;
	}
};

#define inside(a) ((a) < 3 && (a) >= 0)

queue<Sta>q;
const char start[9]={1,2,3,4,5,6,7,8,0};

void Pre() {
	Sta p = Sta(start,0), _p;
	int ha = p.Hash(), d, x, y, _x, _y, i, p1, p2;
	memset(dis, 127, sizeof dis);
	dis[ha] = 0; q.push(p);
	while (!q.empty()) {
		p = q.front(); q.pop();
		d = p.d;
		for (i = 0; i < 9; ++i)
		  if (!p.mp[i]) {
			  p1 = i; x = i / 3, y = i % 3;
			  break;
		  }
		for (i = 0; i < 4; ++i) {
			_x = x + dx[i], _y = y + dy[i];
			if (inside(_x)&&inside(_y)) {
				p2 = _x * 3 + _y;
				swap(p.mp[p1],p.mp[p2]);
				_p = Sta(p.mp,d+1);
				swap(p.mp[p1],p.mp[p2]);
				if (dis[ha=_p.Hash()]>=INF) {
					dis[ha] = d + 1; q.push(_p);
				}
			}
		}
	}
}

int main() {
	int T, ha; scanf("%d", &T);
	char num[3], cur[9];
	Pre();
	while (T--) {
		for (int i = 0; i < 9; ++i) {
			scanf("%s", num);
			if (*num ^ 'x') cur[i] = *num - '0';
			else cur[i] = 0;
		}
		ha = Sta(cur,0).Hash();
		if (dis[ha] ^ INF) printf("%d\n", dis[ha]);
		else puts("-1");
	}

	return 0;
}
