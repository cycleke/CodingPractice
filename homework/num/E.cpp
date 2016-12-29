#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef unsigned long long LL;
template<class T>
T readint(T &a) {
    a = 0; char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        a = (a << 3) + (a << 1) + c - '0';
        c = getchar();
    }
    return a;
}

