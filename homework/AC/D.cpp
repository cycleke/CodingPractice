#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

inline char idx(const char &c) {
	switch (c) {
		case 'A' : return 0;
		case 'T' : return 1; 
		case 'C' : return 2; 
		case 'G' : return 3; 
	}
}

//AC-auto
const int MS = 110, Siz = 4;
int ch[MS][Siz], root, totN, Fail[MS];
bool Unable[MS];

int NewNode() {
	Unable[++totN] = 0;
	memset(ch[totN], 0, sizeof ch[totN]);
	return totN;
}

void Insert(char *S) {
	int cur = root;
	char id;
	while (*S) {
		id = idx(*S);
		if (ch[cur][id]) {
			cur = ch[cur][id];
		} else {
			cur = ch[cur][id] = NewNode();
		}
		++S;
	}
	Unable[cur] = 1;
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
		if (Unable[Fail[p]]) Unable[p] = 1;
		for (int i = 0; i < Siz; ++i) 
		if (ch[p][i]) {
			f = Fail[p];
			
			while (!ch[f][i] && f) f = Fail[f];
			
			if (ch[f][i]) Fail[ch[p][i]] = ch[f][i];
			else Fail[ch[p][i]] = root;
			
			q.push(ch[p][i]);
		} else {
			ch[p][i] = ch[Fail[p]][i];
		}
		
	}
	
}

//Matrix

typedef long long LL;
const int Mod = 100000;

LL tmp1[MS][MS], tmp2[MS][MS];

void Matmul(LL A[MS][MS], LL B[MS][MS]){
	memset(tmp1, 0, sizeof tmp1);
	for (int i = 0; i <= totN; ++i)
	for (int j = 0; j <= totN; ++j) 
	for (int k = 0; k <= totN; ++k) 
	tmp1[i][j] = (tmp1[i][j] + A[i][k] * B[k][j]) % Mod;;

	memcpy(A, tmp1, sizeof tmp1);
}

void MatPow(LL A[MS][MS], int n) {
		for (int i = totN; ~i; --i)
		for (int j = totN; ~j; --j)
		tmp2[i][j] = (i == j);
		while (n) {
			if (n & 1) Matmul(tmp2, A);
			Matmul(A, A);
			n >>= 1;
		}
		memcpy(A, tmp2, sizeof tmp2);
	}

//

void BuildMat(LL A[MS][MS]) {
	for (int i = 0; i <= totN; ++i)
	for (int j = 0; j < Siz; ++j)
	if (!Unable[i] && !Unable[ch[i][j]])
	++A[i][ch[i][j]];
}


char tmpS[12];

int main() {
	int n, m, tot;
	LL ans[MS][MS];
	while (scanf("%d%d\n", &m, &n) == 2) {
		totN = -1; root = NewNode();
		while (m--) {
			gets(tmpS);
			Insert(tmpS);
		}
		BuildFail();
		memset(ans, 0, sizeof ans);
		BuildMat(ans);
		
		for (int i = 0; i <= totN; ++i) {
			for (int j = 0; j <= totN; ++j)
			printf("%d ", ans[i][j]);
			puts("");
		}
		tot = 0;
		MatPow(ans, n);
		for (int i = 0; i <= totN; ++i) {
			tot += ans[0][i];
			tot %= Mod;
		}
		printf("%d\n", tot);
	}
	return 0;
}
