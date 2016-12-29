#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int a[55];

int main() {
	int n, Max, ans, left, pre;
	while (scanf("%d", &n) ^ EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		sort(a + 1, a + n + 1);
		Max = a[pre = ans = 1]; left = 0;
		for (int i = 2; i <= n; ++i)
		if (a[i] > Max && i - pre + left >= ans + 1 && a[i] > a[i - 1]){
			Max = a[i]; left += i - pre - ans - 1;
			pre = i; ++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}
