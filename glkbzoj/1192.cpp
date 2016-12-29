#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define LL long long

LL f(const  LL& x)
{
    LL ans = 0,base = 1,remain = x;
    while(base < remain)
    {
        remain -= base;
        base <<= 1;
        ++ans;
    }
    return ans + 1;
}

int main()
{
    LL m;
    scanf("%lld",&m);
    std::cout << f(m);
}
