#include <bits/stdc++.h>
using namespace std;

const int Maxn = 2010;

int A[5], B[Maxn];
int n;
int C[2][Maxn];
long long ans = 0, cnt1, cnt2;

void Add(int *tr, int x, const int &val) {
	while (x < Maxn) {
		tr[x] += val;
		x += x & -x;
	}
}

int Sum(int *tr, int x) {
	int s = 0;
	while (x) {
		s += tr[x];
		x -= x & -x;
	}
	return s;
}

bool cmp(const int &a, const int &b) { return a < b; }

void Rev() {
	swap(A[1], A[4]); swap(A[2], A[3]);
	for (int i = 1; (i << 1) <= n; ++i)
		swap(B[i], B[n - i + 1]);
}

bool check(const int &a, const int &b) {
	return (a == 2 && b == 3) || (a == 3 && b == 2) || (a + b == 4) || (a + b == 6);
}

int getcnt(const int &a, const int &h, const int &bi, const int &bj) {
	if (a == 1) return Sum(C[h], min(bi, bj) - 1);
	if (a == 2 || a == 3) return Sum(C[h], max(bi, bj) - 1) - Sum(C[h], min(bi, bj));
	if (a == 4) return Sum(C[h], n) - Sum(C[h], max(bi, bj));
}

void Solve1() {
	for (int i = 1; i < n - 2; ++i) {
		memset(C, 0, sizeof C);
		for (int j = i + 2; j <= n; ++j) Add(C[1], B[j], 1);
		for (int j = i + 2; j <= n; ++j) {
			Add(C[0], B[j - 1], 1); Add(C[1], B[j], -1);
			if (cmp(B[i], B[j]) == cmp(A[1], A[3])) {
				cnt1 = getcnt(A[2], 0, B[i], B[j]);
				cnt2 = getcnt(A[4], 1, B[i], B[j]);
				ans += cnt1 * cnt2;
			}
		}
	}
}

void Solve2() {
	for (int i = 2; i < n - 1; ++i) {
		for (int j = 1; j <= n; ++j) C[1][j] = 0;
		Add(C[0], B[i - 1], 1);
		for (int j = n - 1; j > i; --j) {
			Add(C[1], B[j + 1], 1);
			if (cmp(B[i], B[j]) == cmp(A[2], A[3])) {
				cnt1 = getcnt(A[1], 0, B[i], B[j]);
				cnt2 = getcnt(A[4], 1, B[i], B[j]);
				ans += cnt1 * cnt2;
			}
		}
	}
}

void Solve3() {
	for (int i = 1; i < n - 2; ++i) {
		memset(C, 0, sizeof C);
		for (int j = i + 2; j <= n; ++j) Add(C[1], B[j], 1);
		for (int j = i + 2; j < n; ++j) {
			Add(C[0], B[j - 1], 1);
			Add(C[1], B[j], -1);
			if (B[i] > B[j]) {
				cnt1 = getcnt(4, 0, B[i], B[j]);
				cnt2 = getcnt(4, 1, B[i], B[j]);
				ans += cnt1 * cnt2;
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= 4; ++i) scanf("%d", A + i);
	for (int i = 1; i <= n; ++i) scanf("%d", B + i);
	if (check(A[1], A[3])) Solve1();
	else if (check(A[2], A[3])) Solve2();
	else if (check(A[2], A[4])) Rev(), Solve1();
	else {
		if (A[1] == 3) Rev();
		swap(A[2], A[4]); Solve2(); ans = -ans;
		Solve3();
	}
	cout << ans << endl;
	return 0;
}


