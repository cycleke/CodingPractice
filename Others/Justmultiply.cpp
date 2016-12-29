#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#define ll long long
using namespace std;

char s[10010];
ll m;

ll mul(ll a,ll b) {
	ll ret=0;
	while(b) {
		if(b&1) ret=(ret+a)%m;
		a=(a<<1)%m; b>>=1;
	}return ret;
}

ll Pow(ll a,ll b) {
	ll ret=1;
	while(b) {
		if(b&1) ret=mul(ret,a);
		a=mul(a,a); b>>=1;
	}return ret;
}

ll Pow(string b, string e) {
	ll t=0;
	for(int i=0;i<b.length();++i) t=mul(t,10)+b[i]-'0';
	ll ret=1%m;
	for(int i=e.length()-1;~i;--i) {
		ret=mul(ret,Pow(t,e[i]-'0'));
		t=Pow(t,10);
	}return ret;
}

void Work() {
	scanf("%lld%s",&m,s);
	ll ans=1%m; char *p=s,*r,*q;
	while(true) {
		for(q=p;isdigit(*q);++q);
		for(r=q+2;isdigit(*r);++r);
		ans=mul(ans,Pow(string(p,q),string(q+2,r)));
		if(*r=='\0') break;
		p=r+1;
	} printf("%lld\n",ans);
}

int main() {
	int T; scanf("%d",&T);
	while(T--) Work();
	return 0;
}
