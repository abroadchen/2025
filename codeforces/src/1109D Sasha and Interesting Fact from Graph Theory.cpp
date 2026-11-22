//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
快速幂 x^y mod mod，二进制逐位平方相乘。用于求逆元（费马小定理）和大指数幂。
fac[i]：阶乘 i!；inv[i]：i! 的逆元。
C(x,y)：通过阶乘和逆元 O(1) 计算
设 n = 总节点数，k = 路径上（即指定的）顶点数。
若 n == k：整棵树就是固定路径，标号方式是 fac[n]（n 个点的全排列）
否则：k*n^(n-k-1)*(n!/(n-k)!)
这是"有标号树中，恰好包含某 k 个指定定点作为特殊集合（构成一条链）"的计数：把 n 个点用 Cayley 推广法挂到
k 个指定"根"上，k * n^{n-k-1} 来自含指定节点集合的树上色/计数公式；再乘以把
n 个标号分给这 n 个位置的排列数n!/(n-k)!

读入总点数 n、要求的距离 m、两点 a、b。
注意：题目只给 a,b 用作总点数
n（即输入实际是 n,m,a,b，含义为：n 个顶点、要计数
a 到 b 距离=m 的树个数）。实际用到的只有 n 和 m，a,b 仅当作"两个已标号特殊点"（计数时除以 n² 消除它们对称性）
预计算阶乘 fac[0..t+1]，t = max(n,m) 保证覆盖所有用到范围
用 inv[t+1] = ( (t+1)! )^(mod-2) 求最大阶乘逆元，再递推回退求各阶乘逆元：inv[i] = inv[i+1]*(i+1)，即 1/i! = 1/(i+1)! * (i+1)。O(t) 求所有逆元。
i 表示 a→b 路径上除了 a、b 之外的新增顶点个数。
a 到 b距离为 m，所以路径上应有 m 条边、m+1 个节点，其中 a、b 两端 + i 个中间顶点，且
a 到 b 之间有 m−1 个"间隙"可放置。
i 的范围 [0, min(n-2, m-1)]：路径中间顶点最多 n−2（除 a,b 外）且最多 m−1。
对每个
i：C(m-1, i)：从 m−1 个边间隙中选 i 个放入新增顶点（确定路径"形状"中新增点的相对间隔分布）。
calc(n, 2+i)：计算把这 n 个点标号、只让 2+i 个指定点（a,b+新增）构成链的方式数。
ksm(m, n-1-(i+1))：剩余 n−(2+i) 个普通点，每个有
m 种"挂到路径上哪个位置"的选择（Cayley 挂树步数），且要乘……这里是
剩余点数m^剩余点数 ，来自"每个非路径点可挂在
m 个位置之一"的 Cayley 计数修正。
三者相乘即对固定 i 的计数 s，累加到 ans
最终结果 ans 乘 inv(n) 和 inv(n-1)，即除以 n(n−1)。
原因：tree a→b 与 b→a、以及 a、b 作为两个"已固定标号点"在 Cayley 计数时存在对称/重复，需要除以
n^2的两部分 n⋅(n−1) 来去掉 a、b 无序与路径正反重复。得到的就是 a、b 之间有标号树个数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e6+10, mod = 1e9+7;

int ksm(int x, int y) {
    int s = 1;
    while (y) {
        if (y&1) s = 1ll*s*x%mod;
        x = 1ll*x*x%mod;
        y >>= 1;
    }
    return s;
}

int fac[N], inv[N];
int C(int x, int y) { return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod; }
int calc(int n, int k) {
    return n == k ? fac[n] : 1ll*k*ksm(n,n-k-1)%mod*fac[n]%mod*inv[n-k]%mod;
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
inline void add(int &x, int y) { x = x+y >= mod ? x + y - mod : x + y; }

int n, m, a, b, t, ans;
int main() {
    fast;
    read(n, m, a, b); t = max(n,m); fac[0] = 1;
    for (int i = 1; i <= t+1; i++) fac[i] = 1ll*fac[i-1]*i%mod;
    inv[t+1] = ksm(fac[t+1], mod-2);
    for (int i = t; ~i; --i) inv[i] = 1ll*inv[i+1]*(i+1)%mod;
    for (int i = 0; i <= min(n-2,m-1); i++) {
        int s = 1ll*C(m-1,i)*calc(n,2+i)%mod*ksm(m,n-1-(i+1))%mod;
        add(ans,s);
    }
    cout << 1ll*ans*ksm(n,mod-2)%mod*ksm(n-1,mod-2)%mod << '\n';
    return 0;
}