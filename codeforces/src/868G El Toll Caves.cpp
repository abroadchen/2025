//
// Created by Psy.C on 2026/10/5.
//
/**
line 表示一个仿射函数 f(x)=k·x+b，全部运算在模 MOD=1e9+7 下进行【结构分析】：

at(x)：计算 f(x)=kx+b。
operator+/-：仿射函数的逐项加减。
merge(F,G) = 返回复合 G(F(x))，即先作用 F 再作用 G：k = F.k·G.k，b = G.k·F.b + G.b。
getinv(F)：用模逆元求 F 的逆仿射变换（要求 k 可逆）。
qpow_l(x,e)：把仿射变换 x 重复复合 e 次（相当于 x∘x∘…，即多次迭代）。
getsum(x,e)：求仿射变换的几何级数和 ∑_{i=0}^{e} x^i（作为仿射变换返回）；对 k=1 有特判（退化为等差求和）。
核心递归 solve(n, k, A, B, F1, F2) 是一个欧几里得（辗转相除）式递归：

边界 if (!k)：把 A 的“不动点”值代入 F2 返回。
每层先按 n/k 把 getsum(A, n/k)、getsum(A, n/k-1) 复合进 F1、F2，得到新的 f1、f2；
然后构造下一层的变换 a、b；
最后递归 solve(k, n%k, ...)，并把 (n%k)·f1.b + (k−n%k)·f2.b 累加进结果。
main 中：每轮读入 n,k，先令 d=gcd(n,k) 并让 n/=d, k/=d（约分），再用 line(1,1)、line(INV2,1) 作为初始 A、B（line(1,0) 为恒等 F，INV2 = 模下的 1/2）调用递归，最后乘 qpow(n, MOD-2)（即除以 n）作为答案。 */
#include <bits/stdc++.h>
using namespace std;
constexpr int MOD = 1e9+7, INV2 = (MOD+1)>>1;

int qpow(int x, int e) {
    int ret = 1;
    for (; e; e >>= 1, x = 1ll * x * x % MOD)
        if (e & 1) ret = 1ll * ret * x % MOD;
    return ret;
}

struct line {
    int k, b;
    line() {k = b = 0;}
    line(int _k, int _b): k(_k), b(_b) {}
    int at(int x) {return (1ll * x * k + b) % MOD;}
    line operator+(const line &rhs) {return line((k + rhs.k) % MOD, (b + rhs.b) % MOD);}
    line operator-(const line &rhs) {return line((k - rhs.k + MOD) % MOD, (b - rhs.b + MOD) % MOD);}
};
line merge(line F, line G) {//G(F(x))
    return line(1ll * F.k * G.k % MOD, (1ll * G.k * F.b + G.b) % MOD);
}
line getinv(line F) {
    int iv = qpow(F.k, MOD - 2);
    return line(iv, (MOD - 1ll * iv * F.b % MOD) % MOD);
}
line qpow_l(line x, int e) {
    line res = line(1, 0);
    for (; e; e >>= 1, x = merge(x, x)) if (e & 1) res = merge(res, x);
    return res;
}
line getsum(line x, int e) {
    if (!e) return line(0, 0);
    if (x.k == 1) return line(e, 1ll * e * (e + 1) / 2 % MOD * x.b % MOD);
    line pw = qpow_l(x, e + 1) - x;
    line res; res.k = 1ll * pw.k * qpow(x.k - 1, MOD - 2) % MOD;
    res.b = 1ll * x.b * (res.k - e + MOD) % MOD * qpow(x.k - 1, MOD - 2) % MOD;
    return res;
}
int solve(int n, int k, line A, line B, line F1, line F2) {
    if (!k) {
        int E1 = 1ll * A.b * qpow((1 - A.k + MOD) % MOD, MOD - 2) % MOD;
        return F2.at(E1);
    }
    line f1 = F1 + merge(getsum(A, n / k), F2);
    line f2 = F1 + merge(getsum(A, n / k - 1), F2);
    line a = merge(getinv(B), qpow_l(getinv(A), n / k - 1));
    line b = merge(getinv(B), qpow_l(getinv(A), n / k));
    return (solve(k, n % k, a, b, line(f1.k, 0), line(f2.k, 0)) + 1ll * (n % k) * f1.b +
        1ll * (k - n % k) * f2.b) % MOD;
}

int main() {
    int qu; scanf("%d", &qu);
    while (qu--) {
        int n, k; scanf("%d%d", &n, &k); int d = __gcd(n, k); n /= d; k /= d;
        printf("%d\n", 1ll * solve(n, k, line(1, 1), line(INV2, 1),
            line(1, 0), line(1, 0)) * qpow(n, MOD - 2) % MOD);
    }
    return 0;
}