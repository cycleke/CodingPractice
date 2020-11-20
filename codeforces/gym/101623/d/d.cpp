// by sineMora
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include<vector>
#include<map>
#define fo(i, l, r) for (int i = l; i <= r; i++)
#define fd(i, l, r) for (int i = r; i >= l; i--)
#define mem(x) memset(x, 0, sizeof(x))
#define ll long long
using namespace std;
const int maxn = 300050;
ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (!(ch >= '0' && ch <= '9'))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    };
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    };
    return x * f;
}
int n,m;
map<string,int> mp;
map<string,string> tran;
int dui[105],cuo[105];
string s[5],a[25];
char sc[5][30];
bool flag=true,correct=true;
int main()
{
    n=read();
    fo(i,1,n){
        scanf("%s",sc[1]);
        a[i]=s[1]=sc[1];
        mp[s[1]]=i;
    }
    m=read();
    fo(i,1,m){
        scanf("%s%s%s",sc[1],sc[2],sc[3]);
        s[1]=sc[1];s[2]=sc[2];
        if(mp.count(s[1])==0)continue;
        if(sc[3][0]=='c'){
            dui[mp[s[1]]]++;
        }else{
            correct=false;
            cuo[mp[s[1]]]++;
        }
        if(!flag)continue;
        if(tran.count(s[1])){
            flag=false;
        }else{
            tran[s[1]]=s[2];
        }
    }
    if(flag){
        fo(i,1,n){
            cout<<tran[a[i]];
            if(i<n)putchar(' ');
        }
        if(correct) cout<<"\ncorrect";
        else cout<<"\nincorrect";
    }else{
        ll ans1=1,ans2=1,now;
        fo(i,1,n){
            now=mp[a[i]];
            ans1*=dui[now];
            ans2*=(dui[now]+cuo[now]);
        }
        ans2 -= ans1;
        cout<<ans1<<" "<<"correct\n"<<ans2<<" "<<"incorrect";
    }

    return 0;
}

