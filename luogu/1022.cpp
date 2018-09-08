#include <cstdio>
#include <cstring>

int main() {
  char s[100], x_name;
  scanf("%s", s);
  int n = strlen(s);
  for (int i = 0; i < n; ++i)
    if (s[i] >= 'a' && s[i] <= 'z') {
      x_name = s[i];
      break;
    }
  int sign = 1, i = 0;
  double a = 0, b = 0;
  while (i < n) {
    if (s[i] == '=') {
      sign = -1;
      i++;
    } else if (s[i] == x_name) {
      a += sign;
      i++;
    } else if (s[i] == '-' && s[i + 1] == x_name) {
      a -= sign;
      i += 2;
    }else {
      int _sign = s[i] == '-' ? -1 : 1, x = 0;
      if (s[i] == '-' || s[i] == '+') i++;
      while (s[i] >= '0' && s[i] <= '9')
        x = x * 10 + s[i++] - '0';
      x *= _sign;
      if (s[i] == x_name) {
        a += x * sign;
        i++;
      }
      else b += x * sign;
    }
    //printf("%lf %lf\n", a, b);
  }
  printf("%c=%.3lf\n", x_name, -b / a);
  return 0;
}
