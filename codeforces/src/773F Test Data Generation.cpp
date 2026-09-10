//
// Created by Psy.C on 2026/9/9.
//
/**
cp 是复数结构体，重载了 +、-、*、/ 运算符，用于 FFT 的复数运算。
复数乘法 (a+bi)(c+di) = (ac-bd) + (ad+bc)i，代码 {x*o.x - y*o.y, o.x*y + x*o.y} 正确实现。
w[N<<1]：预计算好的单位根（旋转因子）表，避免递归重复计算，是 FFT 的查表版本
计算 FFT 所需的位逆序（bit-reversal）置换表 tr[i]。
tr[i] = tr[i>>1]>>1 | ((i&1)? n>>1 : 0)：经典的 DP 式位逆序。若长度 n 没变（cnt == n）就跳过，避免重复计算。
作用是：把输入序列按下标二进制的逆序重排，作为蝶形运算的准备
预计算所有需要的单位根：w[i+j] = e^{(2π/2i)·j}（这里 pi*j/i 配合前面结构，实际上存的是 exp(i*pi*j/len) 风格的内核）。
关键优化：只每隔 32 个直接算一次 cos/sin，中间的元素用前一个旋转因子乘以 w[i+1]（累乘递推）得到。这大幅减少三角函数调用次数，是性能优化的常见技巧。
w[i] = cp(1,0)：每层第 0 个根为 1
迭代式 FFT（非递归）。先做位逆序（rev(n)），把每个元素搬到 f[tr[i]]。
三层循环实现蝶形运算（butterfly）‍：
外层 p：当前跨度/块大小（块长从 2 倍增到 n），l = p/2 是半宽。
中层 i：每块起始位置。
内层 j：块内位置，w[j|l] 是旋转因子（j|l 即 l+j，因为 l 是 2 的幂，位或=加）。
蝶形操作：t = w * f[i+j+l]; f[i+j+l] = f[i+j] - t; f[i+j] = f[i+j] + t;（标准的 Cooley–Tukey 蝶形）。
op 为 true 表示逆变换（IDFT）‍：需要除以 n（每个元素 /n）

mtt：基于 FFT 的卷积（此处用复数 FFT 而非真正模域 NTT，故可能是"任意模数/近似模板"）。
计算卷积长度 n（≥ 2m 的最小的 2 的幂）。
把 f、g 装入复数数组 p、q，高位补 0。
正变换两个（dft(...,0,n)）、点乘（px）、reverse(p+1,p+n)（这是逆变换的另一种实现技巧）、逆变换（dft(p,1,n)）。
最后把每个卷积项四舍五入取模写回 f——用 f 复用保存卷积结果。
注意：这里用的是复数 FFT 做整数卷积，属于"mTT（my/Multi-Ten-th FFT / 任意模数）‍"风格，若两道瓶颈是取模也是正常
add：在生成函数上做一次「单步转移」。
对当前状态 p（0 或 1），从高到低倒序更新：f[p][i] += f[0][i-1] + f[1][i-1]——即新系数等于上一步两个状态的前一系数之和（很像"走一步"的组合计数递推）。
f[p][1] += 1：边界处的 +1（新增一条路径
mul：用卷积实现"翻倍"——把当前生成函数与自身（对角/交叉）卷积，模拟一次倍增。
先用 g[i][j] = f[0][j]+f[1][j] 作为公共因子，令 g[0][0]=g[1][0]=1，然后两次 mtt（卷积）更新 f。
这实质是生成函数的"平方/倍增"运算，对应组合递推里的"步数翻倍"
读入 n, mx, mod，mx /= 2（题面里 x 步数折半），lg = log2(mx) 是倍增的上界。
n 扩展为 ≥2m 的最小的 2 的幂作为 FFT 长度，init(n) 预计算旋转因子。
核心倍增循环（从高二进制位到低）：对每个二进制位：
mul(j&1, m) 做一次倍增平方；j <<= 1。
若当前位为 1（mx & (1<<i)），则 add((j|1)&1, m) 做一次单步加法，j |= 1。
累加奇数位系数 f[1][k]（k 为奇数）到 ans。
最后输出 ans
 */
#include <bits/stdc++.h>
#define pi acos(-1)
#define ll long long
using namespace std;
constexpr int N = 4e5+5;
struct cp {
    double x, y;
    cp(double x=0.0, double y=0.0) : x(x), y(y) {}
    cp operator+(const cp& o) const { return {x + o.x, y + o.y}; }
    cp operator-(const cp& o) const { return {x - o.x, y - o.y}; }
    cp operator*(const cp& o) const { return {x * o.x - y * o.y, o.x * y + x * o.y}; }
    cp operator+(const double& o) const { return {x + o, y + o}; }
    cp operator-(const double& o) const { return {x - o, y - o}; }
    cp operator*(const double& o) const { return {x * o, y * o}; }
    cp operator/(const double& o) const { return {x / o, y / o}; }
} w[N<<1];

int cnt, tr[N<<1];
inline void rev(int n) {
    if (cnt == n) return;
    cnt = n;
    for (int i = 0; i < n; ++i)
        tr[i] = tr[i>>1]>>1|((i&1)?n>>1:0);
}

inline void init(int n) {
    for (int i = 1; i < n; i <<= 1) {
        w[i] = cp(1, 0);
        for (int j = 1; j < i; ++j)
            w[i+j] = (((j&31)==1)?cp(cos(pi*j/i), sin(pi*j/i)):w[i+j-1]*w[i+1]);
    }
}

void dft(cp *g, bool op, int n) {
    rev(n);
    static cp f[N<<1], t;
    for (int i = 0; i < n; ++i) f[i] = g[tr[i]];
    for (int p = 2, l = 1; p <= n; l = p, p <<= 1)
        for (int i = 0; i < n; i += p)
            for (int j = 0; j < l; ++j)
                t = w[j|l]*f[i|j|l], f[i|j|l] = f[i|j]-t, f[i|j] = f[i|j]+t;
    if (op)
        for (int i = 0; i < n; ++i) g[i] = f[i]/n;
    else
        for (int i = 0; i < n; ++i) g[i] = f[i];
}

//频域点乘（卷积定理的中间步骤）：逐点相乘
inline void px(cp *f, cp *g, int n) {
    for (int i = 0; i < n; ++i)
        f[i] = f[i] * g[i];
}

int mod;
//把浮点结果（FFT 的实部）‍四舍五入并取模 mod
inline ll num(double x) {//+0.49/-0.49 是做四舍五入的浮点补偿
    return x < 0 ? (ll)(x-0.49)%mod:(ll)(x+0.49)%mod;
}

cp p[N<<1], q[N<<1];
void mtt(int *f, int *g, int m) {
    int n = 1;
    for (; n < m<<1; n <<= 1) {}
    for (int i = 0; i < m; ++i) p[i] = cp(f[i], 0), q[i] = cp(g[i], 0);
    for (int i = m; i < n; ++i) p[i] = q[i] = cp(0, 0);
    dft(p, 0, n); dft(q, 0, n); px(p, q, n);
    reverse(p+1, p+n);
    dft(p, 1, n);
    for (int i = 0; i < m; ++i) f[i] = (num(p[i].x)+mod)%mod;
}

int f[2][N<<1];
void add(int p, int m) {
    for (int i = m; i; --i) f[p][i] = (f[p][i]+f[0][i-1]+f[1][i-1])%mod;
    f[p][1] = (f[p][1] + 1)%mod;
}

int g[2][N<<1], n;
void mul(int p, int m) {
    for (auto& i : g)
        for (int j = 1; j < m; ++j)
            i[j] = (f[0][j] + f[1][j])%mod;
    g[0][0] = g[1][0] = 1;
    mtt(g[0], f[p], m); mtt(g[1], f[p^1], m);
    for (int i = 0; i < 2; ++i)
        for (int j = 1; j < m; ++j)
            f[i][j] = (g[i][j] + f[i][j])%mod;
    memset(g[0], 0, sizeof(int)*n);
    memset(g[1], 0, sizeof(int)*n);
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

int main() {
    int mx, lg = 0, j = 0; rd(n), rd(mx); rd(mod); mx/=2;
    if (mx) lg = log2(mx);
    ll ans = 0;
    int m = n+1;
    for (n = 1; n < m<<1; n <<= 1) {}
    init(n);
    for (int i = lg; ~i; --i) {
        mul(j&1, m); j <<= 1;
        if (mx&(1<<i)) add((j|1)&1, m), j |= 1;
        for (int k = 1; k < m; ++k)
            if (k&1) ans += f[1][k];
        ans %= mod;
    }
    write(ans); puts("");
    return 0;
}