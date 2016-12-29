#include<cstdio>  
int n,k,tot;  
int main()  
{  
    scanf("%d",&tot);  
    for (int i=1;i<=tot;++i)  
    {  
        scanf("%d%d",&n,&k);  
        if ((n&k)==k) printf("%d\n",1);  
        else printf("%d\n",0);  
    }  
    return 0;  
}
