#include <set>
#include <cstdio>
#include <cstring>
using namespace std;
set<int>s;
set<int>::iterator it;
int ans[550];
int main() {
	int i,j,n,a,t,res; char op[3];
	for(scanf("%d",&n),memset(ans,127,sizeof ans),i=0;i<n;++i) {
		scanf("%s%d",op,&a);
		if(*op=='A') {
			for(j=1;j<550;++j) (t=a%j)<ans[j]?ans[j]=t:1;
			s.insert(a);
		} else 
			if(a<550) printf("%d\n",ans[a]);
			else { for(j=0,res=0x7f7f7f7f;j<300001;j+=a) {
					it=s.lower_bound(j);
					if(it==s.end()) continue;
					t=*it%a,t<res?res=t:1;
				}
				printf("%d\n",res);
			}
	}
	return 0;
}
