#include <cstdio>
#include <cstring>
inline int cal() {
	static int i, j, k, l;
	static char c1, c2, s[100005];
	i = 0, j = 1;
	scanf("%s", s);
	l = strlen(s);
	while (true) {
		for (k = 0; k < l; ++k) {
			c1 = s[(i + k) % l];
			c2 = s[(j + k) % l];
			if (c1 ^ c2) break;
		}
		if (k == l) break;
		if (c1 > c2) {
			i += k + 1;
			if (i == j) ++i;
		}
		else {
			j += k + 1;
			if (j == i) ++j;
		}
	}
	return i < j ? i : j;
}
int main() {
	int __;
	scanf("%d", &__);
	while (__--) printf("%d\n", cal() + 1);
	return 0;
}
