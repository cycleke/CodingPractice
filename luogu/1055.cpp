#include <cstdio>

int main() {
  char s[14], d[12] = "0123456789X";
  scanf("%s", s);
  int t = 0;
  for (int i = 0, j = 1; i < 12; i++) {
    if(s[i] == '-') continue;
    t += (s[i]-'0') * j++;
  }
  if (d[t%11] == s[12]) {
    printf("Right");
  } else {
    s[12] = d[t%11];
    puts(s);
  }
  return 0;
}
