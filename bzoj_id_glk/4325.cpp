#include <cstdio>
#include <cstring>
#define cmin(a,b) ((__t=(b))<a?a=__t:1)
int s[15], __t, ina, ans;
char inc, inb[1<<16], *ins = inb, *ine = inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while ((inc=getc())<'0'||inc>'9'); ina=inc-'0';
	while ((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}

void dfs(int used) {
	if (used > ans) return;
	int i, j, s1, s2, s3, s4; s1 = s2 = s3 = s4 = 0;
	for (i = 1; i < 15; ++i) s1 += s[i]==1, s2 += s[i]==2;
	for (i = 1; i < 15; ++i) 
	  if (s[i] == 4) {
		  ++s4;
		  if (s1 >= 2) s1 -= 2;
		  else if (s2 >= 2) s2 -= 2;
		  else if (s2) --s2;
	  }
	for (i = 1; i < 15; ++i)
	  if (s[i] == 3) {
		  ++s3;
		  if (s1) --s1;
		  else if (s2) --s2;
	  }
	cmin(ans, used + s1 + s2 + s3 + s4);
	for (i = 1; i < 9; ++i) {
		for (j = i; j < 13; ++j) {
			if ((--s[j]) < 0) break;
			if (j - i >= 4) dfs(used + 1);
		}
		if (j==13) --j;
		while (j >= i) ++s[j--];
	}
	for (i = 1; i < 11; ++i) {
		for (j = i; j < 13; ++j) {
			if ((s[j]-=2) < 0) break;
			if (j - i >= 2) dfs(used + 1);
		}
		if (j==13) --j;
		while (j >= i) s[j--]+=2;
	}
	for (i = 1; i < 12; ++i) {
		for (j = i; j < 13; ++j) {
			if ((s[j]-=3) < 0) break;
			if (j - i >= 1) dfs(used + 1);
		}
		if (j==13) --j;
		while (j >= i) s[j--] += 3;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("T.in", "r", stdin);
#endif
	for (int T = geti(), n = geti(), a, b, i; T; --T) {
		memset(s, 0, 60); ans = 0x7f7f7f7f;
		for (i = n; i; --i) {
			a = geti(), b = geti();
			if (a==0) ++s[14];
			else if (a==1) ++s[12];
			else if (a==2) ++s[13];
			else ++s[a-2];
		}
		dfs(0); printf("%d\n", ans);
	}
	return 0;
}
