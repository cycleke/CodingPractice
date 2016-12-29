#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

int n,m;
int map[100];

const int base = 10000,maxn = 80;

struct Bign
{
	int c[maxn],len,sign;
	Bign(){memset(c,0,sizeof(c)),len = 1,sign = 0;}
	void Zero()
	{
		while(len > 1 && c[len] == 0)len--;
		if(len == 1 && c[len] == 0)sign = 0;
	}
	void Print()const
	{
		if(sign)printf("-");
		printf("%d",c[len]);
		for(int i = len - 1;i >= 1;i--)printf("%04d",c[i]);
		printf("\n");
	}
	void Write(char *s)
	{
		int k = 1,l = strlen(s);
		for(int i = l - 1;i >= 0;i--)
		{
			c[len] += (s[i] - '0') * k;
			k *= 10;
			if(k == base)
			{
				k = 1;
				len++;
			}
		}
	}
	Bign operator = (const int& a)
	{
		char s[100];
		sprintf(s,"%d",a);
		Write(s);
		return *this;//this只能用于成员函数，表示当前对象的地址
	}
	bool operator < (const Bign &a)const
	{
		if(len != a.len)return len < a.len;
		for(int i = len;i >= 1;i--)
		{
			if(c[i] != a.c[i])return c[i] < a.c[i];
		}
		return 0;
	}
	Bign operator + (const Bign &a)const
	{
		Bign r;
		r.len = max(len,a.len) + 1;
		for(int i = 1;i <= r.len;i++)
		{
			r.c[i] += c[i] + a.c[i];
			r.c[i + 1] += r.c[i] / base;
			r.c[i] %= base;
		}
		r.Zero();
		return r;
	}
	Bign operator + (const int &a)const
	{
		Bign b;b = a;
		return *this + b;
	}
	Bign operator - (const Bign &a)const
	{
		Bign b,c;// b - c
		b = *this;
		c = a;
		if(b < c)
		{
			swap(b,c);
			b.sign = 1;
		}
		for(int i = 1;i <= b.len;i++)
		{
			b.c[i] -= c.c[i];
			if(b.c[i] < 0)
			{
				b.c[i] += base;
				b.c[i + 1]--;
			}
		}
		b.Zero();
		return b;
	}
	Bign operator - (const int &a)const
	{
		Bign b;b = a;
		return *this - b;
	}
	Bign operator * (const Bign &a)const
	{
		Bign r;
		r.len = len + a.len + 2;
		for(int i = 1;i <= len;i++)
		{
			for(int j = 1;j <= a.len;j++)
			{
				r.c[i + j - 1] += c[i] * a.c[j];
			}
		}
		for(int i = 1;i <= r.len;i++)
		{
			r.c[i + 1] += r.c[i] / base;
			r.c[i] %= base;
		}
		r.Zero();
		return r;
	}
	Bign operator * (const int &a)const
	{
		Bign b;b = a;
		return *this * b;
	}
	Bign Pow(int n)const{
		Bign b = *this;
		Bign ans;
		ans = 1;
		while(n){
			if(n&1) ans = ans * b;
			b = b * b;
			n>>=1;
		}
		return ans;
	}
};
Bign f[100][100];
Bign maxx;
Bign zero;
int main()
{
	scanf("%d%d",&n,&m);
	Bign b;
	Bign ans;
	zero = ans = 0;
	b = 2;
	for(int p = 0;p < n;++p)
	{
		maxx = zero;
		memset(map,0,sizeof(map));
		for(int i = 0;i < 100;++i)
		for(int j = 0;j < 100;++j)
		f[i][j] = 0;
		for(int i = 1;i <= m;++i)
		scanf("%d",&map[i]);
		for(int j = 1;j <= m;++j)
		{
			for(int i = j;i >= 1;--i)
			{
				f[i][j] = max(f[i+1][j]+(b.Pow(m-(j-i)))*map[i],
						  f[i][j-1]+(b.Pow(m-(j-i)))*map[j]);
				if(maxx < f[i][j]) maxx = f[i][j];
			}
		}
		ans=ans + maxx;
	}
	ans.Print();
	return 0;
}
