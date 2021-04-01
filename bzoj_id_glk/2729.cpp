#include <cstdio>
#include <cstring>
#define base 10000
struct bign{
	int len,a[10020];
	bign() {memset(a,0,sizeof a); len=1;}
	void Out() const {
		printf("%d",a[len]);
		for(int i=len-1;i;--i) printf("%04d",a[i]);
		puts("");
	}
	void clear() {memset(a,0,sizeof a); len=1;}
	void fo() {
		while(a[len+1])++len;
		while(!a[len]&&len>1)--len;
	}
	bign operator + (const bign &b) const {
		bign ret;
		ret.len=(len<b.len)?b.len:len;
		for(int i=1;i<=ret.len;++i) {
			ret.a[i]+=a[i]+b.a[i];
			if(ret.a[i] >= base) ++ret.a[i+1],ret.a[i]-=base;
		}ret.fo();
		return ret;
	}
	bign operator * (const int &b) const {
		bign ret; ret.len=len;
		for(int i=1;i<=len;++i) {
			ret.a[i]+=a[i]*b;
			ret.a[i+1]+=ret.a[i]/base;
			ret.a[i]%=base;
		}ret.fo();
		return ret;
	}
};

void A(int n,int m,bign &a) {
	if(n<m) a=a*0;
	else for(int i=n-m+1;i<=n;++i) a=a*i;
}

int main() {
	int n,m; bign a,b;
	scanf("%d%d",&n,&m);
	a.a[1]=1; b.a[1]=2;
	A(n+1,2,a);	//a.Out();
	A(n+3,m,a); //a.Out();
	A(n+1,1,b); //b.Out();
	A(n+2,m-1,b); //b.Out();
	b=b*m; //b.Out();
	a=a+b; /*a.Out();*/ A(n,n,a);
	a.Out(); return 0;
}
