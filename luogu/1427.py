L = input().split()
L.remove('0')
out = ''
for x in reversed(L):
    out += x + ' '
print(out)
