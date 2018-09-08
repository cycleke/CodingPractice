#include <cstdio>
#include <cstdlib>

int GetLength(int x) {
  int length = 0;
  while (x > 0) {
    length++;
    x /= 10;
  }
  return length;
}
int ModPow(int x,int n,int mod) {
  if(n == 1) return x % mod;
  x %= mod;
  int ret=1;
  while (n > 0) {
    if(n & 1) ret = (long long)ret * x % mod;
    x = (long long)x * x % mod;
    n >>= 1;
  }
  return ret;
}
bool Check(int a,int n,int x,int t) {
  int ret = ModPow(a,x,n);
  int last = ret;
  for(int i=1;i <= t; i++)
    {
      ret = (long long)ret * ret % n;
      if(ret == 1 && last != 1 && last != n - 1) return true;
      last = ret;
    }
  if(ret != 1) return true;
  else return false;
}
bool Miller_Rabin(int n)
{
  if((n & 1) == 0) return false;
  int x = n - 1;
  int t = 0;
  while((x & 1) == 0) {
    x >>= 1;
    t++;
  }
  for(int i = 0; i < 20; i++) {
    int a = rand() % (n - 1) + 1;
    if(Check(a, n, x, t)) return false;
  }
  return true;
}
bool IsPrime(int x) {
  if (x < 400) {
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int i = 3; i * i <= x; i+= 2)
      if (x % i == 0) return false;
    return true;
  } else {
    return Miller_Rabin(x);
  }
}

int a, b;
int dig[12];
bool stopmark;
void Search(const int &step, const int &length) {
  if (step > (length + 1) / 2) {
    for (int i = length; i >= step; i--)
      dig[i] = dig[length + 1 - i];
    int x = 0;
    for (int i = 1; i <= length; i++)
      x = x * 10 + dig[i];
    if (x < a) return;
    if (x > b) {
      stopmark = true;
      return;
    }
    if (IsPrime(x)) printf("%d\n", x);
  } else {
    for (int i = (step == 1 ? 1 : 0); i < 10; i++) {
      dig[step] = i;
      Search(step + 1, length);
      if (stopmark) return;
    }
  }
}

int main() {
  scanf("%d%d", &a, &b);
  int la = GetLength(a), lb = GetLength(b);
  stopmark = false;
  for (int i = la; i <= lb; i++) {
    if (i == 1) {
      if (a <= 5 && 5 <= b) puts("5");
      if (a <= 7 && 7 <= b) puts("7");
    } else if (i == 2) {
      if (a <= 11 && 11 <= b) puts("11");
    } else if (i % 2 == 1) {
      Search(1, i);
    }
  }
  return 0;
}
