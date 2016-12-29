#include <cstdio>
#define SIZE 169
#define ba 10000
const int p[SIZE] = {
	0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,
    79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,
    193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,
    313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,
    443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,
    587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,
    719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,
    859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997
};
inline int geti() {
    register int a; register char c,f=0;
    while(c=getchar(),c<'0')f|=c=='-';a=c-'0';
    while(c=getchar(),'-'<c)a=(a<<3)+(a<<1)+c-'0';
    return f?-a:a;
}
int e[SIZE],Ans[3000];
inline void Fac(const int &n,const bool&k) {
    register int i,j;
    for(i=1;i^SIZE;++i)
        for(j=p[i];j<=n;j*=p[i])
            k?(e[i]+=n/j):(e[i]-=n/j);
}
int main() {
    register int n=geti(),i,len=n-2,m=0,t;
    for(i=0;i<n;++i) {
        t=geti();
        if(!t||len<t-1) return puts("0"),0;
        if(t<0) {++m;continue;}--t;
        Fac(len,1); Fac(t,0); Fac(len-t,0);
        len-=t;
    }
    if(len) {
        for(i=1;(i^SIZE)&&1<m;++i)
            while(!(m%p[i])) m/=p[i],e[i]+=len;
    }
    Ans[1]=len=1;
    for(i=1;i^SIZE;++i)
        while(e[i]--) {
            for(t=1;t<=len;++t) Ans[t]*=p[i];
            for(t=1;t<=len;++t) if(Ans[t]>=ba) Ans[t+1]+=Ans[t]/ba,Ans[t]%=ba;
            while(Ans[len+1]) {
                if(Ans[len]>=ba) Ans[len+1]+=Ans[len]/ba,Ans[len]%=ba;
                ++len;
            }
        }
    for(printf("%d",Ans[len]),i=len-1;i;--i) printf("%04d",Ans[i]);
    return 0;
}
