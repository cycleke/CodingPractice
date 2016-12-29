#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <cstring>
using namespace std;

struct Sta;
typedef priority_queue<Sta, vector<Sta>, greater<Sta> > que, *pque;
const int INF = 1 << 30;
const int fc[] = {1,1,2,6,24,120,720,5040,40320,362820,3628800};
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};
const char Rigthpos[9][2] = {
	{1,1}, {0,0}, {0,1},
	{0,2}, {1,2}, {2,2},
	{2,1}, {2,0}, {1,0}
};
const char goal[9] = {1,2,3,8,0,4,7,6,5};
bool vis[370000];

struct Sta {
#define inside(a) ((a) < 3 && (a) >= 0)
	int f, g, h; char mp[9];
	Sta() { f = g = h = INF; }
	Sta(const char A[9], int _g) {
		memcpy(mp,A,sizeof mp); 
		g = _g; getH();
		f = g + h;
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
	
	void getH() {
		int _x, _y, val; h = 0;
		for (int i = 0; i < 9; ++i) {
			_x = i / 3, _y = i % 3;
			val = mp[i];
			h += abs(_x - Rigthpos[val][0]) + abs(_y - Rigthpos[val][1]);
		}
	}
	
	void Expand(pque q)  {
		int x, y, _x, _y, p1, p2, has;
		for (int i = 0; i < 9; ++i) 
		if (!mp[i]) {
			p1 = i; x = i / 3; y = i % 3; break;
		}
		Sta nn; 
		for (int i = 0; i < 4; ++i) {
			_x = x + dx[i], _y = y + dy[i];
			if (inside(_x) && inside(_y)) {
				p2 = _x * 3 + _y;
				swap(mp[p1], mp[p2]);
				nn = Sta(mp,g + 1);
				swap(mp[p1], mp[p2]);
				
				if (!vis[has = nn.Hash()]) {
					vis[has] = 1; q->push(nn);
				}
				
			}
		}
	}
	bool operator > (const Sta& b) const {
		return f > b.f;
	}
};

char star[9];

int main() {
	for (int i = 0; i < 9; ++i) scanf("%1d", star + i);
	Sta St = Sta(star,0), tmp;
	int En = Sta(goal,0).Hash();
	vis[St.Hash()] = 1;
	que q;
	q.push(St);
	while (!q.empty()) {
		tmp = q.top(); q.pop();
		
		if (tmp.Hash() == En) {
			printf("%d\n", tmp.f);
			break;
		}
		
		tmp.Expand(&q);
	}
	return 0;
}
