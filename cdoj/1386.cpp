#include <cstdio>
#include <cstring>
#define N 100010

int nxt[N], len;
char str[N];

void getnxt() {
	int j = 0;
	for (int i = 2; i <= len; ++i) {
		while (j && str[j+1] != str[i])
		  j = nxt[j];
		if (str[j+1]==str[i]) ++j;
		nxt[i] = j;
	}

}

bool KMP(char *T, char *P, int n, int m) {
	int j = 0;
	for (int i = 1; i <= n; ++i) {
		while (j && P[j+1]!=T[i])
		  j = nxt[j];
		if (P[j+1]==T[i]) ++j;
		if (j == m) return true;
	}
	return false;
}

void Work() {
	scanf("%s", str + 1);
	len = strlen(str + 1);
	getnxt();
	int j = nxt[len], ans = 0;
	while (j) {
		if (len >= j * 3 && KMP(str+j,str,len-(j<<1),j)) {
			ans = j; break;
		}
		j = nxt[j];
	}
	printf("%d\n", ans);
}


int main() {
	int T; scanf("%d", &T);
	while (T--) Work();
	return 0;
}
