#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 50010
#define SN 300
#define ll long long
ll v[N], add[SN], sum[SN];
int l[SN], r[SN], belong[N], block;

int ina; char inc, inb[1<<16], *ins = inb, *ine = inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
	while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}

void Update(int x, int y, int val) {
	if (belong[x] == belong[y]) {
		for (int i = x; i <= y; ++i)
		  v[i] += val;
		sum[belong[x]] += (y - x + 1LL) * val;
		return;
	}
	for (int i = x; i <= r[belong[x]]; ++i)
	  v[i] += val;
	sum[belong[x]] += (r[belong[x]] - x + 1LL) * val;
	for (int i = l[belong[y]]; i <= y; ++i)
	  v[i] += val;
	sum[belong[y]] += (y - l[belong[y]] + 1LL) * val;

	for (int i = belong[x] + 1; i < belong[y]; ++i)
	  add[i] += val;
}

int ret;
int Query(int x, int y, int c) {
	ret = 0;
	if (belong[x] == belong[y]) {
		for (int i = x; i <= y; ++i)
		  ret = (ret + v[i]) % c;
		ret = (ret + (y - x + 1LL) * add[belong[x]]) % c;
		return ret;
	}

	for (int i = x; i <= r[belong[x]]; ++i)
	  ret = (ret + v[i]) % c;
	ret = (ret + (r[belong[x]] - x + 1LL) * add[belong[x]]) % c;

	for (int i = l[belong[y]]; i <= y; ++i)
	  ret = (ret + v[i]) % c;
	ret = (ret + (y - l[belong[y]] + 1LL) * add[belong[y]]) % c;

	for (int i = belong[x] + 1; i < belong[y]; ++i) {
		ret = (ret + sum[i]) % c;
		ret = (ret + (r[i] - l[i] + 1) * add[i]) % c;
	}
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
		if (f) printf("%d\n", Query(a,b,c+1));
		else Update(a,b,c);
	}
	return 0;
}

