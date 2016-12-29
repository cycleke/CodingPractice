#include <cstdio>
#include <cstring>
const int MS=(int)(1e5+10)<<2,N=1e5+10;
int c[MS][3],s[MS],cnt[3];
char bs[N];
#define ls u<<1
#define rs u<<1|1
#define lson u<<1,l,mid
#define rson u<<1|1,mid+1,r
#define MID int mid=l+r>>1

void Up(int u) {
	s[u]=(s[ls]+s[rs])%3;
	for(int i=0;i<3;++i) c[u][i]=c[ls][i];
	int p=s[ls];
	for(int i=0;i<3;++i) c[u][(i+p)%3]+=c[rs][i];
}

void Build(int u,int l,int r) {
	if(l==r) {
		memset(c[u],0,sizeof c[u]);
		s[u]=(bs[l]-'0')%3; c[u][s[u]]=1;
	} else {
		MID; Build(lson),Build(rson); Up(u);
	}
}
void Update(int u,int l,int r,int p,int val) {
	if(l==r) {
		memset(c[u],0,sizeof c[u]);
		s[u]=val; c[u][val]=1;
	} else {
		MID;
		if(p<=mid) Update(lson,p,val);
		else Update(rson,p,val);
		Up(u);
	}
}
void Query(int u,int l,int r,int x,int y,int &d) {
	if(l>=x&&r<=y) {
		for(int i=0;i<3;++i) cnt[(i+d)%3]+=c[u][i];
		d=(d+s[u])%3;
	} else {
		MID;
		if(y<=mid) Query(lson,x,y,d);
		else if(x>mid) Query(rson,x,y,d);
		else Query(lson,x,mid,d),Query(rson,mid+1,y,d);
	}
}

int main() {
	int n,m,x,y,op,d; long long ans;
	scanf("%d%d%s",&n,&m,bs+1); Build(1,1,n);
	while(m--) {
		scanf("%d%d%d",&op,&x,&y);
		if(op==1) Update(1,1,n,x,y);
		else {
			ans=d=0; memset(cnt,0,sizeof cnt);
			cnt[0]=1;
			Query(1,1,n,x,y,d);
			for(int i=0;i<3;++i) ans+=(long long)cnt[i]*(cnt[i]-1LL)>>1;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
