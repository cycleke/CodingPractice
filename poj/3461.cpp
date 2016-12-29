#include <cstdio>
#include <cstring>

char W[10005], T[1000005];
int nxt[1000005];

void getnxt(int len) {
	int j = 0;
	for (int i = 2; i <= len; ++i) {
		while (j && W[j+1] != W[i])
		  j = nxt[j];
		if (W[j+1]==W[i]) ++j;
		nxt[i] = j;
	}
}

int Count() {
	int Wl = strlen(W+1), Tl = strlen(T+1);
	if (Wl == 1 && Tl == 1) return W[1] == T[1];
	getnxt(Wl);
	int j = 0, ret = 0;
	for (int i = 1; i <= Tl; ++i) {
		while (j && W[j+1] != T[i])
		  j = nxt[j];
		if (W[j+1]==T[i]) ++j;
		if (j==Wl) ++ret, j = nxt[j];
	}
	return ret;
}

int main() {
	int _; scanf("%d", &_);
	while (_--) {
		scanf("%s%s",W+1,T+1);
		printf("%d\n", Count());
	}
	return 0;
}
