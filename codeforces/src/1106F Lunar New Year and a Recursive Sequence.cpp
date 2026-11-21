//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
mod = 998244353（质数 p）
_mod = mod-1 = 998244352（费马小定理的指数模数）
g = 3（模 mod 的原根）
node()：默认构造，把二维数组全部清零。
init()：对角线置 1，成为单位矩阵（前提是方阵，n==m）。
operator[]：返回第 i 行的指针，使 now[i][j] 能被当成普通二维数组用（等价于 a[i][j]），是语法糖。
now、base 两个全局矩阵。
重载 * 做矩阵乘法。a 为 n×m，b 为 m×p，结果是 n×p 的 ans。
三重循环标准乘积累加。
注意取模对象是 _mod（即 mod-1）而非 mod——这说明这个矩阵是在指数层面的群里运算（因为后面要解关于指数的方程，指数加减用 mod-1 模）。
用 1ll 防中间乘法溢出。结果矩阵存在 ans.n,ans.m
b==1 → x=0；p==1 同理直接返回 0。
m = sqrt(p)+1：分块大小。
小步（baby step）‍：枚举 j=0..m-1，把 b·a^j mod p 存入哈希表，值为 j。cur 累乘 a。
x = cur = a^m mod p。
大步（giant step）‍：令 i 从 1 到 m，cur = a^{i·m} mod p。若 cur 出现在哈希表中（即 a^{i·m} ≡ b·a^j），则 a^{i·m-j} ≡ b，所以
x=i⋅m−j，返回 i*m - mp[cur]。
找不到 return -1。
标准扩展欧几里得，求 ax + by = gcd(a,b) 的一组整数解 (x,y)，返回 gcd
用 exgcd 求 a 模 p 的乘法逆元（要求 gcd=1），负数统一到 [0,p)。
k：递推阶数。
a[0..k-1]：递推系数。
n：要算第 n 项。
m：离散对数 / 指数方程里的"值"
构造 线性递推的转移矩阵 base（方阵 k×k，伴随矩阵形式）：
base[i][i+1] = 1（i=0..k-2）：把主对角线上方的一格（第 i 行第 i+1 列）置 1，含义是"下一时刻把上一项移下来"（这是上移位矩阵构造）。
base[k-1][i] = a[k-i-1]：最末一行放递推系数（系数倒序填）。
这样 base 作用在列向量 [arr[n-1], arr[n-2], …, arr[n-k]]^T 上可得到下一组，即矩阵递推
now 是一个 k×1 列向量初始状态，now[k-1][0]=1（对应第 0 项之类的初值）。
now = base^(n-k) * now：用矩阵快速幂算出推进后的状态。
h = now[k-1][0]：取出结果向量的末位，即 递推序列的第 n 项具体数值 h（这里整个递推是在 _mod 指数群里算的）
用 BSGS 求 m 的相对原根 g 的离散对数：m = log_g(m)（即求 x 使
g^x≡m）。此时 m 的含义变成指数
d = gcd(h, _mod)。
有解条件：m % d == 0，否则输出 -1。
两边同除 d：h/d · X ≡ m/d (mod _mod/d)。
用 inv(h,_mod/d) 求 h/d 在模 _mod/d 下的逆元，乘到右边得 X ≡ m/d · inv(h/d) (mod _mod/d)（1ll*m*inv(...) 保证不溢出）。
最终 g^X mod mod 就是方程的解，用整数快速幂计算并输出
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=0; i<n; ++i)
using namespace std;

constexpr int N = 105, mod = 998244353, _mod = mod-1, g = 3;

struct node {
    int n, m, a[N][N];
    node() { memset(a, 0, sizeof(a)); }
    void init() { rep(i,n) a[i][i] = 1; }
    int* operator[](int i) { return a[i]; }
} now, base;
inline node operator*(node a, node b) {
    node ans; ans.n = a.n, ans.m = b.m;
    rep(i,a.n) rep(j,b.m) rep(l,a.m)
        ans[i][j] = (ans[i][j]+1ll*a[i][l]*b[l][j]%_mod)%_mod;
    return ans;
}
inline node ksm(node a, int b) {
    node ans; ans.n = a.n, ans.m = a.m; ans.init();
    while (b) {
        if (b&1) ans=ans*a;
        a=a*a;
        b>>=1;
    }
    return ans;
}
inline int ksm(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b&1) ans=1ll*ans*a%p;
        a=1ll*a*a%p;
        b>>=1;
    }
    return ans;
}

unordered_map<int,int> mp;
inline int solve(int a, int b, int p) {
    if (b == 1 || p == 1) return 0;
    mp.clear();
    int m = sqrt(p)+1, cur = 1;
    rep(i,m) { mp[1ll*b*cur%p] = i; cur = 1ll*cur*a%p; }
    int x = cur; cur = 1;
    for (int i = 1; i <= m; ++i) {
        cur = 1ll*cur*x%p;
        if (mp.contains(cur)) return i*m-mp[cur];
    }
    return -1;
}
inline int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    int x1, y1, d; d = exgcd(b,a%b,x1,y1); x = y1, y = x1-a/b*y1;
    return d;
}
inline int inv(int a, int p) {
    int x = 0, y = 0; exgcd(a,p,x,y);
    if (x < 0) x += p;
    return x;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int k, a[N], n, m;
int main() {
    k = rd();
    rep(i,k) a[i] = rd();
    n = rd(), m = rd(); base.n = base.m = k;
    rep(i,k-1) base[i][i+1] = 1;
    rep(i,k) base[k-1][i] = a[k-i-1];
    now.n = k, now.m = 1; now[k-1][0] = 1; now = ksm(base,n-k)*now;
    int h = now[k-1][0]; m = solve(g,m,mod);
    int d = __gcd(h,_mod);
    if (m%d != 0) { cout << "-1\n"; return 0; }
    h /= d, m /= d;
    write(ksm(g,1ll*m*inv(h,_mod/d)%(_mod/d),mod)), putchar('\n');
    return 0;
}