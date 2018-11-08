n, m, k, l = map(int, input().split())
each = -(-(k + l) // m)
if each * m > n:
    print(-1)
else:
    print(each)
