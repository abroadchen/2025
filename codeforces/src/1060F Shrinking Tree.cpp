//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
dp[now][k]（子树内）：在 now 为根的一段子树里，某种"计数/概率"关于 k 的分布。

从转移可见：

dp[now][0]=1，sz[now]=1 初始化。
tmp[i+j] += dp[now][i]·g[j]·C(i+j,i)·C(...)。
这是树上按大小合并的计数 DP，C(i+j,i)·C(...) 是合并两段有序序列的交错排列数——典型的"子树间打乱排列"计数
dp[x][j-1] 乘 0.5、dp[x][i] 乘 1，处理"合并时是否计入减半权重"的边界——这对应题目中 每次比较/方向选择有 50% 概率 的随机性（常见于"随机插入/随机比较"期望题）。

g[i] 表示合并进 now 时，孩子 x 贡献了"第 i 个位置"的累计概率质量（概率游走/随机比较的期望累加）
把当前 already-merged 子树（大小 sz[now]）与孩子子树 x 合并。
dp[now][i]：之前部分贡献 i 个"成功位"；
g[j]：孩子贡献 j 个；
组合权重 C(i+j,i) 与 C(...)：统计两种大小不同且内部有序的序列交错合并的方案数（把 now 侧 i 个元素和 x 侧 j 个元素任意交叉排列，同时考虑剩余元素），这是树上非同构子树合并的标准组合系数。
这是典型的 "树上打乱——把根结构的子树位置随机化"的计数背包 DP。
对每个节点 i，以它为根重跑一次完整 DFS，得到以 i 为根的整棵树 DP。
输出 dp[i][n-1] / fac[n-1]：fac[n-1] 是 (n-1)!，即把"打乱方案数"归一化成概率 —— 由于合并时乘了 C 组合数相当于 (sz-1)! 之类的重排计数，除以 (n-1)! 恰好把计数转成概率。
这就是题目求每个节点成为某种"首元素/根"的期望概率，对全树每点输出
*/
#include <bits/stdc++.h>
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define ld long double
using namespace std;

constexpr int N = 55;

ld fac[N];
inline ld C(int n, int m) { return fac[n]/(fac[m]*fac[n-m]); }

ld dp[N][N], g[N], tmp[N];
int sz[N];
vector<int> G[N];
void dfs(int now, int fa) {
    dp[now][0] = 1; sz[now] = 1;
    for (auto x : G[now]) {
        if (x == fa) continue;
        dfs(x, now);
        rep(i,sz[x]+1) {
            g[i] = 0;
            for (int j = 1; j <= sz[x]; j++) {
                if (j <= i) g[i] += 0.5*dp[x][j-1];
                else g[i] += dp[x][i];
            }
        }
        rep(i,sz[now]+sz[x]) tmp[i] = 0;
        rep(i,sz[now]) rep(j,sz[x]+1)
            tmp[i+j] += dp[now][i]*g[j]*C(i+j,i)*C(sz[now]-1-i+sz[x]-j,sz[now]-1-i);
        rep(i,sz[now]+sz[x]) dp[now][i] = tmp[i];
        sz[now] += sz[x];
    }
}


int main() {
    int n; cin >> n; fac[0] = 1;
    for (int i = 1; i <= n-1; i++) fac[i] = fac[i-1]*i;
    for (int i = 1, x, y; i <= n-1; i++) {
        cin >> x >> y;
        G[x].push_back(y); G[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        dfs(i, 0);
        cout << fixed << setprecision(9) << (double)(dp[i][n-1]/fac[n-1]) << '\n';
    }
    return 0;
}