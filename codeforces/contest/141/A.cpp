#include <cstdio>
#include <cstring>
int cnt[30];
char a[105],b[105],c[105];
int main() {
	scanf("%s%s%s",a,b,c);
	for(int i=0;a[i];++i) --cnt[a[i]-'A'];
	for(int i=0;b[i];++i) --cnt[b[i]-'A'];
	for(int i=0;c[i];++i) ++cnt[c[i]-'A'];
	for(int i=0;i<26;++i) if(cnt[i]) return puts("NO"),0;
	return puts("YES"),0;
}
