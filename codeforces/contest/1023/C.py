n, k = [int(x) for x in input().split()]
s = input()
pairs = k // 2
subs = ''
count = 0
sum = 0
for i in range(len(s)):
    if s[i] == '(':
        sum += 1
        count += 1
        subs += '('
        if count == pairs:
            subs += ')' * sum
            break
    else:
        if sum > 0:
            sum -= 1
            subs += ')'
print(subs)
