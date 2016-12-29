#include <cstdio>
#include <cstring>
using namespace std;

typedef short int sint;
const int Maxn = (65535 << 1) + 100;
sint C[Maxn << 3], lazy[Maxn << 3];
bool Fun[Maxn + 100];
//1 取 0 ，2 取 1 ， 3 取反

void Add(const int &u, const int &val) {
	if (!val) return;
	if (val <= 2) C[u] = val - 1, lazy[u] = val;
	else {
		lazy[u] = 3 - lazy[u];
		if (~C[u]) C[u] ^= 1;
	}
}

void Down(const int &u) {
	if (!lazy[u]) return;
	Add(u << 1, lazy[u]); Add(u << 1 | 1, lazy[u]);
	lazy[u] = 0;
}

void Up(int u) {
	if (C[u<<1] ^ C[u<<1|1]) C[u] = -1;
	else C[u] = C[u<<1];
}

void Update(int u, int l, int r, int x, int y, const int &val) {
	if (x > y) return;
	if (!(l ^ x) && !(r ^ y)) {
		Add(u, val); return;
	}
	Down(u);
	int mid = (l + r) >> 1;
	if (y <= mid) Update(u << 1, l, mid, x, y, val);
	else if (x > mid) Update(u << 1 | 1, mid + 1, r, x, y, val);
	else {
		Update(u << 1, l, mid, x, mid, val);
		Update(u << 1 | 1, mid + 1, r, mid + 1, y, val);
	}
	Up(u);
 }

void Query(int u, int l, int r) {
	if (~C[u]) {
		for (int i = l; i <= r; ++i) Fun[i] = C[u];
	} else {
		Down(u);
		int mid = (l + r) >> 1;
		Query(u<<1, l, mid);
		Query(u<<1|1, mid + 1, r);
	}
}

void Print(const int &l, const int &r) {
	if (l & 1) printf("(%d,", l >> 1);
	else printf("[%d,", l >> 1);
	if (r & 1) printf("%d)", (r+1) >> 1);
	else printf("%d]", (r+1) >> 1);
}

void Out() {
	Query(1, 0, Maxn);
	int cnt = 0, s;
	bool flag = false;
	for (int i = 0; i <= Maxn; ++i) {
		if (Fun[i] && !flag) {
			s = i; flag = true;
		} else if (!Fun[i] && flag) {
			if (cnt++) putchar(' ');
			Print(s, i - 1);
			flag = false;
		}
	}
	if (!cnt) puts("empty set");
	else puts("");
}

int main() {
	freopen("A.in","r",stdin);
	char op, l, r; int a, b;
	while (scanf("%c %c%d,%d%c\n", &op, &l, &a, &b, &r) != EOF) {
		a <<= 1; b <<= 1;
		if (l == '(') ++a;
		if (r == ')') --b;
		if (a > b) {
			if (op == 'C' || op == 'I')  Update(1,0,Maxn,0,Maxn,1);
			continue;
		}
		if (op == 'U') {
			Update(1, 0, Maxn, a, b, 2);
		} else if (op == 'I') {
			Update(1, 0, Maxn, 0, a - 1, 1);
			Update(1, 0, Maxn, b + 1, Maxn, 1);
		} else if (op == 'D') {
			Update(1, 0, Maxn, a, b, 1);
		} else if (op == 'C') {
			Update(1, 0, Maxn, 0, a - 1, 1);
			Update(1, 0, Maxn, b + 1, Maxn, 1);
			Update(1, 0, Maxn, a, b, 3);
		} else Update(1, 0, Maxn, a, b, 3);

		//Out();
	}
	Out();
	return 0;
}
