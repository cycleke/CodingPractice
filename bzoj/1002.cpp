#include <cstdio>
int a[20],b[20],c[20],n;
#define ba 1000000
int main() {
    scanf("%d",&n);
    if(n<3) return puts(n<2?"1":"5"),0;
    register int i,la=1,lb=1,lc=1;
    *a=1,*b=5; n-=2;
    while(n--) {
        //c=3*b-a+2
        for(i=0;i<lb;++i) c[i]=b[i]*3;
        for(i=0;i<lb;++i) c[i+1]+=c[i]/ba,c[i]%=ba;
        for(lc=lb;c[lc];++lc); *c+=2;
        for(i=0;i<lc;++i) {
            c[i]-=a[i];
            if(c[i]<0) --c[i+1],c[i]+=ba;
        }
        while(!c[lc-1]) --lc;
        for(i=0;i<lb;++i)a[i]=b[i];la=lb;
        for(i=0;i<lc;++i)b[i]=c[i];lb=lc;
    }
    printf("%d",c[lc-1]);
    for(i=lc-2;~i;--i) printf("%06d",c[i]);
    return 0;
}
