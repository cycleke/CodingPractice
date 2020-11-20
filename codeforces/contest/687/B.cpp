#include <cstdio>
inline long long gcd(long long a,long long b) {
	for(long long t;b;t=a%b,a=b,b=t);
	return a;
}
int main() {
	int n,k,c; long long lcm=1,t;
	for(scanf("%d%d",&n,&k);n;--n) {
		scanf("%d",&c);
		t=gcd(c,lcm);
		lcm=c/t*lcm;
		lcm%=k;
	}
	return puts(lcm?"No":"Yes"),0;
}
