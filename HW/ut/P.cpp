#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int Maxn = 1e6 + 5;

LL Stack[Maxn];
char tmpS[Maxn];

int main() {
	int T, top, sign, op, len, pos; char ch;
	LL ans, a;
	scanf("%d%*c", &T); 
	while (T--) {
		scanf("%s", tmpS);
		pos = a = top = 0; op = sign = 1;
		len = strlen(tmpS);
		while (pos < len) {
			ch = tmpS[pos++];
			if (ch == '#' || ch  == ' ')
                 break;
			if (ch >= '0' && ch <= '9') {
				a = (a << 3) + (a << 1) + ch - '0';
			} else {
				Stack[top++] = a * sign;
				sign = 1; a = 0;
				if (op == 2) {
					Stack[top - 2] = Stack[top - 1] * Stack[top - 2];
					--top;
				} else if (op == 3) {
					Stack[top - 2] = Stack[top - 2] / Stack[top - 1];
					--top;
				}
				op = 1;
				if (ch == '-') sign = -1;
				else if (ch == '*') op = 2;
				else if (ch == '/') op = 3;
			}
		}
		Stack[top++] = a * sign;
		if (op == 2) {
			Stack[top - 2] = Stack[top - 1] * Stack[top - 2];
			--top;
		} else if (op == 3) {
			Stack[top - 2] = Stack[top - 2] / Stack[top - 1];
			--top;
		}
		ans = 0;
		for (int i = 0; i < top; ++i) ans += Stack[i];
		printf("%lld\n", ans);
	}
	
	return 0;
}
