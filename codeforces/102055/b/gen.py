import random
from random import randint as rnd

MAXN = 10
MAXV = 100

def singal():
    n = rnd(1, MAXN)
    res = str(n * 2) + ' ' + str(n) + '\n'
    for i in range(1, n + 1):
        res += '{} {}\n'.format(i * 2 - 1, i * 2)
    for i in range(n * 2):
        res += '{} {}\n'.format(rnd(1, MAXV), rnd(1, MAXV))
    return res

print(20)
for i in range(20):
    print(singal())
