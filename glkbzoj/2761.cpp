#include<cstdio>
#include<cstring>
#include<iostream>
#include<set>
using namespace std;

void work()
{
    int n;
    scanf("%d",&n);
    set<int>s;
    int a;
    bool ok = false;
    while(n--)
    {
        scanf("%d",&a);
        if(s.find(a) != s.end()) continue;
        s.insert(a);
        if(ok) printf(" ");
        else ok = 1;
        printf("%d",a);
    }
}


int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        work();
        if(T) puts("");
    }
    return 0;
}
