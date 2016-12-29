#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

//AC auto

const int MS = 33, Siz = 26;
int ch[MS][Siz], Fail[MS], root, totN;
bool is_R[MS];

int NewNode() {
	is_R[++totN] = 0;
	memset(ch[totN], 0, sizeof ch[totN]);
	return totN;
}

void Insert(char *S) {
	int cur = root, idx;
	while (*S) {
		idx = *S - 'a';
		if (!ch[cur][idx]) ch[cur][idx] = NewNode();
		cur = ch[cur][idx];
		++S;
	}
	is_R[cur] = 1;
}

void BuildFail() {
	queue<int>q;
	Fail[root] = root;
	for (int i = 0; i < Siz; ++i) if (ch[root][i]) {
		Fail[ch[root][i]] = root;
		q.push(ch[root][i]);
	} 
	int p, f;
	while (!q.empty()) {
		p = q.front(); q.pop();
		if (is_R[Fail[p]]) is_R[p] = 1;
		for (int i = 0; i <Siz; ++i)
		if (ch[p][i]) {
			f = Fail[p];
			
			while (!ch[f][i] && f) f = Fail[f];
			
			if (ch[f][i]) Fail[ch[p][i]] = ch[f][i];
			else Fail[ch[p][i]] = root;
			
			q.push(ch[p][i]);
			
		} else ch[p][i] = ch[Fail[p]][i];		
	}
}

//Matix
typedef unsigned long long LL;
struct Mat {
	LL mp[MS][MS];
	void clear() {
		memset(mp, 0, sizeof mp);
	}
	Mat() { this->clear(); }
	
	Mat operator + (const Mat &A) const {
		Mat C;
		for (int i = 0; i < MS; ++i)
		for (int j = 0; j < MS; ++j)
		C.mp[i][j] = mp[i][j] + A.mp[i][j];
		return C;
	}
	
	Mat operator * (const Mat &A) const {
		Mat C;
		for (int i = 0; i < MS; ++i)
		for (int j = 0; j < MS; ++j)
		for (int k = 0; k < MS; ++k)
		C.mp[i][j] += mp[i][k] * A.mp[k][j];
		return C;
	}
	
	Mat operator ^ (const int &c) const {
		int k = c;
		Mat B = *this, C;
		for (int i = 0; i < MS; ++i) C.mp[i][i] = 1;
		while (k) {
			if (k & 1) C = C * B;
			B = B * B;
			k >>= 1;
		}
	}
	
	Mat operator << (const LL &c) const {
		int i;
		for (i = 0; (1 << i) <= c; ++i);
		Mat C, B;
		C = B = *this;
		for (i -= 2; ~i; --i) {
			C = C + C * B;
			B = B * B;
			if ((1 << i) & c) B = B * (*this), C = C + B;
		}
		return C;
	}	
	
};

void BuildMat(Mat &A) {
	A.clear();
	for (int i = 0; i <= totN; ++i)
	for (int j = 0; j < Siz; ++j)
	if (!is_R[i] && !is_R[ch[i][j]]) ++A.mp[i][ch[i][j]];
}

const LL inr = 10330176681277348905ULL;

char tmpS[10];

LL mod_pow(LL base, LL n) {
	LL ans = 1;
	while (n) {
		if (n & 1) ans = ans * base;
		base = base * base;
		n >>= 1;
	}
	return ans;
}

int main() {
	int N;
	LL L,tot;
	Mat ans;
	while (scanf("%d", &N) == 1) {
		cin >> L;
		totN = -1; root = NewNode();
		while (N--) {
			scanf("%s", tmpS);
			Insert(tmpS);
		}
		BuildFail();
		BuildMat(ans);
		ans = ans << L;
		tot = mod_pow(26,(LL)L + 1) - 26;
		tot = tot * inr;
		for (int i = 0; i <= totN; ++i)
		tot -= ans.mp[0][i];
		cout << tot << endl;
	}
	return 0;
}
