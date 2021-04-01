#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int Siz = 26, Maxl = 1000010, MS = 5000000;
int ch[MS][Siz], Cnt[MS], root, totN, Fail[MS], ans;

int NewNode() {
	Cnt[++totN] = 0;
	memset(ch[totN], 0, sizeof ch[totN]);
	return totN;
}

void Insert(char *S) {
	int cur = root;
	char idx;
	while (*S) {
		idx = *S - 'a';
		if (ch[cur][idx]) {
			cur = ch[cur][idx];
		} else {
			cur = ch[cur][idx] = NewNode();
		}
		++S;
	}
	++Cnt[cur];
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
		ans += Cnt[u]; Cnt[u] = 0;
		u = Fail[u];
	}
}

void Search(char *S) {
	ans = 0;
	int cur = root, idx, f;
	while (*S) {
		idx = *S - 'a';
		if (ch[cur][idx]) {
			cur = ch[cur][idx];
		} else {
			f = Fail[cur];
			while (!ch[f][idx] && f) f = Fail[f];
			
			if (ch[f][idx]) cur = ch[f][idx];
			else cur = root;
			
		}
		if (Cnt[cur]) Count(cur);
		++S;
	}
	
} 

char tmpS[Maxl];
void Work() {
	int N;
	scanf("%d", &N);
	totN = -1; root = NewNode();
	getchar();
	while (N--) {
		gets(tmpS);
		Insert(tmpS);
	}
	BuildFail();
	gets(tmpS);
	Search(tmpS);
	printf("%d\n", ans);
}


int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		Work();
	}
	return 0;	
}
