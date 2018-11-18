def getRawInteger():
    return [int(x) for x in input().split()]


t = getRawInteger()[0]
for i in range(t):
    a, b, k = getRawInteger()
    cb = k // 2
    ca = k - cb
    print(a * ca - b * cb)
