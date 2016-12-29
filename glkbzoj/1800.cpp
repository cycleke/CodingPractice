#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define LL long long

int N;
int dis[25];

int main()
{
    cin >> N;
    int a,C = 0;
    for(int i = 1;i <= N;++i)
    {
         scanf("%d",&a);
         dis[i+1] = dis[i] + a;
         C += a;
    }
    int c = C  >> 1;
    int cnt = 0;
    for(int i = 1;i <= N;++i)
    {
        for(int j = i+1;j <= N;++j)
        if(dis[j] - dis[i] < c) continue;
        else if(dis[j] - dis[i] == c){
            ++cnt;
            break;
        }
        else break;
    }
    //cout << cnt << endl;
    cout << (cnt * (cnt - 1) >> 1);
   return 0;
}
