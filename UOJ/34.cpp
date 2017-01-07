#include<cstdio>
#include<iostream>
#include<cmath>
#include<memory.h>
#define N 400010
using namespace std;
const double pi=acos(-1);
struct complex{
    double x,i;
    complex(){}
    complex(double x,double i):x(x),i(i){}
    complex operator+(complex a) {return complex(x+a.x,i+a.i);}
    complex operator-(complex a) {return complex(x-a.x,i-a.i);}
    complex operator*(complex a) {return complex(x*a.x-i*a.i,x*a.i+i*a.x);}
}a[N],b[N];
int n,m,i,nn,len,rev[N];
void fft(complex *a,int n,int t)
{
    for (int i=0;i<n;i++) if (i<rev[i]) swap(a[i],a[rev[i]]);
    for (int j=1;j<n;j<<=1)
    {
        complex wn(cos(2*pi/(j<<1)),t*sin(2*pi/(j<<1)));
        for (int i=0;i<n;i+=(j<<1))
        {
            complex w(1,0),t0,t1;
            for (int k=0;k<j;k++,w=w*wn) t0=a[i+k],t1=w*a[i+j+k],a[i+k]=t0+t1,a[i+j+k]=t0-t1;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    memset(a,0,sizeof(a));memset(b,0,sizeof(b));
    for (i=0;i<=n;i++) scanf("%lf",&a[i].x);
    for (i=0;i<=m;i++) scanf("%lf",&b[i].x);
    nn=1;len=0;while (nn<=n+m) nn<<=1,len++;
    rev[0]=0;
    for (i=1;i<nn;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
    fft(a,nn,1);fft(b,nn,1);
    for (i=0;i<=nn;i++) a[i]=a[i]*b[i];
    fft(a,nn,-1);
    for (i=0;i<=n+m;i++) printf("%d ",(int)(a[i].x/nn+0.5));
}
