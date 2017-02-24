#include <cstdio>
#include <cstring>
#include <algorithm>

int c1[10], c2[10], a1[10], a2[10];
char s[1005];

int main() {
	int n;
	scanf("%d", &n);
	scanf("%s", s);
	for (int i = 0; i < n; ++i) ++c1[s[i] - '0'], ++a1[s[i] - '0'];
	scanf("%s", s);
	for (int i = 0; i < n; ++i) ++c2[s[i] - '0'], ++a2[s[i] - '0'];
	
	
	int ans = 0;

	
	for (int i = 0; i < 10; ++i) {
	    int cnt = 0;
		for (int j = i; j < 10 && cnt < a1[i]; ++j)
			cnt += a2[j];
		cnt = std::min(cnt, a1[i]);
		ans += cnt;
		for (int j = i; j < 10 && cnt; ++j) {
			int t = std::min(cnt, a2[j]);
			a2[j] -= t;
			cnt -= t;
		}
		
	}
	
	printf("%d\n", n - ans);
	
	ans = 0;
	for (int i = 0; i < 9; ++i) {
	    int cnt = 0;
		for (int j = i + 1; j < 10 && cnt < c1[i]; ++j)
			cnt += c2[j];
		cnt = std::min(cnt, c1[i]);
		ans += cnt;
		for (int j = i + 1; j < 10 && cnt; ++j) {
			int t = std::min(cnt, c2[j]);
			c2[j] -= t;
			cnt -= t;
		}
		
	}
	printf("%d\n", ans);
	return 0;
}
