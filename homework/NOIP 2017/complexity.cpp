#include <cstdio>
#include <cstring>
#include <cstdlib>

const char *R[3] = {"Yes", "No", "ERR"};

inline int CComplex(int line) {
	char Var[110];
	bool Memory[26], Mark[110], Contributed[110];
	int complex = 0, maxcomplex = 0;
	int StackCount = 0, NotRun = 0;
	memset(Mark, 0, 110);
	memset(Memory, 0, 26);
	memset(Contributed, 0, 110);
	for (int i = 0; i < line; ++i) {
		char op = getchar();
		while ((op != 'F') && (op != 'E'))
			op = getchar();
		if (op == 'F') {
			char var, sx[5], sy[5];
			scanf(" %c %s %s", &var, sx, sy);
			if (Memory[var - 'a']) {
				char buffer[30];
				for (int j = i; j < line; ++j)
					gets(buffer);
				return -1;
			}
			Memory[var - 'a'] = true;
			Var[StackCount++] = var;
			if (sx[0] == 'n') {
				if (sy[0] == 'n')
					continue;
				++NotRun;
				Mark[StackCount - 1] = true;
				continue;
			}
			if (sy[0] == 'n') {
				++complex;
				Contributed[StackCount - 1] = true;
				if (NotRun == 0 && complex > maxcomplex)
					maxcomplex = complex;
				continue;
			}
			if (atoi(sx) > atoi(sy)) {
				++NotRun;
				Mark[StackCount - 1] = true;
				continue;
			}
		}
		else {
			--StackCount;
			if (Contributed[StackCount]) {
				--complex;
				Contributed[StackCount] = false;
			}
			if (StackCount < 0) {
				char buffer[30];
				for (int j = i; j < line; ++j)
					gets(buffer);
				return -1;
			}
			Memory[Var[StackCount] - 'a'] = false;
			if (Mark[StackCount]) {
				--NotRun;
				Mark[StackCount] = false;
			}
		}
	}
	return StackCount == 0 ? maxcomplex : -1;
}

inline int Check() {
	int L, w;
	char O[10];
	scanf("%d %s", &L, O);
	if (O[2] == '1') w = 0;
	else w = atoi(O + 4);
	int Complex = CComplex(L);
	if (Complex == -1)
		return 2;
	return Complex == w ? 0 : 1;
}

int main() {
	freopen("complexity.in", "r", stdin);
	freopen("complexity.out", "w", stdout);
	int _;
	scanf("%d", &_);
	while (_--)
		puts(R[Check()]);
	return 0;
}
