#include <stdio.h>
#include <string.h>
#define L(u) (u<<1)
#define R(u) (u<<1|1)
#define LL long long
const int M = 100005;

struct Node
{
    int l,r;
    LL add,sum;
}node[M<<2];

LL A[M];
void Pushup(int u)
{
    node[u].sum = node[L(u)].sum + node[R(u)].sum;
    return ;
}
void Pushdown (int u)
{
    node[L(u)].add += node[u].add;
    node[L(u)].sum += (node[L(u)].r - node[L(u)].l+1)*node[u].add;

    node[R(u)].add += node[u].add;
    node[R(u)].sum += (node[R(u)].r - node[R(u)].l+1)*node[u].add;

    node[u].add = 0;
}
void Build (int u,int left,int right)
{
    node[u].l = left,node[u].r = right;
    node[u].add = 0;
    if (node[u].l == node[u].r)
    {
        node[u].sum = A[left];
        return ;
    }
    int mid = (node[u].l + node[u].r)>>1;
    Build (L(u),left,mid);
    Build (R(u),mid+1,right);
    Pushup(u);
}


void Update(int u,int left,int right,LL val)
{
    if (left<=node[u].l&&node[u].r <= right)
    {
        node[u].add += val;
        node[u].sum += (node[u].r - node[u].l+1)*val;
        return ;
    }
    node[u].sum += (right - left + 1)*val; /
    if (node[u].add) Pushdown(u);          
    int mid = (node[u].l + node[u].r)>>1;
    if (right <= mid) Update(L(u),left,right,val);
    else if (left > mid) Update(R(u),left,right,val);
    else {
        Update(L(u),left,mid,val);
        Update(R(u),mid+1,right,val);
    }
}

LL Query(int u,int left,int right)
{
    if (left <= node[u].l&&node[u].r <= right)
        return node[u].sum;
    if (node[u].add) Pushdown(u);
    int mid = (node[u].l + node[u].r)>>1;
    if (right <= mid) return Query(L(u),left,right);
    else if (left > mid) return Query(R(u),left,right);
    else return (Query(L(u),left,mid) + Query(R(u),mid+1,right));
    //Pushup(u);
}
int main ()
{
    int n,m,i,a,b;
    LL c;
    char ch[3];
    while (~scanf ("%d %d",&n,&m))
    {
        for (i = 1;i <= n;i ++)
            scanf ("%lld",&A[i]);
        Build(1,1,n);
        while (m --)
        {
            scanf ("%s",ch);
            if (ch[0] == 'Q')
            {
                scanf ("%d%d",&a,&b);
                printf ("%lld\n",Query(1,a,b));
            }
           else
            {
                scanf ("%d %d %lld",&a,&b,&c);
                Update(1,a,b,c);
            }
        }

    }
    return 0;
}

