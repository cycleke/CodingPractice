// by OwenCreeper
#include "bits/stdc++.h"
#define N 100000
using namespace std;
long long l[N + 5];
int A, B, n, T, Case = 0;
void work() {
	scanf("%d%d%d", &A, &B, &n);
	int mx = A;
	for (int i = 1; i <= A; i++) {
		int x;
		scanf("%d", &x);
		l[i] = l[i - 1] + x;
	}
	while (n--) {
		int pos = lower_bound(l + 1, l + 1 + mx, A) - l, tpb = B, tpa = A;
		B = A - l[pos - 1], A = pos;
		if (tpa == A && tpb == B) break;
	}
	Case++;
	printf("Case #%d: %d-%d\n", Case, A, B);
}
int main(int argc, char const *argv[]) {
	scanf("%d", &T);
	while (T--) work();
	return 0;
}
