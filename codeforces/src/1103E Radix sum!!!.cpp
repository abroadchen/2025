//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
一个 node 是长度为 k（=10）的系数数组 a[11]，表示一个次数 < k 的多项式（或一个 10 维向量）。
node():a(){}：默认构造全 0。
下标运算符重载（const 只读版 / 可写版）
向量逐位相加
向量整体乘一个标量（y 是 unsigned long long，自然溢出取模）
循环卷积（循环多项式乘法）‍：
两个次数 < k 的多项式普通卷积得到次数 < 2k 的结果 a[]（先用静态数组 a[30] 存，逐项
x[i]⋅y[j] 累加到 a[i+j]）。
然后把 a[i] 与 a[i+k] 相加（即次数 ≥ k 的部分回卷到低位），实现模 t^k-1
的循环卷积。因为 k=10 且用 10 次单位根，这个变换域里的乘法就是逐点循环卷积
向量逐位相加（友元重载，供译码用）
apply(x)：把向量循环右移 x 位（正向旋转）。用于正向变换时乘单位根
w^x的效果：在 DFT 变换域，乘以
w^(j*u)相当于把位置旋转。
iapply(x)：循环左移（逆向旋转），即 apply 的逆操作，用于逆变换
全局 T：单位根模板向量（init 里初始化）。
ct[]：规模 N 的数组，存每个数对应的初始向量（出现次数）。
m：维度数（=5）。
lim：总状态数 = 10^5(pw[m]）。
pw[i] = 10^i，即各维的"步长"
三重循环遍历 m 个维度。外层 i 是当前处理的维度，内层分成每个"块"做长度为 k 的变换。
a 从 0 跳到 pw[i+1]（即每 10^(i+1)个位置为一组块）。
b 遍历块内的 pw[i] 个起始点，即当前维的 10 个位置
取出当前维的 10 个元素（位置 a+b+j*pw[i]，j 是当前维的 0..9 下标）存到 x[]，y[] 清零做输出缓冲
对每个输出位置 j，累加所有输入 x[u] 乘以单位根因子 w^(j*u)
apply(j*u) 就是乘上单位根：在变换域就等于给系数做 j*u 的旋转。即：
Yj=∑uXuW^(ju)
 ，式中乘法用 x[u].apply(j*u)（模 t^k−1 单位根的循环位移）表示
写回。
这层循环整体就是长度为 k 的点 DFT（用 10 次单位根）‍，沿当前维度做，遍历完全部 m 个维度即为多维 FWHT（等价于 10 进制逐维 FWT）
与 dwt 完全对称，只是把 apply（正向单位根）换成 iapply（逆单位根），即用
w^-(ju)
 。这实现逆 DFT。逆变换通常还要除以长度 k，但这里借助初 iv5 在 get 里处理
构造一个多项式 T(t)=1-t+t^2-t^3+t^4
对向量 x 做多项式长除法取模，逐步消去次数 ≥ n 的项（n=4）：
从最高次 k-1 往下到 n，每次取最高项系数 u，用它消除，把 u*T[n-j] 减到低位项 x[i-j]。
结果 x 变为一个次数 < n（<4）的多项式，且模的是由 T 决定的多项式环。这是把变换域值投影到某个模约化空间。
取常数项 x[0]，乘上 iv（来自 iv5^m，即
5^−m mod 2^64 ），再右移 m 位。
iv = ksm(iv5, m)。因每维逆变换需除以 10？不——这里是除以
5^m。右移 m 位即除以
2^m（此处 m=5，右移 5 位）。
计算得最终答案标量，取模
2^58输出（可能题目答案范围在
2^58内，或防符号溢出）。
即：还原过程 = 除以
5^5并去掉 2^5因子，得到真正计数结果
node 版：在变换域把每个 ct[i] 自乘 n 次

设置 k=10（进制）、m=5（维度/位数上限），初始化 pw（10^i），lim=10^5。
iv：预处理逆缩放常数
5^-5mod2^64
读入 n 个数，ct[x][0]++：把值为 x 的数的第 0 位计数加 1（构造初始向量：每个数值 x 对应一个"只在位置 0"有系数的 indicator 向量，值为该 x 出现的次数）。
对整组 ct 做多维正向 FWHT（转换到变换域）。
变换域里每个点自幂 n 次 —— 因为卷积定理：时域自卷 n 次 ⟺ 频域逐点 n 次幂。所以
(dft(ct))^n的逆 DFT 就是原序列自卷积 n 次的结果。
逆变换回时域。
init() 初始化单位根模板 T（只需在 get 前设置一次）。
对前 n 个位置调用 get，还原出最终计数并逐行输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define int unsigned long long
using namespace std;

constexpr int N = 1e5+10, iv5 = 14757395258967641293ull;

int k;
struct node {
    int a[11];
    node():a(){}
    int operator[](int x) const { return a[x]; }
    int& operator[](int x) { return a[x]; }
    void operator+=(node const &x) { rep(i,k) a[i] += x[i]; }
    void operator*=(int y) { rep(i,k) a[i] *= y; }
    friend node operator*(node const &x, node const &y) {
        static int a[30]; node ans{};
        rep(i,k+k) a[i] = 0;
        rep(i,k) rep(j,k) a[i+j] += x[i]*y[j];
        rep(i,k) ans[i] = a[i] + a[i+k];
        return ans;
    }
    friend node operator+(node const &x, node const &y) {
        node ans{};
        rep(i,k) ans[i] = x[i] + y[i];
        return ans;
    }
    node apply(int x) const {
        x %= k; node ans{};
        rep(i,k) ans[(i+x)%k] = a[i];
        return ans;
    }
    node iapply(int x) const {
        x %= k; x = (k-x)%k; node ans{};
        rep(i,k) ans[(i+x)%k] = a[i];
        return ans;
    }
} T, ct[N];

int m, lim, pw[10];
void dwt(node *c) {
    rep(i,m) for (int a = 0; a < lim; a += pw[i+1]) rep(b,pw[i]) {
        static node x[11], y[11];
        rep(j,k) x[j] = c[a+b+j*pw[i]], y[j] = node();
        rep(j,k) rep(u,k) y[j] += x[u].apply(j*u);
        rep(j,k) c[a+b+j*pw[i]] = y[j];
    }
}
void idwt(node *c) {
    rep(i,m) for (int a = 0; a < lim; a += pw[i+1]) rep(b,pw[i]) {
        static node x[11], y[11];
        rep(j,k) x[j] = c[a+b+j*pw[i]], y[j] = node();
        rep(j,k) rep(u,k) y[j] += x[u].iapply(j*u);
        rep(j,k) c[a+b+j*pw[i]] = y[j];
    }
}
void init() { T[0] = 1, T[1] = -1ull, T[2] = 1, T[3] = -1ull, T[4] = 1; }

int iv;
int get(node x) {
    int n = 4;
    for (int i = k-1; i >= n; i--) {
        int u = x[i];
        for (int j = 1; j <= n; j++) x[i-j] -= u*T[n-j];
    }
    int u = x[0]; u *= iv; u>>=m;
    return u%(1ull<<58);
}
int ksm(int x, int y) {
    int res = 1;
    while (y) {
        if (y&1) res *= x;
        x *= x;
        y >>= 1;
    }
    return res;
}
node ksm(node x, int y) {
    node res{}; res[0] = 1;
    while (y) {
        if (y&1) res=res*x;
        x=x*x, y>>=1;
    }
    return res;
}

int n;
signed main() {
    fast;
    k = 10, m = 5; pw[0] = 1;
    for (int i = 1; i <= m; i++) pw[i] = pw[i-1]*k;
    lim = pw[m], iv = ksm(iv5, m);
    cin >> n;
    for (int i = 1, x; i <= n; i++) { cin >> x; ++ct[x][0]; }
    dwt(ct);
    rep(i,lim) ct[i] = ksm(ct[i],n);
    idwt(ct); init();
    rep(i,n) cout << get(ct[i]) << '\n';
    return 0;
}