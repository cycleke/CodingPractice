#include <cstdio>
#include <cstring>

char s[20];
int cnt[10];

int main() {
	
	int n; scanf("%d", &n);
	scanf("%s", s);
	for (int i = 0; i < n; ++i) {
		if (s[i]=='4') cnt[2]+=2,cnt[3]+=1;
		else if (s[i]=='6') cnt[3]+=1,cnt[5]+=1;
		else if (s[i]=='8') cnt[2]+=3,cnt[7]+=1;
		else if (s[i]=='9') cnt[2]+=1,cnt[3]+=2,cnt[7]+=1;
		else ++cnt[s[i]-'0'];
	}
	for (int i = 7; i > 1; --i)
	  while (cnt[i]--) putchar('0'+i);

	return 0;
}
