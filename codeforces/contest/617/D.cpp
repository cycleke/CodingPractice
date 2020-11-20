#include <cstdio>
#define max(a,b) (a<b?b:a)
#define min(a,b) (a<b?a:b)
int main() {
	int x1,x2,x3,y1,y2,y3;
	scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3);
	if(x1==x2&&x2==x3) puts("1");
	else if(y1==y2&&y2==y3) puts("1");
	else if(y1==y2&&(x3>=max(x1,x2)||x3<=min(x1,x2))) puts("2");
	else if(y1==y3&&(x2>=max(x1,x3)||x2<=min(x1,x3))) puts("2");
	else if(y2==y3&&(x1>=max(x2,x3)||x1<=min(x2,x3))) puts("2");
	else if(x1==x2&&(y3>=max(y1,y2)||y3<=min(y1,y2))) puts("2");
	else if(x1==x3&&(y2>=max(y1,y3)||y2<=min(y1,y3))) puts("2");
	else if(x2==x3&&(y1>=max(y2,y3)||y1<=min(y2,y3))) puts("2");
	else puts("3");
	return 0;
}
