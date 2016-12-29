#include <cstdio>
#include <algorithm>

const int Maxn = 1e5 + 10;
typedef long long LL;
int pos[Maxn], N, C;

bool check(const int &v) {
	int Cnt = 1, head = pos[1];
	for (int i = 2; i <= N; ++i) {
		if (pos[i] - head >= v) {
			++Cnt; head = pos[i];
		}
	}
	
	return Cnt >= C;
}

int main() {
	scanf("%d%d", &N, &C);
	for (int i = 1; i <= N; ++i) 
		scanf("%d", pos + i);
	std::sort(pos + 1, pos + N + 1);
	int l = 0, r = pos[N] - pos[1], mid, ans = -1;
	while (l <= r) {
		mid = ((LL)l + r) >> 1;
		if (check(mid)) {
			ans = mid; l = mid + 1;
		} else r = mid - 1;
	}
	printf("%d", ans);
	return 0;
}
