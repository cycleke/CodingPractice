#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  char password[51];
  scanf("%d%s", &n, password);
  int len = strlen(password);
  for (int i = 0; i < len; i++) {
    password[i] = (password[i]  - 'a' + n) % 26 + 'a';
  }
  puts(password);
  return 0;
}
