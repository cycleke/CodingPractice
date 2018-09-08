n = int(input())
a = [int(x) for x in input().split()]
max_len, pre = 0, -1
cur_len = 0
for cur in a:
    if cur > pre:
        cur_len += 1
        max_len = max(max_len, cur_len)
    else:
        cur_len = 1
    pre = cur
print(max_len)
