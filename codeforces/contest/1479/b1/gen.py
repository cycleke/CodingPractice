# -*- coding: utf-8 -*-

from random import randint as rnd

n, x = 10**5, 10
print(n)
print(*[rnd(1, x) for _ in range(n)])
