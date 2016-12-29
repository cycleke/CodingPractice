#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MS = 1005;
int ls[MS], rs[MS], p[MS], k, totN;
char op[MS], s[MS];

inline int New(const int &l, const int &r, const char &o, const int &pp) {
	++totN; ls[totN] = l, rs[totN] = r, op[totN] = o, p[totN] = pp;
	return totN;
}

inline void FPC(const char &o) {
	switch (o) {
		case '+' : putchar('-'); break;
		case '-' : putchar('+'); break;
		case '*' : putchar('/'); break;
		case '/' : putchar('*'); break;
	}
}

int f();
int g();
int d();
void Print(int u, bool flag);

int main() {
	int t;
	while (scanf("%s", s) ^ EOF) {
		memset(ls, 0, sizeof ls);
		memset(rs, 0, sizeof rs);
		memset(p, 0, sizeof p);
		memset(op, 0, sizeof op);
		totN = k = 0;
		t = f();
		Print(t, false);
		memset(s, 0, sizeof s);
	}
	return 0;
}

int f() {
	int l, r; char o;
	l = g();
	while (s[k]=='+' || s[k] == '-') {
		o = s[k++]; r = g();
		l = New(l, r, o, 1);
	}
	return l;
}

int g() {
	int l, r; char o;
	l = d();
	while (s[k]=='*' || s[k] == '/') {
		o = s[k++]; r = d();
		l = New(l, r, o, 2);
	}
	return l;
}

int d() {
	if (s[k] >= 'a' && s[k] <= 'z') return New(0, 0, s[k++], 3);
	++k; int ret = f(); ++k; return ret;
}

void Print(int u, bool flag) {
	if (op[u] >= 'a' && op[u] <= 'z') { putchar(op[u]); return; }
	int l = ls[u], r = rs[u];

	if (p[l] > p[u]) Print(l, false);
	else if (p[l] < p[u]) {
		putchar('('); Print(l, false); putchar(')');
	} else Print(l, flag);
	if (!flag) putchar(op[u]);
	else FPC(op[u]);

	if (p[r] > p[u]) Print(r, false);
	else if (p[r] < p[u]) {
		putchar('('); Print(r, false); putchar(')');
	} else {
		if (op[u] == '-' || op[u] == '/') flag = !flag;
		Print(r, flag);
	}
}
