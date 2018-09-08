a = [int(x) for x in input().split()]
height = int(input()) + 30
count = 0
for x in a:
    if x <= height: count += 1
print(count)
