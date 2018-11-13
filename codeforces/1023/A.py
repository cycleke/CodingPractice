input()
s = input()
t = input()

sl = s.split('*')
if len(sl) == 1:
    if s == t:
        print("YES")
    else:
        print("NO")
else:

    def Equal(a, b):
        if a == '' or b == '':
            return True
        return a == b

    if len(s) - 1 > len(t):
        print("NO")
    elif Equal(sl[0], t[:len(sl[0])]) and Equal(sl[1], t[-len(sl[1]):]):
        print("YES")
    else:
        print("NO")
