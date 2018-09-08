n = int(input())
a = [int(x) for x in input().split()]
out = ''
for i in range(n):
    count = 0
    for j in range(i):
        if a[j] < a[i]: count += 1
    out += str(count) + ' '
print(out)
