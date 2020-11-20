#include <iostream>
using namespace std;
int co[6],p[55];
long long cnt[6];
int main() {
	long long res=0,t;
	int n,i,j;
	cin >> n;
	for(i=0;i<n;++i) cin>>p[i];
	for(i=0;i<5;++i) cin>>co[i];
	for(i=0;i<n;++i) {
		res+=p[i];
		for(j=4;~j;--j) {
			t=res/co[j];
			cnt[j]+=t;
			res-=co[j]*t;
		}
	}
	for(i=0;i<5;++i) cout << cnt[i] << "\n "[i<4];
	cout << res;
	return 0;
}
