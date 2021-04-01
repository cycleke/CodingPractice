#include<cstdio>
#include<cstring>
#define lowbit(u) (u&-u)
#define maxn 100010
#define LL long long
#define cint const int&
inline void read(int& x){
	x = 0;
	c = getchar();
	while(c<'0'||c>'9') c = getchar();
	while(c>='0'&&c<='9') c = getchar(),x = x * 10 + c - '0';
}

int sum(LL x){
	int cnt;
	while(x){
		if(x&1) ++cnt;
		x>>=1;
	}
	return cnt;
}

LL A[2000];l
int s(0),x,t(0);

void clr(cint a,cint b,cint k){
	int x = a/64,y = b/64;
	if(y-x>1){
		for(int i = x+1;i<y;++i) A[i] = k;
	}
	if(k){
		if(a%64) A[x] = A[x] | ((LL)1<<(63 - a%64));
		else A[x] = -1;
		if(b%64) A[y] = A[y] | ((LL)1<<(63 - b%64));
		else A[y] = -1;
	}else{
		if(a%64) A[x] = A[x] & (~(((LL)1<<(63 - a%64))-1));
		else A[x] = 0;
		if(b%64) A[y] = A[y] & (~(((LL)1<<(63 - b%64))-1));
		else A[y] = 0;
	}
}

void fan(cint a,cint b){
	int x = a/64,y = b/64;
	if(y-x>1){
		for(int i = x+1;i<y;++i) A[i] = ~A[i];
	}
		if(a%64) {}
		else A[x] = ~A[x];
		if(b%64) {}
		else A[y] = ~A[y];
}

int main(){
	int n,q;
	read(n);read(q);
	for(int i = 0;i < n;++i)｛
		read(x);
		A[t]<<=1;
		A[t] = A[t] & x;
		++s;
		if(s==64) s = 0,++t;
	}
	int k,a,b;
	while(q--)｛
		read(k);read(a);read(b);
		switch (k){
			case 0:clr(a,b,0);break;
			case 1:clr(a,b,-1);break;
			case 2:fan(a,b);break;
			case 3:s(a,b);break;
			default:cs(a,b);break;
	}
	return 0;
}
