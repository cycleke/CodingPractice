#include <cmath>
#include <cstdio>
#include <cstring>
#define N 100005
#define SN 420
#define Mod 10007
int l[SN], r[SN], mly[SN], aly[SN], bel[N];
int v[N], n, blo, m;

void rebuild(int u) {
	for (int i = l[u]; i <= r[u]; ++i)
	  v[i] = (v[i] * mly[u] + aly[u]) % Mod;
	mly[u] = 1, aly[u] = 0;
}

#define Cal(x,f,c) ((f?x*=c:x+=c),x%=Mod)

void Update(int f, int a, int b, int c) {
	if (bel[a] == bel[b]) {
		rebuild(bel[a]);
		for (int i = a; i <= b; ++i)
		  Cal(v[i], f, c);
		return;
	}

	rebuild(bel[a]); rebuild(bel[b]);
	for (int i = a; i <= r[bel[a]]; ++i)
	  Cal(v[i], f, c);
	for (int i = l[bel[b]]; i <= b; ++i)
	  Cal(v[i], f, c);

	for (int i = bel[a]+1; i < bel[b]; ++i)
	  if (f) aly[i] = aly[i] * c % Mod, mly[i] = mly[i] * c % Mod;
	  else aly[i] = (aly[i] + c) % Mod;
}

int main() {
	scanf("%d", &n); blo = sqrt(n);
	for (int i = 1; i <= n; ++i) scanf("%d", v + i);
	m = (n - 1) / blo + 1;
	for (int i = 1; i <= n; ++i)
	  bel[i] = (i - 1) / blo + 1;
	for (int i = 1; i <= m; ++i)
	  mly[i]=1,aly[i]=0,l[i]=(i-1)*blo+1,r[i]=i*blo;
	r[m] = n;
	int f, a, b, c;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d%d", &f, &a, &b, &c);
		if (f < 2) Update(f, a, b, c);
		else printf("%d\n", (v[b] * mly[bel[b]] + aly[bel[b]]) % Mod);
	}
	return 0;
}
