//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 1e5+5, inf = 2e9;

int a[N], k, A, B;
int solve(int l, int r) {
    int res = inf, sz = 0;
    int u = lower_bound(a+1,a+1+k,l)-a, v = upper_bound(a+1,a+1+k,r)-a;
    sz = v - u;
    if (!sz) return A;
    if (l == r) return B*sz;
    int mid = (l+r)>>1;
    int x = solve(l, mid), y = solve(mid+1, r);
    res = x + y;
    return min(res, sz*(r-l+1)*B);
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n;
signed main() {
    read(n,k,A,B);
    for (int i = 1; i <= k; ++i) read(a[i]);
    sort(a+1,a+1+k);
    int len = 1<<n;
    write(solve(1,len)), putchar('\n');
    return 0;
}