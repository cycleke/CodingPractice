#!/usr/bin/env python3
# -*- coding: utf-8 -*-

gao = lambda:map(int, input().split())

n = gao()
a = gao()
a = sorted(a)[::-1]
a[1:1] = a.pop(),
print(*a)
