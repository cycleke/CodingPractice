#include <cstdio>  
#include <iostream>  
#include <algorithm>  
#include <cstdlib>  
#include <ctime>  
#include <queue>
using namespace std;  
const int Maxn = 1000011;  
struct node {  
    int s,v,r,cnt; int ch[2];  
}N[Maxn];

int totN, root;  
const int INF = 1 << 30;  
void up(int u) {  
    int ls = N[u].ch[0], rs = N[u].ch[1];  
    N[u].s = N[u].cnt + N[ls].s + N[rs].s;
}  

void Rot(int &u, int d) {  
    int t = N[u].ch[d^1];  N[u].ch[d^1] = N[t].ch[d];  
    N[t].ch[d] = u;  
    up(u); up(t); u = t;  
}  

void Ins(int &u,int val) {  
    if (!u) {  
        u = ++totN; N[u].v = val; N[u].cnt = 1; N[u].s = 1; N[u].r = rand();  
    } else {  
        ++N[u].s; int k = val < N[u].v ? 0 : 1;  
        if (N[u].v == val) { ++N[u].cnt; return; }  
        Ins(N[u].ch[k], val);  
        if (N[N[u].ch[k]].r > N[u].r) Rot(u, k ^ 1);  
    }  
}  

void Del(int &u,int val) {  
    if (!u) return;  
    if (N[u].v == val) {  
        if (N[u].cnt > 1) { --N[u].cnt; --N[u].s; return; }  
        if (!N[u].ch[0] || !N[u].ch[1]) u = N[u].ch[0] + N[u].ch[1];  
        else {  
            int k = N[N[u].ch[0]].r > N[N[u].ch[1]].r;  
            Rot(u,k); Del(u, val);   
        }  
    } else --N[u].s, Del(N[u].ch[val < N[u].v ? 0 : 1],val);  
}  
  
int Kth(int u,int k) {  
    if (!u) return 0;  
    if (k <= N[N[u].ch[0]].s) return Kth(N[u].ch[0],k);  
    if (k > N[N[u].ch[0]].s + N[u].cnt)   
        return Kth(N[u].ch[1],k - N[N[u].ch[0]].s - N[u].cnt);  
    return N[u].v;  
}   

queue<int>q;

int main() { 
    int n, op, x, si = 0;  
    scanf("%d", &n);  
    srand(time(NULL));  
    while (n--) {  
        scanf("%d", &op);
		if (op == 1) {
			scanf("%d", &x); ++si;
			q.push(x); Ins(root,x);
		} else if (op == 2) {
			Del(root, q.front()); q.pop(); --si;
		} else {
			printf("%d\n", Kth(root, (si >> 1) + 1));
		}
    }  
    return 0;  
}  
