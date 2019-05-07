#!/usr/bin/env python3

n, m, r = map(int, input().split())
mi = min(map(int, input().split()))
mx = max(map(int, input().split()))

print(max(r, r // mi * mx + r % mi))

