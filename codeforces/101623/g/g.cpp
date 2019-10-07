// by sineMora
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <vector>
#include <map>
#define fo(i, l, r) for (int i = l; i <= r; i++)
#define fd(i, l, r) for (int i = r; i >= l; i--)
#define mem(x) memset(x, 0, sizeof(x))
#define ll long long
#define double long double
using namespace std;
const double eps = 1e-13;
const double pi = acos(-1);
ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (!(ch >= '0' && ch <= '9'))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    };
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    };
    return x * f;
}
//Compares a double to zero
int sgn(double x)
{
    if (fabs(x) < eps)
        return 0;
    if (x < 0)
        return -1;
    else
        return 1;
}
//square of a double
inline double sqr(double x) { return x * x; }
struct Point
{
    double x, y;
    Point() {}
    Point(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
    void input()
    {
        scanf("%lf%lf", &x, &y);
    }
    void output()
    {
        printf("%.2f,%.2f\n", x, y);
    }
    bool operator==(Point b) const
    {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    bool operator<(Point b) const
    {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }
    Point operator-(const Point &b) const
    {
        return Point(x - b.x, y - b.y);
    }
    //叉积
    double operator^(const Point &b) const
    {
        return x * b.y - y * b.x;
    }
    //点积
    double operator*(const Point &b) const
    {
        return x * b.x + y * b.y;
    }
    //返回长度
    double len()
    {
        return hypot(x, y); //库函数
    }
    //返回长度的平方
    double len2()
    {
        return x * x + y * y;
    }
    //返回两点的距离
    double distance(Point p)
    {
        return hypot(x - p.x, y - p.y);
    }
    Point operator+(const Point &b) const
    {
        return Point(x + b.x, y + b.y);
    }
    Point operator*(const double &k) const
    {
        return Point(x * k, y * k);
    }
    Point operator/(const double &k) const
    {
        return Point(x / k, y / k);
    }
    Point rotate(Point p, double angle)
    {
        Point v = (*this) - p;
        double c = cos(angle), s = sin(angle);
        return Point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
    }
} pts[1050];
struct Line
{
    Point s, e;
    Line() {}
    Line(Point _s, Point _e)
    {
        s = _s;
        e = _e;
    }
    bool operator==(Line v)
    {
        return (s == v.s) && (e == v.e);
    }
    //根据一个点和倾斜角 angle 确定直线,0<=angle<pi
    Line(Point p, double angle)
    {
        s = p;
        if (sgn(angle - pi / 2) == 0)
        {
            e = (s + Point(0, 1));
        }
        else
        {
            e = (s + Point(1, tan(angle)));
        }
    }
    //ax+by+c=0
    Line(double a, double b, double c)
    {
        if (sgn(a) == 0)
        {
            s = Point(0, -c / b);
            e = Point(1, -c / b);
        }
        else if (sgn(b) == 0)
        {
            s = Point(-c / a, 0);
            e = Point(-c / a, 1);
        }
        else
        {
            s = Point(0, -c / b);
            e = Point(1, (-c - a) / b);
        }
    }
    bool pointonseg(Point p)
    {
        return sgn((p - s) ^ (e - s)) == 0 && sgn((p - s) * (p - e)) <= 0;
    }
};
struct polygon
{
    int n;
    Point p[15];
    Line l[15];
    void getline()
    {
        for (int i = 0; i < n; i++)
        {
            l[i] = Line(p[i], p[(i + 1) % n]);
        }
    }
    int relationpoint(Point q)
    {
        for (int i = 0; i < n; i++)
        {
            if (p[i] == q)
                return 3;
        }
        getline();
        for (int i = 0; i < n; i++)
        {
            if (l[i].pointonseg(q))
                return 2;
        }
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            int j = (i + 1) % n;
            int k = sgn((q - p[j]) ^ (p[i] - p[j]));
            int u = sgn(p[i].y - q.y);
            int v = sgn(p[j].y - q.y);
            if (k > 0 && u < 0 && v >= 0)
                cnt++;
            if (k < 0 && v < 0 && u >= 0)
                cnt--;
        }
        return cnt != 0;
    }
    double getarea()
    {
        double sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += (p[i] ^ p[(i + 1) % n]);
        }
        return fabs(sum) / 2;
    }
} pol[10], tmp, nei, wai;
int n, nowpol;
bool check(double rate)
{
    tmp=pol[nowpol];
    for(int i = 0;i < tmp.n;i++){
        tmp.p[i] =tmp.p[i]*rate;
    }
    fo(i,1,n){
        if(tmp.relationpoint(pts[i])==1) return false;
    }
    return true;
}
bool check2(double rate)
{
    tmp=pol[nowpol];
    for(int i = 0;i < tmp.n;i++){
        tmp.p[i] =tmp.p[i]*rate;
    }
    fo(i,1,n){
        if(tmp.relationpoint(pts[i])==0) return false;
    }
    return true;
}
double ansrate=0.0;
int chs;
double fz,fm;
int main()
{
    n = read();
    fo(i, 1, n)
    {
        pts[i].x = read();
        pts[i].y = read();
    }
    fo(i, 1, 6)
    {
        nowpol = i;
        pol[i].n = i + 2;
        pol[i].p[0] = Point(100, 0);
        fo(j, 1, i + 1)
        {
            pol[i].p[j] = pol[i].p[j - 1].rotate(Point(0, 0), 2.0 * pi / (i + 2));
        }
        double lp = 1e-3, rp = 1e7, mid, ans;
        while (rp - lp > eps)
        {
            mid = (lp + rp) / 2.0;
            if (check(mid))
            {
                ans = mid;
                lp = mid;
            }
            else
            {
                rp = mid;
            }
        }
        fz=ans*ans;
        lp = 1e-3, rp = 1e7;
        while (rp - lp > eps)
        {
            mid = (lp + rp) / 2.0;
            if (check2(mid))
            {
                ans = mid;
                rp = mid;
            }
            else
            {
                lp = mid;
            }
        }
        fm=ans*ans;
        if(sgn(ansrate-fz/fm)<0){
            chs=i+2;
            ansrate=fz/fm;
        }
    }
    printf("%d %.10Lf",chs,ansrate);
    return 0;
}

