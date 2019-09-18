// by sineMora
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#define fo(i, l, r) for (int i = l; i <= r; i++)
#define fd(i, l, r) for (int i = r; i >= l; i--)
#define ll long long
using namespace std;
const int maxn = 300050;
const ll mod = 1e9 + 7;
const double eps = 1e-12;
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
struct dat{
    int p;
    double num;
    double v;
    friend bool operator < (dat a,dat b){
        if(fabs(a.v-b.v)<eps){
            return a.num < b.num;
        }else{
            return a.v < b.v;
        }
    }
}now;
int n,m;
double v[maxn];
double getv(){
    double sum = 0;
    fo(i,1,n){
        sum += v[i];
    }
    sum /= (double)n;
    double ret = 0;
    fo(i,1,n){
        ret += (v[i]-sum)*(v[i]-sum);
    }
    ret /= (double)n;
    return ret;
}
priority_queue<dat> q;
int main(){
    int T=read(),tt=0;
    while(T--){
        n=read();m=read();
        fo(i,1,n)v[i]=read();
        double avg = 0;
        fo(i,1,n) avg += v[i];
        avg /= m;
        fo(i,1,n){
            now.p=i;
            now.num=1;
            now.v=now.num*(v[i]/now.num-avg)*(v[i]/now.num-avg)-(now.num+1)*(v[i]/(now.num+1)-avg)*(v[i]/(now.num+1)-avg);
            q.push(now);
        }
        double nowvi;
        fo(i,1,m-n){
            now = q.top();
            q.pop();
            now.num++;
            nowvi = v[now.p];
            now.v=now.num*(nowvi/now.num-avg)*(nowvi/now.num-avg)-(now.num+1)*(nowvi/(now.num+1)-avg)*(nowvi/(now.num+1)-avg); 
            q.push(now);
        }
        double ans = 0;
        while(!q.empty()){
            now = q.top();
            q.pop();
            nowvi = v[now.p];
            ans += now.num*(nowvi/now.num-avg)*(nowvi/now.num-avg);
        }
        ans /= (double)m;
        printf("Case #%d: %.12lf\n",++tt,ans);
    }
    return 0;
}
