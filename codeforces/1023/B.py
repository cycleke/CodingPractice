n, k = [int(x) for x in input().split()]
if k & 1:
    print(max(0, min(k // 2, n - k // 2)))
else:
    print(max(0, min(k // 2 - 1, n - k // 2)))
