//
// Created by Psy.C on 2026/10/13.
//
/**
OR 卷积的变换：正向（p=1）+ 逆 (p=-1，除以 len)。OR 卷积 C[k]=Σ_{i|j=k} a[i]b[j]
AND 卷积 C[k]=Σ_{i&j=k} a[i]b[j]，正变换区别在于累加方向相反。p=1 正变换，p=-1 逆变换
XOR 卷积，逆变换要乘 inv2（4 的模逆，因为 2*inv2≡1 (mod 1e9+7)）。这是标准 XOR-FWT
子集卷积（subset convolution）‍。语义：f[i][s] 表示异或值（bitmask）为 s、popcount(s)=i 的元素个数。子集卷积实现"选两个数 x、y 且 x&y==0（不重叠），最终结果 mask = x|y"的计数：

按 popcount 分层（i 层 × i-j 层），
对每层异或值做 OR 卷积（Σ_{x|y=s} f[j][x] f[i-j][y]），
逆变换后，只保留 popcount 为 i 的结果（因为 x&y==0 ⟺ popcount(x)+popcount(y)==popcount(x|y)）。
这就是"选两个不重叠的数，OR 起来"的经典子集卷积
cnt = popcount，fib = 斐波那契数列
f[cnt[v]][v]：子集卷积的输入；
c[v]：XOR 卷积的输入（出现次数）；
b[v]：累加 fib[v]（按位权）
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = (1<<17)+5, mod = 1e9+7, inv2 = 5e8+4;

int add(const int a) {
    return (a%mod + mod)%mod;
}

int len;
namespace OR {
    void fwt(int *f, const int p) {
        for (int s = 2; s <= len; s <<= 1)
            for (int i = 0, t = s>>1; i < len; i += s)
                for (int j = i; j < i+t; ++j)
                    f[j+t] = add(f[j+t]+p*f[j]);
    }
}

namespace AND {
    void fwt(int *f, const int p) {
        for (int s = 2; s <= len; s <<= 1)
            for (int i = 0, t = s>>1; i < len; i += s)
                for (int j = i; j < i+t; ++j)
                    f[j] = add(f[j]+p*f[j+t]);
    }
}

namespace XOR {
    void fwt(int *f, const int p) {
        int t1, t2;
        for (int s = 2; s <= len; s <<= 1)
            for (int i = 0, t = s>>1; i < len; i += s)
                for (int j = i; j < i+t; ++j) {
                    t1 = f[j], t2 = f[j+t];
                    if (p > 0) f[j] = (t1+t2)%mod, f[j+t] = add(t1-t2);
                    else f[j] = 1ll*(t1+t2)*inv2%mod, f[j+t] = 1ll*add(t1-t2)*inv2%mod;
                }
    }
}

int lg2, f[20][N], h[N], cnt[N], a[N];
void get() {
    for (int i = 0; i <= lg2; ++i) OR::fwt(f[i], 1);
    for (int i = 0; i <= lg2; ++i) {
        for (int s = 0; s < len; ++s) h[s] = 0;
        for (int j = 0; j <= i; ++j)
            for (int s = 0; s < len; ++s)
                h[s] = (h[s]+1ll*f[j][s]*f[i-j][s]%mod)%mod;
        OR::fwt(h, -1);
        for (int s = 0; s < len; ++s)
            if (cnt[s] == i) a[s] = (a[s]+h[s])%mod;
    }
}

int low_bit(const int x) { return x&-x; }
int count(int x) {
    int ret = 0;
    while (x) ret++, x -= low_bit(x);
    return ret;
}

int fib[N];
void init() {
    fib[0] = 0, fib[1] = 1;
    for (int i = 2; i < 1<<17; ++i) fib[i] = (fib[i-1]+fib[i-2])%mod;
    for (int i = 0; i < 1<<17; ++i) cnt[i] = count(i);
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n, mx, b[N], c[N], ans;
int main() {
    rd(n); init();
    for (int i = 1, v; i <= n; ++i) {
        rd(v), mx = max(mx, v);
        f[cnt[v]][v]++, c[v]++, b[v] = (b[v]+fib[v])%mod;
    }
    for (lg2=0, len=1; len <= mx; len<<=1, ++lg2){} get();//子集卷积 → a[]
    XOR::fwt(c, 1);
    for (int i = 0; i < len; ++i) c[i] = 1ll*c[i]*c[i]%mod;//XOR 自卷积
    XOR::fwt(c, -1);
    for (int i = 0; i < len; ++i)
        a[i] = 1ll*a[i]*fib[i]%mod, c[i] = 1ll*c[i]*fib[i]%mod;//乘斐波那契权
    AND::fwt(a, 1), AND::fwt(b, 1), AND::fwt(c, 1);//AND 变换
    for (int i = 0; i < len; ++i) a[i] = 1ll*a[i]*b[i]%mod*c[i]%mod;//点乘
    AND::fwt(a, -1);//AND 逆变换
    for (int i = 1; i <= len; i<<=1) (ans+=a[i])%=mod;//只累加 2 的幂的下标
    write(ans), putchar('\n');
    return 0;
}