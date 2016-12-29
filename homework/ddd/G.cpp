#include <cstdio>
#include <cstring>

char num[1005], tmp;
int m, len;

int main() {
	while (scanf("%s%d", num, &m) == 2) {
		len = strlen(num);
		num[len] = 0;
		for (int i = m; i; --i) 
		for (int j = 0, k; j < len; ++j) {
			if (!(~num[j])) continue;
			for (k = j + 1; k < len; ++k) if (num[k] >= '0') break;
			if (num[j] > num[k]) {
				num[j] = -1; break;
			}
		}
		bool Notzero = 0;
		for (int i = 0; i < len; ++i) {
			Notzero |= (num[i] > '0');
			if (~num[i] && Notzero) putchar(num[i]);
		}
		if (!Notzero) putchar('0');
		puts("");
	}
	return 0;
}
