//
// Created by Psy.C on 2026/10/2.
//
/**
n = 2^k：参赛人数（必须是 2 的幂）。
p[i][j]：选手 i 击败选手 j 的概率（读入时除以 100，把百分比转小数）。
g[u][i]：选手 i 能从以节点 u 为根的子树所代表的那个小组中胜出（成为该组冠军）的概率。
f[u][i]：在以 u 为根的小组里，"以 i 最终胜出为条件"，整个小组比赛能获得的最大（期望）收益。
根是节点 1，覆盖 [1..n] 全体选手，构成一棵满二叉树（类似线段树的区间划分）
把区间 [l,r] 递归分成两半，分别递归到左子树 u<<1、右子树 u<<1|1
区间只有一个选手 l：他必然是该组冠军，g=1；此时该"组"里没有可再计分的比赛收益，f=0
一个选手 i 要从整组 [l,r] 胜出，必须：

先从自己的半组胜出（概率 g[u<<1][i] 或 g[u<<1|1][i]）；
在决赛中击败另一半组的冠军 j（j 从另一组胜出的概率 g[u<<1][j] 或 g[u<<1|1][j]），单场胜率 p[i][j]；
对另一半所有可能冠军 j 求和（全概率公式）。
前半循环：i 在左半（1..mid），j 在右半；

后半循环：i 在右半，j 在左半
假设选手 i 从整组胜出（冠军）。

收益由三部分构成：

g[u][i] * (r-l+1)/2：以 i 胜出的概率为权重，给整组一半人数 (r-l+1)/2 记一笔收益（这是题目设定的计分规则：每场淘汰赛的胜者从被淘汰的一半人那里得分，或类似"淘汰赛赢一场加半组价值"）。
f[左子树][i]：i 在自己半组内的收益（如果 i 在左半）。
f[右子树][j] 或 f[左子树][j]：另一半组冠军 j 在其半组内的收益。
由于 i 要和另半组的某个冠军 j 打决赛，j 的具体身份影响总收益，因此对 j 取 max——即选择"最能配出最大收益的那个对手半组冠军"结构（且 j = i 所在半组之外的）。

注意：这里的 f 是一个"条件收益期望 / 上层决策最大化"的量，max 表示在决赛对手的不确定性中取最优收益方案
读入人数指数 k，n=2^k。
读入 n×n 胜率矩阵，除以 100 转成概率。
从根跑 dfs(1,1,n) 完成整个锦标赛 DP。
对根节点枚举谁是最终冠军，取 f[1][i] 最大值作为答案，保留 10 位小数输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,a,b) for (int i=a; i<=b; ++i)
using namespace std;
constexpr int N = 1e3+10;

int n;
double f[N][N], g[N][N], p[N][N];
void dfs(int u, int l, int r) {
    if (l == r) { f[u][l] = 0; g[u][l] = 1; return; }
    int mid = (l+r) >> 1;
    dfs(u<<1, l, mid);
    dfs(u<<1|1, mid+1, r);
    rep(i,1,mid) rep(j,mid+1,n) g[u][i] += g[u<<1][i]*g[u<<1|1][j]*p[i][j];
    rep(i,mid+1,n) rep(j,1,mid) g[u][i] += g[u<<1|1][i]*g[u<<1][j]*p[i][j];
    rep(i,1,mid) rep(j,mid+1,n) f[u][i] = max(f[u][i], g[u][i]*(r-l+1)/2+f[u<<1][i]+f[u<<1|1][j]);
    rep(i,mid+1,n) rep(j,1,mid) f[u][i] = max(f[u][i], g[u][i]*(r-l+1)/2+f[u<<1|1][i]+f[u<<1][j]);
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) (x*=10) += ch&15;
    if (f) x = -x;
}

int k;
double ans;
int main() {
    fast;
    rd(k); n = 1<<k;
    rep(i,1,n) rep(j,1,n) rd(p[i][j]), p[i][j]/=100;
    dfs(1, 1, n);
    rep(i,1,n) ans = max(ans, f[1][i]);
    printf("%.10lf\n", ans);
    return 0;
}