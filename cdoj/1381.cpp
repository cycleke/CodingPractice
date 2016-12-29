#include <cstdio>
#include <cstring>

char W[100005], T[100005];
int nxt[100005];

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
		if (j==Wl) ++ret, j = 0;
	}
	return ret;
}

int main() {
	scanf("%s%s",T+1,W+1);
	printf("%d\n", Count());
	return 0; 
}
