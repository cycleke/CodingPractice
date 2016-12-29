#include <bits/stdc++.h>
using namespace std;
#define MS 1000000
int ch[2][MS], totNode, v[MS];

void Insert(const int &x) {
	int u, i, t;
	for (u = 0, i = 1 << 19, t; i; i >>= 1) {
		t = (x&i)?1:0;
		if (!ch[t][u]) ch[t][u] = ++totNode;
		u = ch[t][u];
	}
	v[u] = x;
}
int Search(int x) {
	int u, i, t; x = ~x;
	for (u = 0, i = 1 << 19, t; i; i>>= 1) {
		t = (x&i)?1:0;
		if (!ch[t][u]) t ^= 1;
		u = ch[t][u];
	}
	return v[u];
}

int main() {
	int n, m, op, a, id = 0;
	scanf("%d", &n);
	while (n--) scanf("%d", &a), Insert(a);
	scanf("%d", &m);
	while (m--) {
		scanf("%d%d", &op, &a);
		if (op) printf("%d\n", Search(a));
		else Insert(a);
	}
	return 0;
}
