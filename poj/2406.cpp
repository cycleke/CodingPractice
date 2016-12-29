#include <cstdio>
#include <cstring>

int nxt[4000010];
char s[4000010];

int main() {
	while (scanf("%s", s + 1) ^ EOF) {
		if (s[1]=='.') break;
		int j = 0, len = 1;
		for (int i = 2; s[i]; ++i, ++len) {
			while (j && s[j+1] != s[i])
			  j = nxt[j];
			if (s[j+1]==s[i]) ++j;
			nxt[i] = j;
		}
		if (len % (len - nxt[len])) puts("1");
		else printf("%d\n", len / (len - nxt[len]));
	}
	return 0;
}
