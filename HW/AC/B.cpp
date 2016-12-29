#include <set>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MS = 100010, Siz = 128, Maxl = 10010;
int ch[MS][Siz], Fail[MS], root, totN, id[MS];
char tmpS[Maxl];

priority_queue<int, vector<int>, greater<int> >pq;

//AC

int NewNode() {
	id[++totN] = 0;
	memset(ch[totN], 0, sizeof ch[totN]);
	return totN;
}


void Insert(char *S, const int &val) {
	int cur = root;
	char idx;
	while (*S) {
		idx = *S;
		if (ch[cur][idx]) {
			cur = ch[cur][idx];
		} else {
			cur = ch[cur][idx] = NewNode();
		}
		++S;
	}
	id[cur] = val;
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
		if (id[u]) pq.push(id[u]);
		u = Fail[u];
	}
}

void Search(char *S) {
	int cur = root, idx, f;
	while (*S) {
		idx = *S;
		if (ch[cur][idx]) {
			cur = ch[cur][idx];
		} else {
			f = Fail[cur];
			while (!ch[f][idx] && f) f = Fail[f];
			
			if (ch[f][idx]) cur = ch[f][idx];
			else cur = root;
			
		}
		if (id[cur]) Count(cur);
		++S;
	}
	
} 


//

int main() {
	
	int N, M;
	scanf("%d", &N);
	getchar();
	totN = -1; root = NewNode();
	for (int i = 1; i <= N; ++i) {
		gets(tmpS);
		Insert(tmpS, i);
	}
	BuildFail();
	
	int tot = 0;
	scanf("%d", &M);
	getchar();
	for (int i = 1; i <= M; ++i) {
		gets(tmpS);
		Search(tmpS);
		if (!pq.empty()) {
			++tot;
			printf("web %d:", i);
			int k = 0;
			while (!pq.empty()) {
				if (k == pq.top()) {
					pq.pop(); continue;
				}
				k = pq.top(); printf(" %d", k);
				pq.pop();
			}
			puts("");
		}
	}
	printf("total: %d\n", tot);
	return 0;
}
