#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 50010
#define SN 300
int l[SN], r[SN], belong[N], block, sum[SN], v[N];
bool flag[SN];

int ina; char inc, inb[1<<16], *ins = inb, *ine = inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
	while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}

void Cal(int u) {
	if(flag[u]) return;
	flag[u] = true; sum[u] = 0;
	for (int i = l[u]; i <= r[u]; ++i) {
		v[i] = sqrt(v[i]); sum[u] += v[i];
		if (v[i] > 1) flag[u] = false;
	}
}

void Update(int x, int y) {
	if (belong[x] == belong[y]) {
		for (int i = x; i <= y; ++i) {
			sum[belong[i]] -= v[i];
			v[i] = sqrt(v[i]);
			sum[belong[i]] += v[i];
		}
		return;
	}
	for (int i = x; i <= r[belong[x]]; ++i) {
			sum[belong[i]] -= v[i];
			v[i] = sqrt(v[i]);
			sum[belong[i]] += v[i];
	}
	for (int i = l[belong[y]]; i <= y; ++i) {
			sum[belong[i]] -= v[i];
			v[i] = sqrt(v[i]);
			sum[belong[i]] += v[i];
	}
	for (int i = belong[x] + 1; i < belong[y]; ++i)
	  Cal(i);
}

int ret;
int Query(int x, int y) {
	ret = 0;
	if (belong[x] == belong[y]) {
		for (int i = x; i <= y; ++i)
		  ret += v[i];
		return ret;
	}
	for (int i = x; i <= r[belong[x]]; ++i)
	  ret += v[i];
	for (int i = l[belong[y]]; i <= y; ++i)
	  ret += v[i];
	for (int i = belong[x] + 1; i < belong[y]; ++i) 
	  ret += sum[i];
	return ret;
}

int main() {
	int n = geti(), num;
	for (int i = 1; i <= n; ++i) v[i] = geti();
	block = floor(sqrt(n) + 0.5);
	num = n / block; if (n % block) ++num;
	for (int i = 1; i <= num; ++i)
	  l[i]=(i-1)*block+1,r[i]=i*block;
	r[num] = n;
	for (int i = 1; i <= n; ++i) {
		belong[i]=(i-1)/block+1;
		sum[belong[i]] += v[i];
	}
	int f, a, b, c;
	for (int T = 0; T < n; ++T) {
		f = geti(), a = geti(), b = geti(), c = geti();
		if (f) printf("%d\n", Query(a,b));
		else Update(a,b);
	}
	return 0;
}

