#include <cstdio>
#include <cstring>

int ans[100000], len;

int b[310];

int fcal(int d) {
	int pos = 0;
	while (ans[pos] == 9 || d <= 0) {
		d += ans[pos]; ans[pos] = 0;
		++pos;
	}
	++ans[pos]; --d;
	if (len<pos+1) len=pos+1;
	return d;
}

void cal(int d) {
	if (d <= 0) d = fcal(d);
	int pos = 0, t;
	while(d > 0) {
		t = 9 - ans[pos];
		if (t >= d) ans[pos] += d;
		else ans[pos] = 9;
		d -= t; ++pos;
	}
	if (len < pos) len = pos;
}

int main() {

	int n; scanf("%d", &n); len = 1;
	for (int i = 1; i <= n; ++i) scanf("%d", b + i);
	for (int i = 1; i <= n; ++i) {
		cal(b[i]-b[i-1]);
		for (int j = len-1; ~j; --j)
		  putchar('0'+ans[j]);
		puts("");
	}
	return 0;
}
