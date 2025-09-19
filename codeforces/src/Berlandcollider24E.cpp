//
// Created by Psy.C on 2025/9/19.
//

/*
 *重载小于运算符，按位置x排序
 *
*mx记录当前最右边的正向运动物体的位置
对于正向运动的物体(v>0)，更新mx为最大位置
对于非正向运动的物体，计算其位置，如果位置小于mx说明发生碰撞
 *
 *
 *
*使用二分搜索找最早碰撞时间：
左边界l=0，右边界r=1e9+7
当精度足够时停止搜索(1e-10)
如果在mid时间发生碰撞，则答案在左半区间
否则在右半区间
如果没有碰撞，输出-1
 *
 *
 *
 *
 *
 *
 *
 */
#include <algorithm>
#include <cstdio>
using namespace std;

static const int maxn = 5e5+7;

inline void read() {}

template<class T1, class... T2>
inline void read(T1& a, T2&... b) {
    register T1 x = 0;
    register bool f = false;
    char ch = getchar();
    while (ch < '0') f |= (ch == '-'), ch = getchar();
    while (ch >= '0') x = (x * 10) + (ch ^ 48), ch = getchar();
    x = (f ? -x : x);
    a = x;
    read(b...);
}

template<class T> inline T qmax(const T& x, const T& y) { return x > y ? x : y; }
template<class T> inline T qmin(const T& x, const T& y) { return x < y ? x : y; }

struct node {
    long double x, v;
    node(){}
    node(long double _x, long double _v): x(_x), v(_v) {}
    bool operator<(const node& o) const { return x < o.x; }
} a[maxn];

long long n;

bool check(long double mid) {
    long double mx = -1e30;
    for (int i = 0; i < n; ++i) {
        if (a[i].v > 0) mx = qmax(mx, a[i].x + a[i].v * mid);
        else {
            long double t = a[i].x + a[i].v * mid;
            if (t < mx) return true;
        }
    }
    return false;
}

long double ans;

int main() {
    read(n); int i, j;
    for (i = 0; i < n; ++i) read(a[i].x, a[i].v);

    long double l = 0, r = 1e9 + 7;
    while (r - l >= 1e-10) {
        long double mid = (l + r) / 2;
        if (check(mid)) ans = r = mid;
        else l = mid;
    }

    if (r == 1e9 + 7) ans = -1;
    printf("%.10Lf\n", ans);
    
    return 0;
}