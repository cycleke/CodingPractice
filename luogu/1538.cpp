#include <cstdio>
#include <cstring>

int k, n;
char s[256];

void PrintCol(int status) {
  for (int i = 0; i < n; i++) {
    putchar_unlocked(' ');
    if (status >> (s[i] - '0') & 1) {
      for (int i = 0; i < k; i++)   
        putchar_unlocked(' ');
    } else {
      for (int i = 0; i < k; i++)
        putchar_unlocked('-');
    }
    putchar_unlocked(' ');
    putchar_unlocked(' ');
  }
  putchar_unlocked('\n');
}

void PrintRaw(int status1, int status2) {
  for (int step = 0; step < k; step++) {
    for (int i = 0; i < n; i++) {
      //putchar_unlocked(' ');
      if (status1 >> (s[i] - '0') & 1)
        putchar_unlocked(' ');
      else
        putchar_unlocked('|');
      for (int i = 0; i < k; i++)   
        putchar_unlocked(' ');
      if (status2 >> (s[i] - '0') & 1)
        putchar_unlocked(' ');
      else
        putchar_unlocked('|');
      putchar_unlocked(' ');
    }
    putchar_unlocked('\n');
  }
}

#define F(a) (1 << a)

int main() {
  scanf("%d%s", &k, s);
  n = strlen(s);
  
  PrintCol(F(1) | F(4));
  PrintRaw(F(1) | F(2) | F(3) | F(7), F(5) | F(6));
  PrintCol(F(1) | F(7) | F(0));
  PrintRaw(F(1) | F(3) | F(4) | F(5) | F(7) | F(9), F(2));
  PrintCol(F(1) | F(4) | F(7));

  return 0;
}
