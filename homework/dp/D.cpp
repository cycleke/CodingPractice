#include <cstdio>
#include <iostream>
#include <cstring>
#include <map>
#include <stack>
#include <algorithm>
using namespace std;
const int Maxn = 100005, MaxS = 1000005;
const int dx[] = {0,0,-1,-1,-1,1,1,1};
const int dy[] = {1,-1,-1,0,1,-1,0,1};
struct edge {
	int to; edge *next;
}E[Maxn * 100];
int X[Maxn], Y[Maxn], T[Maxn], totedge = -1;
int dfs_time, per[Maxn], Belong[Maxn], Wealth[Maxn], Bcnt;
int in[Maxn], f[Maxn];
bool ins[Maxn];
edge *head[Maxn], *lx[MaxS], *ly[MaxS], *Edge[Maxn];
inline int readint(int& a) {
	a = 0; char c = getchar(); int flag = 1;
	while(c <'0' || c > '9') {
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		a = (a << 3) + (a << 1) + c - '0';
		c = getchar();
	}
	return a;
}
typedef pair<int,int> pii;
#define MK make_pair
map<pii,int>S;

void adde(const int& a,const int& b) {
	edge *ne = E + (++totedge);
	ne->to = b; ne->next = head[a];
	head[a] = ne;
}

void addE(const int& a,const int& b) {
	edge *ne = E + (++totedge);
	ne->to = b; ne->next = Edge[a];
	Edge[a] = ne;
}

void Link(const int& a) {
	edge *ne = E + (++totedge);
	ne->to = a; ne->next = lx[X[a]];
	lx[X[a]] = ne;
	ne = E + (++totedge);
	ne->to = a; ne->next = ly[Y[a]];
	ly[Y[a]] = ne;
}
stack<int>s;
int tarjan(const int& u) {
	int lowu = per[u] = ++dfs_time;
	s.push(u); ins[u] = true;
	for (edge *i = head[u]; i; i = i->next) {
		if (!per[i->to]) lowu = min(lowu,tarjan(i->to));
		else if(ins[i->to]) lowu = min(lowu,per[i->to]);
	}
	if (lowu == per[u]) {
		int v; ++Bcnt;
		while(1) {
			v = s.top(); s.pop();
			ins[v] = false; Belong[v] = Bcnt;
			++Wealth[Bcnt];
			if (v == u) break;
		}
	}
	return lowu;
}

int topsort() {
	stack<int>ss;
	while (!ss.empty()) ss.pop();
	int ans = -1, u;
	for (int i = 1; i <= Bcnt; ++i) if (!in[i]){
		ss.push(i); f[i] = Wealth[i];
	} 
	while (!ss.empty()) {
		u = ss.top(); ss.pop();
		if (f[u] > ans) ans = f[u];
		for (edge *it = Edge[u]; it; it = it->next) {
			if (!(--in[it->to])) ss.push(it->to);
			f[it->to] = max(f[it->to],f[u] + Wealth[it->to]);
		}
	}
	return ans;
}

int main() {
	int N, R, C;
	readint(N), readint(R), readint(C);
	for (int i = 1; i <= N; ++i) {
		readint(X[i]); readint(Y[i]); readint(T[i]);
		Link(i); S[MK(X[i],Y[i])] = i;
	}
	for (int i = 1; i <= N; ++i) {
		if (T[i] == 1) {
			for (edge *it = lx[X[i]]; it; it = it->next) {
				if (it->to == i) continue;
				adde(i,it->to);
			}
		}else if(T[i] == 2) {
			for (edge *it = ly[Y[i]]; it; it = it->next) {
				if (it->to == i) continue;
				adde(i,it->to);
			}
		}else {
			int _x, _y; map<pii,int>::iterator it;
			for (int j = 0; j < 8; ++j) {
				_x = X[i] + dx[j], _y = Y[i] + dy[j];
				it = S.find(MK(_x,_y));
				if (it == S.end()) continue;
				adde(i,it->second);
			}
		}
	}
	for (int i = 1; i <= N; ++i) if(!per[i]) tarjan(i);
	for (int i = 1; i <= N; ++i) {
		for (edge *it = head[i]; it; it = it->next) {
			if (Belong[i] != Belong[it->to]) {
				addE(Belong[i],Belong[it->to]); ++in[Belong[it->to]]; 
			}
		}
	}
	cout << topsort() << endl;
	return 0;
}
