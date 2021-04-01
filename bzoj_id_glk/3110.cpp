#include <cstdio>
#include <iostream>

#define lch (u << 1)
#define rch (u << 1 | 1)

using namespace std;
typedef long long ll;
int ReadInt()
{
	ll x = 0;int sign = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') sign = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') {x = x*10 + ch-'0'; ch = getchar();}
	return x*sign;
}

const int maxn = 50000+5;
const int maxm = 360 * maxn;

int N, M;
int root[3*maxn]; // 外层线段树 

ll sum[maxm],lazy[maxm];
int lc[maxm],rc[maxm]; // 内层线段树 
int size;

void insert(int u, int l, int r, int L, int R)
{ // 内层线段树 
	if(l == L && r == R) 
	{
		sum[u] += r-l+1;
		lazy[u]++; return;
	}
	int mid = (l + r) >> 1;
	if(R <= mid) insert(lc[u] ? lc[u] : lc[u] = ++size, l, mid, L, R);
	else if(L > mid) insert(rc[u] ? rc[u] : rc[u] = ++size, mid+1, r, L, R);
	else
	{
		insert(lc[u] ? lc[u] : lc[u] = ++size, l, mid, L, mid);
		insert(rc[u] ? rc[u] : rc[u] = ++size, mid+1, r, mid+1, R);
	}
	sum[u] += R - L + 1;
}

void add(int u, int l, int r, int L, int R, int x)  
{ // 外层线段树
	insert(root[u] ? root[u] : root[u] = ++size, 1, N, L, R);
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(x <= mid) add(lch, l, mid, L, R, x);
	else add(rch, mid+1, r, L, R, x);
}

ll count(int u, int l, int r, int L, int R)
{ // 内层线段树 
	if(l == L && r == R) return sum[u];
	
	int mid = (l + r) >> 1;
	ll ans;
	
	if(R <= mid) ans = count(lc[u], l, mid, L, R);
	else if(L > mid) ans = count(rc[u], mid+1, r, L, R);
	else
	{
		ans = count(lc[u], l, mid, L, mid);
		ans += count(rc[u], mid+1, r, mid+1, R);
	} 
	ans += (R - L + 1) * lazy[u];
	return ans;
}

int query(int u, int l, int r, int L, int R,ll x)
{ // 外层线段树 
	if(l == r) return l;
	int mid = (l + r) >> 1;
	ll cnt = count(root[rch], 1, N, L, R);
	if(cnt >= x) return query(rch, mid+1, r, L, R, x);
	else return query(lch, l, mid, L, R, x - cnt);
}

int main()
{
	N = ReadInt(); M = ReadInt();
	int type, a, b, c;
	while(M--)
	{
		type = ReadInt(); a = ReadInt(); b = ReadInt();c = ReadInt();
		if(type == 1) add(1, 1, N, a, b, c);
		else printf("%d\n", query(1, 1, N, a, b, c));
	}
	return 0;
}
