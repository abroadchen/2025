//
// Created by Psy.C on 2026/3/1.
//
/**
c^48 相当于 c-'0'，将字符转换为数字

pre[n-i]*c(n-1-i,m-1)：前缀和的组合贡献
a[n-i+1]*c(n-i,m)：当前元素的组合贡献
整体乘以权重 x 后累加到答案
 */
#include <bits/stdc++.h>
using namespace std;

///快速读取整数
template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

///读取单个数字字符
inline void readd(int& x) {
    char c = getchar();
    for (; !isdigit(c); c = getchar()) {}
    x = c^48;
}

template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;//确定数字的位数和最高位权值
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);//从高位到低位输出每一位数字
}


constexpr int N = 1e5+1, mod = 1e9+7;

inline int ksm(int x, int p) {
    int res = 1;
    for (; p; p>>=1, x = 1ll*x*x%mod)
        if (p&1) res = 1ll*res*x%mod;
    return res;
}

int fac[N], inv[N];
inline void init() {
    fac[0] = 1;
    for (int i = 1; i <= N-1; ++i) fac[i] = 1ll*fac[i-1]*i%mod;
    inv[N-1] = ksm(fac[N-1], mod-2);
    for (int i = N-2; ~i; --i) inv[i] = 1ll*inv[i+1]*(i+1)%mod;
}

inline int c(const int n, const int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}

int n, m, a[N], pre[N], ans;
int main() {
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
        readd(a[i]);
        pre[i] = pre[i-1] + a[i];
    }
    init();
    for (int x = 1, i = 1; i <= n-m; ++i, x = 1ll*x*10%mod)
        ans = (ans+1ll*x*(1ll*pre[n-i]*c(n-1-i,m-1)%mod+
            1ll*a[n-i+1]*c(n-i,m)%mod)%mod)%mod;
    write(ans);
    putchar('\n');
    return 0;
}