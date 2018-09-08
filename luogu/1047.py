L, M = [int(x) for x in input().split()]
tree = set(range(L + 1))
for i in range(M):
    s, t = [int(x) for x in input().split()]
    tree -= set(range(s, t + 1))
print(len(tree))
