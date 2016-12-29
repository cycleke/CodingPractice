#include <cstdio>
#define N 100005
int C[N<<2],best,ans,pre,n,m;
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	for(;(inc=getc())<'0'||inc>'9';);
	for(ina=inc-'0';(inc=getc())>='0'&&inc<='9';ina=(ina<<3)+(ina<<1)+inc-'0');
	return ina;
}
#define Down(u) ((~C[u])?C[u<<1]=C[u<<1|1]=C[u],C[u]=-1:1)
#define Up(u) ((C[u<<1]==C[u<<1|1]&&C[u]==-1)?C[u]=C[u<<1]:1)
void Update(int u,int l,int r,int x,int y,int op) {
	if(x<=l&&r<=y) {
		if(op<2) {C[u]=op;return;}
		else if(~C[u]) {C[u]^=1;return;}
	}Down(u);
	int m=l+r>>1;
	if(x<=m) Update(u<<1,l,m,x,y,op);
	if(y> m) Update(u<<1|1,m+1,r,x,y,op);
	Up(u);
}
int QSum(int u,int l,int r,int x,int y) {
	if(x<=l&&r<=y) {
		if(C[u]==1) return r-l+1;
		if(C[u]==0) return 0;
	}Down(u);
	int m=l+r>>1,ret=0;
	if(x<=m) ret+=QSum(u<<1,l,m,x,y);
	if(y> m) ret+=QSum(u<<1|1,m+1,r,x,y);
	Up(u); return ret;
}
void QC(int u,int l,int r,int x,int y){
	if(x<=l&&r<=y) {
		if(~C[u]) {
			if(pre==1&&C[u]==1) ans+=r-l+1;
			else if(pre==0&&C[u]==1) ans=r-l+1;
			else if(C[u]==0) ans=0;
			best<ans?best=ans:1; pre=C[u];
			return;
		}
		if(l==r) return;
	}Down(u);
	int m=l+r>>1;
	if(x<=m) QC(u<<1,l,m,x,y);
	if(y> m) QC(u<<1|1,m+1,r,x,y);
	Up(u);
}
int main() {
	int op,x,y,i;
	for(n=geti(),m=geti(),i=0;i<n;++i) Update(1,0,n-1,i,i,geti());
	while(m--) {
		op=geti(),x=geti(),y=geti();
		if(op<3) Update(1,0,n-1,x,y,op);
		else if(op==3) printf("%d\n",QSum(1,0,n-1,x,y));
		else {
			pre=1,ans=best=0;
			QC(1,0,n-1,x,y); printf("%d\n",best);
		}
	}return 0;
}
