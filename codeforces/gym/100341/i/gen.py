# -*- coding: utf-8 -*-

import random
from random import randint as rnd

MAXN = 10
MAXX = 100

s = {(0, 0)}

for i in range(MAXN):
    x = rnd(-MAXX, MAXX)
    y = rnd(-MAXX, MAXX)
    s.add((x, y))

s.remove((0, 0))
p = list(s)
random.shuffle(p)
n = len(p)

print(n)
for x, y in p:
    print(x, y)
