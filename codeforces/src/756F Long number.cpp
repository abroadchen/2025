//
// Created by Psy.C on 2026/9/3.
//
/**
dat{val, ten} 双字段	一并维护"数值"和"长度因子"，拼接/去前缀均为 O(1)
operator- = 去前缀	conca(B)-conca(A) 直接得到区间 (A+1..B)，免单独算区间和
stereotype 闭式	用 Σ k·a^k 的公式 O(log) 算出任意大 N 的顶部段，无需逐位
双模数	数值走 mod p，指数走 mod φ，配合 Euler 定理处理超大指数
f[] 全 9 断点预处理	conca 只算位数最长的顶部段，低位部分 O(1) 查表
KSM 逐位倍增	大指数重复用"×10 + 数位"扫描，类比大数快速幂
默认参数 ksm(x) = 逆元	一个函数兼顾幂与求逆，简洁

预处理 f：O(S²)？不——每位 i 做一次 O(1) 的公式计算（ksm/msk 都是 O(log)），所以 O(S log S)。
实际上每步是常数次 ksm/msk（各 O(log p)），总计 O(S log p)。
括号匹配：O(S)。
solve：每个字符被扫一次，O(S) 次递归；每次 conca 代价 O(L)（扫数字串）+ O(log) 公式；KSM 代价 O(|N|)。整体 O(S) 量级（忽略 log 因子）。
总：O(S log p)，约 1e5 × 30，可过


A - B：gene(A) || (conca(B) - conca(A))。conca(B) = 1..B，conca(A) = 1..A，相减（去前缀）得 (A+1)..B，再前置 A → A, A+1, …, B。
N(X)：solve(p+1, mat[p]) 求括号内 X，KSM 重复 N 次；mat[p]+2 跳过 ) 和随后的 + 分隔符。
各项之间统一用 + 分隔，所以 +/-/) 后都跳一个分隔符（+1 或 +2）。
mat[] 由 main 里括号栈预处理：mat[左括号]=右括号，mat[右括号]=左括号


1. 顶部段的闭式和
设 A = 10^(L-1)，count = N - A + 1。这 count 个 L 位数拼起来的数值为：

val=
k=A
∑
N
​
 k⋅10
L(N−k)

令 a = 10^{-L}（mod 意义下），则 k·10^{L(N-k)} = (fv-rv) 经过移位。具体地，fv - rv 通过 stereotype 算出 Σ_{k=A}^{N} k·a^k，再乘 10^{L·N} 把指数翻正，就得到 val。

2. stereotype(a, modn, phin)：算术-几何级数和
它计算的是（其中 M = modn-1，a^M 的指数用 phin = (M+1) mod φ 压缩）：

G(M)=
(a−1)
2

Ma
M+1
 (a−1)−a
M+1
 +1
​

可验证 G(M)−G(M−1)=Ma
M
 ，所以 G(M)=∑
k=0
M
​
 ka
k
 +const。于是：

fv = G(N)（modn=N+1, phin=(N+1) mod φ）
rv = G(10^(L-1)-1)（modn=10^(L-1), phin=10^(L-1) mod φ）
fv - rv = Σ_{k=A}^{N} k·a^k

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int mod = 1e9+7, phi = mod - 1, N = 1e5+1e2;

int ksm(int x, int y=phi-1) {
    int z = 1;
    for (; y; y>>=1, x=1ll*x*x%mod)
        if (y&1) z = 1ll*z*x%mod;
    return z;
}

struct dat {
    int val, ten;
    dat() { val = 0, ten = 1; }
    dat(int V, int T) { val = V, ten = T; }
    friend dat operator+(const dat& u, const dat& v) {
        return dat((1ll*u.val*v.ten+v.val)%mod, 1ll*u.ten*v.ten%mod);
    }
    friend dat operator-(const dat& u, const dat& v) {
        dat w;
        w.ten = 1ll*u.ten*ksm(v.ten)%mod;
        w.val = (u.val+mod-1ll*v.val*w.ten%mod)%mod;
        return w;
    }
} f[N];

//x 重复 y 次（倍增拼接）
dat ksm(dat x, int y) {
    dat z;
    for (; y; y>>=1, x=x+x)
        if (y&1) z = z + x;
    return z;
}
int stereotype(int a, int modn, int phin) {
    int an = ksm(a, phin), ia1 = ksm((a+mod-1)%mod);
    return (1ll*(modn+mod-1)*an-1ll*(an+mod-1)*ia1%mod+mod+1)%mod*ia1%mod;
}

int msk(int x, int y) {
    int z = 1;
    for (; y; y>>=1, x=1ll*x*x%phi)
        if (y&1) z = 1ll*z*x%phi;
    return z;
}

dat conca(char *l, char *r) {
    int modn = 0, phin = 0;
    for (char *i = l; i != r; ++i)
        modn = (10ll*modn+(*i-'0'))%mod, phin = (10ll*phin+(*i-'0'))%phi;
    (++modn)%=mod, (++phin)%=phi;
    int i = r-l-1, fv = stereotype(ksm(10, phi-(i+1)), modn, phin),
    rv = stereotype(ksm(10, phi-(i+1)), ksm(10, i), msk(10, i)),
    val = 1ll*(fv+mod-rv)*ksm(ksm(10, i+1), (phin+phi-1)%phi)%mod,
    ten = ksm(ksm(10, i+1), (phin+phi-msk(10, i))%phi);
    return f[i] + dat(val, ten);
}

//把数字串 l..r 当作字面量，返回 (值 mod p, 10^len)
dat gene(char *l, char *r) {
    dat ret;
    ret.ten = ksm(10, r-l);
    while (l != r) ret.val = (10ll*ret.val+*(l++)-'0')%mod;
    return ret;
}

//d 重复 "数字串 l..r 表示的大数" 次
dat KSM(char *l, char *r, dat d) {
    static dat pov[10];
    for (int i = 1; i < 10; ++i) pov[i] = pov[i-1] + d;
    dat ret;
    while (l != r) ret = ksm(ret, 10) + pov[*(l++) - '0'];
    return ret;
}

char s[N];
int mat[N];
dat solve(int l, int r) {
    if (l >= r) return dat();//空串
    int p = l;
    while (s[p] >= '0' && s[p] <= '9') p++;//扫数字前缀
    if (p == r) return gene(s+l, s+r);//纯字面量
    //N(X)+rest
    if (s[p] == '(') return KSM(s+l, s+p, solve(p+1, mat[p])) + solve(mat[p]+2, r);
    //A + rest
    if (s[p] == '+') return gene(s+l, s+p) + solve(p+1, r);
    //A - B + rest
    if (s[p] == '-') {
        int q = p + 1;
        while (s[q] >= '0' && s[q] <= '9') q++;//q 停在 B 后的 '+'
        return (gene(s+l, s+p) + (conca(s+p+1, s+q) - conca(s+l, s+p))) + solve(q+1, r);
    }
}

int S, stk[N], tp;
int main() {
    fast;
    cin >> s; S = strlen(s);
    for (int i = 0; i < S; ++i) {
        int fv = stereotype(ksm(10, phi-(i+1)), ksm(10, i+1), msk(10, i+1)),
        rv = stereotype(ksm(10, phi-(i+1)), ksm(10, i), msk(10, i)),
        val = 1ll*(fv+mod-rv)*ksm(ksm(10, i+1), (msk(10, i+1)+phi-1)%phi)%mod,
        ten = ksm(ksm(10, i+1), (msk(10, i+1)+phi-msk(10, i))%phi);
        f[i+1] = f[i] + dat(val, ten);
    }
    for (int i = 0; i < S; ++i) {
        if (s[i] == '(') stk[++tp] = i;
        if (s[i] == ')') mat[stk[tp]] = i, mat[i] = stk[tp--];
    }
    cout << solve(0, S).val << '\n';
    return 0;
}