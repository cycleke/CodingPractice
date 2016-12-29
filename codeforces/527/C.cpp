#include <bits/stdc++.h>
using namespace std;
set<int>H,V;
set<int>::iterator it1,it2,it3;
int cnth[200005],cntv[200005],w,h,n;

int main() {
	scanf("%d%d%d",&w,&h,&n);
	//H[0]=H[h]=V[0]=V[w]=1;
	H.insert(0); H.insert(h);
	V.insert(0); V.insert(w);
	cnth[h]=cntv[w]=1;
	char op[3]; int x,mh=h,mv=w;
	while(n--) {
		scanf("%s%d",op,&x);
		if(*op=='H') {
			H.insert(x);
			it1=it2=it3=H.find(x);
			--it1,++it3;
			--cnth[*it3-*it1];
			++cnth[*it3-*it2];
			++cnth[*it2-*it1];
		} else {
			V.insert(x);
			it1=it2=it3=V.find(x);
			--it1,++it3;
			--cntv[*it3-*it1];
			++cntv[*it3-*it2];
			++cntv[*it2-*it1];
		}
		while(!cnth[mh]) --mh;
		while(!cntv[mv]) --mv;
		cout << (long long) mh * mv << endl;
	}
	return 0;
}
