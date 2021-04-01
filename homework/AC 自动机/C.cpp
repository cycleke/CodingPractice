#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MS = 50010, Maxl = 2000010, ML = 53, MaxN = 1010, Siz = 26;
int Cnt[MaxN], ch[MS][Siz], Fail[MS], v[MS], root, totN;
char virus[MaxN][ML];
char tmpS[Maxl];

int NewNode() {
	v[++totN] = 0;
	memset(ch[totN], 0, sizeof ch[totN]);
	return totN;
}

void Insert(char *S, const int &val) {
	int cur = root;
	char idx;
	while (*S) {
		idx = *S - 'A';
		if (ch[cur][idx]) {
			cur = ch[cur][idx];
		} else {
			cur = ch[cur][idx] = NewNode();
		}
		++S;
	}
	v[cur] = val;
}

void BuildFail() {
	queue<int>q;
	Fail[root] = root;
	for (int i = 0; i < Siz; ++i) if (ch[root][i]) {
		Fail[ch[root][i]] = root;
		q.push(ch[root][i]);
	}
	int f, p;
	while (!q.empty()) {
		p = q.front(); q.pop();
		
		for (int i = 0; i < Siz; ++i) if (ch[p][i]) {
			f = Fail[p];
			
			while (!ch[f][i] && f) f = Fail[f];
			
			if (ch[f][i]) Fail[ch[p][i]] = ch[f][i];
			else Fail[ch[p][i]] = root;
			
			q.push(ch[p][i]);
		}
		
	}
	
}

void Count(int u) {
	while (u) {
		++Cnt[v[u]];
		u = Fail[u];
	}
}

void Search(char *S) {
	int cur = root, idx, f;
	while (*S) {
		if (*S < 'A' || *S > 'Z') {
			cur = root; ++S; continue;
		}
		idx = *S - 'A';
		if (ch[cur][idx]) {
			cur = ch[cur][idx];
		} else {
			f = Fail[cur];
			while (!ch[f][idx] && f) f = Fail[f];
			
			if (ch[f][idx]) cur = ch[f][idx];
			else cur = root;
			
		}
		if (v[cur]) Count(cur);
		++S;
	}
	
}

int main() {
	int N;
	while (scanf("%d\n", &N) == 1) {
		totN = -1;
		root = NewNode();
		memset(Cnt, 0, sizeof Cnt);
		for (int i = 1; i <= N; ++i) {
			gets(virus[i]);
			Insert(virus[i], i);
		}
		BuildFail();
		gets(tmpS);
		Search(tmpS);
		for (int i = 1; i <= N; ++i)
			if (Cnt[i]) {
				printf("%s: %d\n", virus[i], Cnt[i]);
			}
		
	}
	
	return 0;
}
