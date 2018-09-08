def Calc(s):
    x = 1
    for ch in s:
        x = x * (ord(ch) - ord('A') + 1) % 47
    return x
if Calc(input()) == Calc(input()):
    print('GO')
else:
    print('STAY')
