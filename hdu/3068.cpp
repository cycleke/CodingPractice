#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int Len = 3e5;

int p[Len];
char s[Len], str[Len];

int main() {
	int l1, l2, ans, mx, id, i;
	while (scanf("%s", s) ^ EOF) {
		l1 = strlen(s);
		str[0] = '~', str[1] = '!';
		for (i = 0; i < l1; ++i) str[(i<<1) + 2] = s[i], str[(i<<1) + 3] = '!';
		str[l2 = (l1 << 1) + 2] = '@';
		ans = id = mx = 0;
		for (i = 1; i < l2; ++i) {
			if (i < mx) p[i] = min(p[(id<<1) - i], mx - i);
			else p[i] = 1;
			for (; str[p[i]+i]==str[i-p[i]]; ++p[i]);
			if (p[i] + i > mx) mx = p[i] + i, id = i;
			if (p[i] > ans) ans = p[i];
		}
		printf("%d\n", ans - 1);
	}
	return 0;
}
