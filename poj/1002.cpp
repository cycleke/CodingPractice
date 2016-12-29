#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

string ss[100001];

char* input()
{
	char a;
	char s[10];
	int i = 0;
	while(i <= 7)
	{
		a = getchar();
		if(a=='-' || a == ' ') continue;
		if(a>='0' && a <= '9')s[i]=a;
		else
		{
			if(a >= 'A' && a <= 'C') s[i]='2';
			else if(a >= 'D' && a <= 'F') s[i]='3';
			else if(a >= 'G' && a <= 'I') s[i]='4';
			else if(a >= 'J' && a <= 'L') s[i]='5';
			else if(a >= 'M' && a <= 'O') s[i]='6';
			else if(a >= 'P' && a <= 'S') s[i]='7';
			else if(a >= 'T' && a <= 'V') s[i]='8';
			else if(a >= 'W' && a <= 'Y') s[i]='9';
		}
		++i;
	}
	return s;
}

int main()
{
	int m;
	scanf("%d",&m);
	for(int i = 0;i < m;++i)
	{
		ss[i] = (string)input();
	}
	sort(ss,ss+m);
	int cnt = 0;
	bool ok = false;
	string a = ss[0];
	for(int i = 0;i < m;++i)
	{
		if(ss[i] == a) ++cnt;
		else {
			if(cnt > 1)
			{
				cout << a << ' ' << cnt << endl;
				ok = true;
			}
			a = ss[i]; cnt = 1;
		}
	}
	if(!ok) cout << "No duplicates. ";
	return 0;
}
