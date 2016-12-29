#include <cstdio>
#include <cstring>

struct bign {
	int num[100], len;
	bign() { memset(num, 0, sizeof num); len = 1; }
	void Write() const {
		for (int i = len - 1; ~i; --i)
			printf("%d", num[i]);
	}
};

int main() {
	int n; bign a, b, c;
	scanf("%d", &n);
	if (n == 1) { puts("1"); return 0;} 
	else if (n == 2) { puts("5"); return 0; }
	a.num[0] = 1; b.num[0] = 5;
	for (int i = 3, j; i <= n; ++i) {// c = f[i], a = f[i - 2], b = f[i - 1]    
		//c = 3 * b - a + 2    
		c = b;
		for (j = 0; j < b.len; ++j) 
			c.num[j] *= 3;
		for (j = 0; j < b.len; ++j)
			c.num[j + 1] += c.num[j] / 10, c.num[j] %= 10;
		if (c.num[b.len]) ++c.len;
		//c.Write(); puts("");
		c.num[0] += 2;
		j = 1;
		while (c.num[j] >= 10) { c.num[j + 1] += c.num[j] / 10; c.num[j] /= 10; ++j; }
		//c.Write(); puts("");
		if (j == c.len) ++c.len;
		for (j = 0; j < c.len; ++j) {
			c.num[j] -= a.num[j];
			if (c.num[j] < 0) --c.num[j + 1], c.num[j] += 10;
		}
		while (c.num[c.len - 1] == 0) --c.len;
		a = b; b = c;
	}
	c.Write();
	return 0;
}
