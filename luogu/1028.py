n = int(input())
f = [0] * (n + 1)
for i in range(1, n + 1):
    half = i // 2
    for j in range(1, half + 1):
        f[i] += f[j]
    f[i] += 1
print(f[n])
