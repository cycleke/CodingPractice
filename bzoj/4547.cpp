#include <cstdio>
#include <cstring>

const int mod(10000007);

struct Matrix {
    int n, m, a[3][3];
} A, B;

Matrix operator * (const Matrix &a, const Matrix &b) {
    static Matrix c;
    c.n = a.n, c.m = b.m;
    memset(c.a, 0, sizeof c.a);
    for (register int k = 0; k < a.m; ++k)
        for (register int i = 0; i < a.n; ++i)
            for (register int j = 0; j < b.m; ++j)
                c.a[i][j] = (c.a[i][j] + (long long)a.a[i][k] * b.a[k][j]) % mod;
    return c;
}

int main() {
    int n, k, x;
    A.n = 1, A.m = 3;
    A.a[0][0] = A.a[0][1] = -1000000000;

    scanf("%d%d", &n, &k);
    for (register int i = 0; i < n; ++i) {
        scanf("%d", &x);
        A.a[0][2] = (A.a[0][2] + x) % mod;
        if (x >= A.a[0][1]) {
            A.a[0][0] = A.a[0][1];
            A.a[0][1] = x;
        } else if (x > A.a[0][0])
            A.a[0][0] = x;
    }

    while (A.a[0][0] < 0 && k) {
        --k;
        x = A.a[0][0] + A.a[0][1];
        A.a[0][2] = (A.a[0][2] + x) % mod;
        A.a[0][0] = x;
    }
    B.n = B.m = 3;
    B.a[1][0] = 1;
    B.a[0][1] = B.a[1][1] = 1;
    B.a[0][2] = B.a[1][2] = B.a[2][2] = 1;
    for (; k; (k >>= 1) ? (B = B * B, 1) : 0)
        if (k & 1) A = A * B;
    A.a[0][2] += mod;
    printf("%d", A.a[0][2] % mod);
    return 0;
}
