#include <cstdio>
#include <cstring>

char S[300005], c;
int n, i, j, ret, m, x;

int main() {
	scanf("%d%d%s", &n, &m, S);
	ret = 0;
	for (i = 0; i < n;) {
		if (S[i] ^ '.') ++i;
		else {
			for (j = i; S[j] == '.'; ++j);
			ret += j - i - 1;
			i = j;
		}
	}
	while (m--) {
		scanf("%d %c", &x, &c);
		if (c ^ '.') {
			if (S[x-1] ^ '.') { printf("%d\n", ret); continue; }
			if (x < n && S[x]   == '.') --ret;
			if (x > 0 && S[x-2] == '.') --ret;
			printf("%d\n", ret); S[x-1] = c;
		} else {
			if (S[x-1] ^ '.') {
				
			if (x < n && S[x]   == '.') ++ret;
			if (x > 0 && S[x-2] == '.') ++ret;
			printf("%d\n", ret); S[x-1] = c;
			} else printf("%d\n", ret);
		}
	}
	return 0;
}
