#include <cstdio>
#include <algorithm>
struct D{
	int a,id;
	bool operator < (const D& x) const {
		return a+id < x.a+x.id;
	}
	D(int _a=0,int _id=0): a(_a),id(_id){}
}p[200005];

int main() {
	int n,i,j,v; scanf("%d",&n);
	for(i=1;i<=n;++i) {
		scanf("%d",&v);
		p[i]=D(v,i);
	}
	std::sort(p+1,p+n+1);
	for(i=1;i<n;++i)
	  if(p[i].a+p[i].id==p[i+1].a+p[i+1].id) return puts(":("), 0;
	for(i=1;i<=n;++i) {
		j=p[i].a-(i-p[i].id);
		if(j<0) return puts(":("), 0;
	}
	for(i=1;i<=n;++i)
	  printf("%d ",p[i].a-(i-p[i].id));
	return 0;
}
