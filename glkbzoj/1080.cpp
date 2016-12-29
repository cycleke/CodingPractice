#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct D {
	int a,i,j,t;
	D() {}
	D(int _a,int _i,int _j,int _t):a(_a),i(_i),j(_j),t(_t){}
};
//Input
int ina; char inc,inb[1<<16],*ins=inb,*ine=inb;
#define getc() ((ins==ine&&(ine=(ins=inb)+fread(inb,1,1<<16,stdin),ins==ine))?EOF:*ins++)
inline int geti() {
	while((inc=getc())<'0'||inc>'9'); ina=inc-'0';
	while((inc=getc())>='0'&&inc<='9') ina=(ina<<3)+(ina<<1)+inc-'0';
	return ina;
}
inline int getis(char s[]) {
	for(ina=1,inc=getc();inc!='\n'&&inc!='\r';++ina,inc=getc()) s[ina]=inc;
	s[ina]=0; return ina-1;
}
#define N 63
#define min(a,b) ((a)<(b)?(a):(b))
int n,m,len[N],ans,dp[N][N][N][3];
char str[N][N]; bool cmp[N][N][N];
queue<D>q;

int main() {
	int i,j,k,t,o;
	for(n=geti(),i=1;i<=n;++i) {
		len[i]=getis(str[i]);
		while(str[i][len[i]]==' ') str[i][len[i]--]=0;
		if(len[i]==0) return puts("0"),0;
	}
	for(i=1;i<=n;++i)
	  for(j=1;j<=n;++j)
		for(cmp[i][j][len[i]]=true,k=0;k<len[i];++k){
			t=min(len[i]-k,len[j]);
			for(o=1;o<=t;++o)
			  if(str[i][o+k]^str[j][o]) break;
			cmp[i][j][k]=o>t;
		}
	ans=0x3f3f3f3f;
	memset(dp,63,sizeof dp);
	for(i=1;i<=n;++i) {
		dp[i][0][0][2]=len[i];
		q.push(D(i,0,0,2));
	}
	while(!q.empty()) {
		D p=q.front(); q.pop();
		int _a,_i,_j,_t,res=dp[p.a][p.i][p.j][p.t];
		if(p.t==0) {
			if(p.i==p.j&&p.i==len[p.a]) {
				(res<ans)?ans=res:1;
				continue;
			}
			for(i=1;i<=n;++i)
			  if(_t=0,cmp[p.a][i][p.j]) {
				  if(len[i]+p.j>len[p.a]) {
					  _a=i,_i=len[p.a]-p.j,_j=p.i-p.j;
					  o=res+len[i]-(len[p.a]-p.j);
				  }else {
					  _a=p.a,_i=p.j+len[i],_j=p.i;
					  (_i<_j)?_i^=_j^=_i^=_j:1;
					  o=res;
				  }
				  (o<dp[_a][_i][_j][_t])?q.push(D(_a,_i,_j,_t)),dp[_a][_i][_j][_t]=o:1;
			  }
		} else if(p.t==1) {
			if(p.i==p.j&&p.i==len[p.a]) continue;
			for(i=1;i<=n;++i)
			  if(cmp[p.a][i][p.j]) {
				  if(p.j+len[i]>=len[p.a]) {
					  _a=i,_i=_j=len[p.a]-p.j,_t=2;
					  o=res+len[i]-_i;
				  }else {
					  _a=p.a,_i=p.i,_j=p.j+len[i],_t=1;
					  o=res;
				  }
				  (o<dp[_a][_i][_j][_t])?q.push(D(_a,_i,_j,_t)),dp[_a][_i][_j][_t]=o:1;
			  }
		} else if(p.t==2) {
			for(i=1;i<=n;++i) {
				if(!cmp[p.a][i][p.j]||(p.i==0&&i==p.a)) continue;
				if(p.j+len[i]>len[p.a]) {
					_a=i,_i=len[i],_j=len[p.a]-p.j,_t=1;
					o=res+len[i]-_j;
				}else {
					_a=p.a,_i=_j=p.i+len[i],_t=2;
					o=res;
				}
				(o<dp[_a][_i][_j][_t])?q.push(D(_a,_i,_j,_t)),dp[_a][_i][_j][_t]=o:1;

				for(j=1;j<=n;++j) {
					if(!cmp[p.a][j][p.j]||i==j||!cmp[i][j][0]) continue;
					int si=i,sj=j;
					if(len[si]<len[sj]||(len[si]==len[sj]&&sj==p.a)) si^=sj^=si^=sj;
					if(p.i+len[si]>len[p.a]) {
						if(p.j+len[sj]>len[p.a]) {
							_a=si,_i=len[sj],_j=len[p.a]-p.i;
							o=res+len[si]-_j,_t=0;
						}else {
							_a=si,_i=len[p.a]-p.i,_j=len[sj];
							o=res+len[si]-_i; (p.a==sj&&p.i==0)?_t=2:_t=0;
						}
					}else {
						_a=p.a,_i=p.i+len[si],_j=p.i+len[sj],_t=0;
						o=res; if(p.i==0&&si==p.a) (_j<len[p.a])?_t=1:_a=sj,_t=2,_i=_j=len[sj];
					}
					(o<dp[_a][_i][_j][_t])?q.push(D(_a,_i,_j,_t)),dp[_a][_i][_j][_t]=o:1;
				}

			}
		}
	}
	return printf("%d\n",(ans^0x3f3f3f3f)?ans:-1),0;
}
