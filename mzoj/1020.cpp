#include <cmath>
#include <cstdio>
#include <cstring>
#define N 100005
#define SN 320
int v[N], bel[N], l[SN], r[SN], ly[SN];
int n, m, blo, ret;

void rebuild(int u) {
	if (~ly[u]) for (int i = l[u]; i <= r[u]; ++i) v[i] = ly[u];
	ly[u] = -1;
}
void cal(int a, int b, int c) {
	ret = 0;
	if (bel[a] == bel[b]) {
		rebuild(bel[a]);
		for (int i = a; i <= b; ++i)
		  if (v[i] ^ c) v[i] = c;
		  else ++ret;
		return;
	}

	rebuild(bel[a]);
	for (int i = a; i <= r[bel[a]]; ++i)
	  if (v[i] ^ c) v[i] = c;
	  else ++ret;
	rebuild(bel[b]);
	for (int i = l[bel[b]]; i <= b; ++i)
	  if (v[i] ^ c) v[i] = c;
	  else ++ret;

	for (int i = bel[a] + 1; i < bel[b]; ++i)
	  if (~ly[i]) {
		  if (ly[i] ^ c) ly[i] = c;
		  else ret += blo;
	  } else {
		  for (int j = l[i]; j <= r[i]; ++j)
			if (v[j] ^ c) v[j] = c;
			else ++ret;
		  ly[i] = c;
	  }
}

int main() {
	scanf("%d", &n); blo = sqrt(n);
	for (int i = 1; i <= n; ++i) scanf("%d",v+i),bel[i]=(i-1)/blo+1;
	m = (n - 1) / blo + 1;
	for (int i = 1; i <= m; ++i)
	  l[i]=(i-1)*blo+1,r[i]=i*blo,ly[i]=-1;
	r[m] = n;
	int a, b, c;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		cal(a, b, c);
		printf("%d\n", ret);
	}
	return 0;
}
