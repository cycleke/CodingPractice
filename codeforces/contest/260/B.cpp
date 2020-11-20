#include <cstdio>
#include <cstring>
char s[100010];

#define isnum(a) (a>='0'&&a<='9')
int cnt[40][40][2100];
const int k[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

int main() {
	scanf("%s", s);
	int len = strlen(s);
	int mx = 0, d, m, y;
	for (int i = 0; i <= len - 10; ++i) {
		bool ok = isnum(s[i])&&isnum(s[i+1])&&isnum(s[i+3])&&isnum(s[i+4])&&isnum(s[i+6])&&isnum(s[i+7])&&isnum(s[i+8])&&isnum(s[i+9]);
		ok &= (s[i+2]=='-')&&(s[i+5]=='-');
		if (!ok) continue;
		int dd, mm, yyyy;
		dd = (s[i]-'0')*10 + s[i+1]-'0';
		mm = (s[i+3]-'0')*10 + s[i+4]-'0';
		yyyy = (s[i+6]-'0')*1000+(s[i+7]-'0')*100+(s[i+8]-'0')*10+s[i+9]-'0';
		if (dd > 31 || dd < 1 || mm > 12 || mm < 1 || yyyy < 2013 || yyyy > 2015) continue;
		if (dd > k[mm]) continue;
		if ((++cnt[dd][mm][yyyy]) > mx) {
			mx = cnt[dd][mm][yyyy];
			d = dd, m = mm, y = yyyy;
		}
	}
	printf("%02d-%02d-%d",d,m,y);
	return 0;
}
