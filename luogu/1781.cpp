#include <cstdio>
#include <cstring>

int main() {
  int n;
  scanf("%d", &n);
  int id = 0, num_length = 0;
  char num[101] = {0};
  for (int i = 1; i <= n; i++) {
    char s[101];
    scanf("%s", s);
    int length = strlen(s);
    if (length < num_length) continue;
    else if (length > num_length) {
      id = i;
      strcpy(num, s);
      num_length = length;
    } else {
      bool is_upper = false;
      for (int i = 0; i < length; i++) {
        if (s[i] > num[i]) {
          is_upper = true;
          break;
        } else if (s[i] < num[i]) {
          break;
        }
      }
      if (is_upper) {
        id = i;
        strcpy(num, s);
        num_length = length;
      }
    }
  }
  printf("%d\n%s", id, num);
  return 0;
}
