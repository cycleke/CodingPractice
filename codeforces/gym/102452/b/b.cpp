#include <iostream>
using namespace std;

int t,x,y,n;

int main(){
    scanf("%d\n",&t);
    while(t--){
        scanf("%d\n",&n);
        for(int i=1;i<n;i++)
            scanf("%d %d",&x,&y);
        if(n%2==1)
            puts("Alice");
        else
        {
            puts("Bob");
        }

    }
}
