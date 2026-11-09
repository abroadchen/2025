//
// Created by Psy.C on 2026/11/9.
//

/**
真正学会的起点..
L=1024=2^10：FFT 的长度。
P = 490019：一个素数。
phi = P-1 = 490018：Fermat 小定理的指数模数。
关键拆分：P-1 = 490018。注意到 490018 = 2 × 491 × 499 = 2 × K × (M-1)，其中 K=491，M-1=499。这三个因式两两互素 → 指数可以按 CRT 拆成三维（每个维度对应一个因子），这就是后面 Chi/iChi 的存在意义
完全手写一个 double 复数类，供 FFT 使用（也可以直接用 complex<double>，这里为性能自写）。
A[2][L][L]、B[2][L][L]：两个三维数组存"二维频域信号"，第三维取 0/1 两个"奇偶性相位"（对应 CRT 分解里"2"那个因子）。
w[L]：单位根表
标准模幂、模逆元
因为 phi = P-1 = 2·K·(M-1) 且三个因子两两互素，任意指数 i 可以被唯一分解为三元组 (x, y, z)：
x = i mod 2（奇偶性）
y = i mod K
z = i mod (M-1)
这就是 中国剩余定理（CRT）‍：给定 (a,b,c)（三余数），iChi 用 CRT 反解出唯一的指数 i = (a·X + b·Y + c·Z) mod phi，其中 X/Y/Z 是各因子对应的预计算系数（保证在对应模意义下为 1，在其它模意义下为 0）。
作用：把原来需要处理 phi 种不同指数的问题，降到三个小维度组合，为后面 FFT/分块铺路
pwc[k] = c^k mod P：因为后面指数形如 (i²·j³) mod phi，而 c^k mod P 随 k 以 phi 为周期，所以预先把所有 c^k 存下来，查询 O(1)。
pw1/lg1：在模 K=491 下，7 是原根，pw1[t]=7^t mod 491，lg1[值]=对应t。这样乘法换指数→加法（相当于把模 491 的乘法群映射成加法群，配合后面指数求和变卷积）。
pw2/lg2 同理在模 M-1=499 下。
这几个表是为了把"指数相乘"转换成"指数相加"，从而可以用 FFT 高效做卷积
dft 是一维 FFT / 逆 FFT（ri 指明方向）。
idft(F, ir) 对二维数组做二维 FFT：先沿行方向、再沿列方向各做一次一维变换，这是标准的二维 FFT 分解
st[] 记录所有"以 K 为步长"和"以 M-1 为步长"的下标。因为 CRT 分解要求每个维度索引满足特定约束，所以先显式算出这些小块位置直接累加。
三个双层循环分别累加：只动 i、只动 j、以及"选一个边界 i × 选一个边界 j"这三种低纬度/边界情况，用朴素 O(双边界规模) 直接累加进 ans。
这是分块/阈值优化：把指数落在"较整齐边界"上的项直接算掉，剩下的"大数据量主体"交给后面的 FFT 处理。避免 FFT 维度过大。
这部分逻辑复杂，核心是先把能直接算的边界项累加进 ans，主体留给 FFT
把每个下标 i 先用 Chi 拆成三维 (x,y,z)。
lg1[y]<<1、lg2[z]<<1：把"模 K 的指数"和"模 M-1 的指数"翻倍（因为公式里是 i²，指数翻倍对应乘法群上的平方）。lg2[z]*3 同理对应 j³。
把 a[i] 累加到三维数组 A[x][y][z] 上。这样把"序列"写成了"三维频域稀疏信号"，为二维 FFT 做准备。
if (x) A[0][y][z].r += a[i]：处理奇偶维度为 1 时的归并（CRT 里“2”这一维度）
标准的"二维 FFT 卷积"套路：A、B 正变换到频域 → 逐点相乘 → 逆变换回到时域
从频域结果中取整数部分（FFT 浮点求整）。
用 iChi 把三维坐标 CRT 反解回原指数，pwc[...] 查 c^指数 幂表，乘上卷积值累加进 ans。
if (!x) v -= A[1][...]：奇偶维度归并的减项（涉及 CRT 第 1 维度为 1 时对 0 的修正）。
最后 (ans+P)%P 把结果规范到 [0,P) 输出
*/
#include <bits/stdc++.h>
#define rep(i,n) for (i=1; i<n; ++i)
#define db double
#define pi acos(-1.)
#define ll long long
using namespace std;

constexpr int N = 1e5+10, L = 1024, P = 490019, phi = P-1, M = 500, K = 491;

struct cp {
    db r, i;
    cp(db _r=0, db _i=0) : r(_r), i(_i) {}
    cp operator+(const cp &o) const { return {r+o.r, i+o.i}; }
    cp operator-(const cp &o) const { return {r-o.r, i-o.i}; }
    cp operator*(const cp &o) const { return {r*o.r-i*o.i, i*o.r+o.i*r}; }
    cp operator/(const db &o) const { return {r/o, i/o}; }
    void operator*=(const cp &o) { *this = *this * o; }
    void operator/=(const db &o) { *this = *this / o; }
} A[2][L][L], B[2][L][L], w[L];

int ksm(int x, int k, int mod) {
    int r = 1;
    for (; k; k>>=1, x=1ll*x*x%mod)
        if (k&1) r=1ll*r*x%mod;
    return r;
}
int Iv(int x, int mod) { return ksm(x, mod-2, mod); }


void Chi(int i, int &x, int &y, int &z) { x = i&1; y = i%K; z = i%(M-1); }
int iChi(int a, int b, int c) {
    int x = 1ll*K*(M-1)*Iv(K*(M-1), 2) % phi;
    int y = 2ll*(M-1)*Iv(2*(M-1), K) % phi;
    int z = 2ll*K*Iv(2*K, M-1) % phi;
    return (1ll*a*x + 1ll*b*y + 1ll*c*z) % phi;
}

int R[L], pwc[phi], c, pw1[M], lg1[M], pw2[M], lg2[M];
void init() {
    int x = 9, i;
    rep(i,L) R[i] = R[i>>1]>>1|(i&1)<<x;
    for (i = 0; i < L; ++i) w[i] = {cos(2*pi*i/L), sin(2*pi*i/L)};
    pwc[0] = 1;
    rep(i,phi) pwc[i] = 1ll*pwc[i-1]*c%P;
    pw1[0] = 1;
    rep(i,M-10) { pw1[i] = pw1[i-1]*7%K; lg1[pw1[i]] = i; }
    pw2[0] = 1;
    rep(i,M-2) { pw2[i] = pw2[i-1]*7%(M-1); lg2[pw2[i]] = i; }
}

void dft(cp *F, int ri) {
    int i;
    rep(i,L) if (i < R[i]) swap(F[i], F[R[i]]);
    int d = L>>1, j, k;
    for (i = 1; i < L; i<<=1, d>>=1)
        for (j = 0; j < L; j += i<<1) {
            cp *l = F+j, *r = F+j+i, *p = w, tp;
            for (k = i; k--; ++l, ++r, p += d)
                tp = *r**p, *r = *l-tp, *l = *l+tp;
        }
    if (!~ri) {
        rep(i,L>>1) swap(F[i], F[L-i]);
        for (i = 0; i < L; ++i) F[i]/=L;
    }
}
void idft(cp F[L][L], int ir) {
    int i, j;
    for (i = 0; i < L; ++i) dft(F[i], ir);
    for (i = 0; i < L; ++i) {
        static cp tp[L];
        for (j = 0; j < L; ++j) tp[j] = F[j][i];
        dft(tp, ir);
        for (j = 0; j < L; ++j) F[j][i] = tp[j];
    }
}

int tp, n, m, st[N], a[N], b[N], ans;
void solve() {
    tp = 0; int i, j;
    for (i = 0; i < max(n, m); i += K) st[++tp] = i;
    for (i = 0; i < max(n, m); i += M-1) st[++tp] = i;
    sort(st+1, st+tp+1);
    tp = unique(st+1, st+tp+1) - st - 1;
    for (i = 0; i < n; ++i) {
        int i2 = 1ll*i*i%phi; ll sum = 0;
        for (j = 1; j <= tp && st[j] < m; ++j) {
            int j3 = 1ll*st[j]*st[j]*st[j]%phi;
            sum += 1ll*a[i]*b[st[j]]*pwc[1ll*i2*j3%phi]%P;
        }
        ans = (ans + sum) % P;
    }
    for (j = 0; j < m; ++j) {
        int j3 = 1ll*j*j*j%phi; ll sum = 0;
        for (i = 1; i <= tp && st[i] < n; ++i) {
            int i2 = 1ll*st[i]*st[i]%phi;
            sum += 1ll*a[st[i]]*b[j]*pwc[1ll*i2*j3%phi]%P;
        }
        ans = (ans + sum) % P;
    }
    for (i = 1; i <= tp && st[i] < n; ++i) {
        int i2 = 1ll*st[i]*st[i]%phi; ll sum = 0;
        for (j = 1; j <= tp && st[j] < m; ++j) {
            int j3 = 1ll*st[j]*st[j]*st[j]%phi;
            sum += 1ll*a[st[i]]*b[st[j]]*pwc[1ll*i2*j3%phi]%P;
        }
        ans = (ans - sum) % P;
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}


int main() {
    int i, j;
    n = rd(), m = rd(), c = rd();
    for (i = 0; i < n; ++i) a[i] = rd();
    for (i = 0; i < m; ++i) b[i] = rd();
    init(); solve();
    for (i = 0; i < n; ++i) {
        int x, y, z; Chi(i, x, y, z);
        if (!y || !z) continue;
        y = (lg1[y]<<1)%(M-10); z = (lg2[z]<<1)%(M-2);
        A[x][y][z].r += a[i];
        if (x) A[0][y][z].r += a[i];
    }
    for (j = 0; j < m; ++j) {
        int x, y, z; Chi(j, x, y, z);
        if (!y || !z) continue;
        y = (lg1[y]*3)%(M-10); z = (lg2[z]*3)%(M-2);
        B[x][y][z].r += b[j];
        if (x) B[0][y][z].r += b[j];
    }
    idft(A[0], 1); idft(A[1], 1); idft(B[0], 1); idft(B[1], 1);
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < L; ++y)
            for (int z = 0; z < L; ++z) A[x][y][z] *= B[x][y][z];
    idft(A[0], -1); idft(A[1], -1);
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < L; ++y)
            for (int z = 0; z < L; ++z) {
                ll v = (ll)(A[x][y][z].r + 0.5);
                if (!x) v -= (ll)(A[1][y][z].r + 0.5);
                v %= P;
                ans = (ans + v*pwc[iChi(x,pw1[y%(M-10)], pw2[z%(M-2)])])%P;
            }
    cout << (ans+P)%P << '\n';
    return 0;
}