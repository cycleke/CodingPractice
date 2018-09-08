n = int(input())
a = [int(x) for x in input().split()]
s = set()
for x in a:
    for y in a:
        if x != y : s.add(x + y)
print(len(s & set(a)))
