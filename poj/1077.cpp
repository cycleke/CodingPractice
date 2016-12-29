#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <cstdlib>
using namespace std;

struct Sta;

struct cmp{
	bool operator 
};

typedef priority_queue< Sta*, vector<Sta*>, cmp > que, *pque;
const int INF = ~0U>>1;
const int fc[] = {1,1,2,6,24,120,720,5040,40320,362820,3628800};
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};
const char Rigthpos[9][2] = {
	{1,1}, {0,0}, {0,1},
	{0,2}, {1,2}, {2,2},
	{2,1}, {2,0}, {1,0}
};
bool vis[3700000];
struct Sta {
#define inside(a) ((a) < 3 && (a) >= 0)
	int h, g, f, hash;
	char mp[9]; Sta *fa;
	Sta() {h = g = h = INF;}
	Sta(const char A[9], const int& _g) {
		memcpy(mp,A,sizeof mp); 
		g = _g; getH();
		f = g + h; getHash();
		fa = NULL;
	}
	void getHash()  {
		int sum; hash = 0;
		for (int i = 0; i < 9; ++i) {
			sum = 0;
			for (int j = i + 1; j < 9; ++j)
			if (mp[i] > mp[j]) ++sum;
			hash += sum * fc[8 - i];
		}
	}
	void getH() {
		int _x, _y, val; h = 0;
		for (int i = 0; i < 9; ++i) {
			_x = i / 3, _y = i % 3;
			val = mp[i];
			h += abs(_x - Rigthpos[val][0]) + abs(_y - Rigthpos[val][1]);
		}
	}
};
Sta D[500000];
int totD;
inline Sta *NewSta() { return D + (totD++); }

int main() {

}
