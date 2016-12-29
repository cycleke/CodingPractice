#include <cstdio>
#include <cstring>
#include<cmath>
#include <algorithm>
#include <iostream>
#include<ctime>
using namespace std;
#define LL long long
#define ret0 return 0
const int base = 100000000;
const int maxn = 2000;
const double PI = acos(-1.0);
struct Bign
{
	LL c[maxn];
	int len,sign;
	//初始化 
	Bign(){memset(c,0,sizeof(c)),len = 1,sign = 0;}
	//高位清零
	void Zero()
	{
		while(len > 1 && c[len] == 0)len--;
		if(len == 1 && c[len] == 0)sign = 0;		
	} 
	//压位读入 
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
	void Read()
	{
		char s[maxn] = {0};
		scanf("%s",s);
		Write(s);
	}
	//输出
	void Print()
	{
		if(sign)printf("-");
		printf("%lld",c[len]);
		for(int i = len - 1;i >= 1;i--)printf("%04lld",c[i]);
		printf("\n");
	} 
	//重载 = 运算符，将低精赋值给高精 
	Bign operator = (LL a)
	{
		char s[100];
		sprintf(s,"%lld",a);
		Write(s);
		return *this;//this只能用于成员函数，表示当前对象的地址 
	} 
	//重载 < 运算符
	bool operator < (const Bign &a)const
	{
		if(len != a.len)return len < a.len;
		for(int i = len;i >= 1;i--)
		{
			if(c[i] != a.c[i])return c[i] < a.c[i];
		}
		return 0;
	}
	bool operator > (const Bign &a)const
	{
		return a < *this;
	}
	bool operator <= (const Bign &a)const
	{
		return !(a < *this);
	}
	bool operator >= (const Bign &a)const
	{
		return !(*this < a);
	}
	bool operator != (const Bign &a)const
	{
		return a < *this || *this < a;
	}
	bool operator == (const Bign &a)const
	{
		return !(a < *this) && !(*this < a);
	}
	bool operator == (const LL &a)const
	{
		Bign b;b = a;
		return *this == b;
	}
	//重载 + 运算符
	Bign operator + (const Bign &a)
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
	Bign operator + (const LL &a)
	{
		Bign b;b = a;
		return *this + b;
	}
	//重载 - 运算符
	Bign operator - (const Bign &a)
	{
		Bign b,c;// b - c
		b = *this;
		c = a;
		if(c > b)
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
	Bign operator - (const LL &a)
	{
		Bign b;b = a;
		return *this - b;
	}
	//重载 * 运算符 
	Bign operator * (const Bign &a)
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
	Bign operator * (const LL &a)
	{
		Bign b;b = a;
		return *this * b;
	}
	//重载 / 运算符 
	Bign operator / (const Bign &b)
	{
		Bign r,t,a;
		a = b;
		//if(a == 0)return r;
		r.len = len;
		for(int i = len;i >= 1;i--)
		{
			t = t * base + c[i];
			int div,ll = 0,rr = base;
			while(ll <= rr)
			{
				int mid = (ll + rr) / 2;
				Bign k = a * mid;
				if(k > t)rr = mid - 1;
				else
				{
					ll = mid + 1;	
					div = mid; 
				} 
			}
			r.c[i] = div;
			t = t - a * div;
		}
		r.Zero();
		return r; 
	}
	Bign operator / (const LL &a)
	{
		Bign b;b = a;
		return *this / b;
	}
	//重载 % 运算符
	Bign operator % (const Bign &a)
	{
		return *this - *this / a * a;
	}
	Bign operator % (const LL &a)
	{
		Bign b;b = a;
		return *this % b;
	}
};

int main()
{
	Bign a,b;
	LL n;
	scanf("%lld",&n);
	if(n < 4){
		putchar('1');ret0;
	}
	double t = clock() / CLOCKS_PER_SEC;
	n -= 4;
	a = b = 1;
	LL i = 1,j = n + PI,last;
	while(i <= (LL)((n+PI)/PI)){
		last = j;
		j = n + PI - i * PI;
		for(LL k = last - 1;k > j;--k){
			b = b * (k+1);
			b = b / (i+k);
		}
		b = b * (j + 1);
		b = b / i;
		++i;
		a = a + b;
	}
	a.Print();
	double t1 = clock() / CLOCKS_PER_SEC;
	cout << t1 - t;
	return 0;
}
