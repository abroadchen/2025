//
// Created by Psy.C on 2026/4/1.
//
/**
dp[i][j]表示节点i在深度j的概率
q: 查询次数
n: 当前节点数
p[N+5]: 父节点数组
dep[N+5]: 深度数组

读入查询次数，初始化节点数n为1
读入操作类型op和节点u
创建新节点v（n自增），设置v的父节点为u
从节点u开始向上更新
t1 = dp[cur][0]*0.5+0.5: 计算当前节点的概率调整因子
循环更新到第49层祖先（或到根节点）
dp[p[cur]][i] /= t1: 调整父节点的概率值
逐层向上更新
更新u节点的dp[0]值（乘以0.5）
从u开始向上更新所有祖先节点的dp值
dp[p[cur]][i] *= 0.5+0.5*dp[cur][i-1]: 更新概率值，考虑子节点的影响
ans = dep[u]: 初始化为节点u的实际深度
ans += i*(dp[u][i]-dp[u][i-1]): 累加概率加权的深度贡献
时间复杂度约为O(q × 50)，空间复杂度为O(N × 50)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5;

double dp[N+5][51];
int q, n, p[N+5], dep[N+5];
int main() {
    fast;
    for (int i = 1; i <= N; ++i)
        for (int j = 0; j <= 50; ++j)
            dp[i][j] = 1.;
    cin >> q; n++;
    while (q--) {
        int op, u; cin >> op >> u;
        if (op == 1) {
            int v = ++n; p[v] = u;
            int cur = u;
            double t1 = dp[cur][0]*0.5+0.5, t2;
            for (int i = 1; i < 50 && p[cur]; i++) {
                t2 = dp[p[cur]][i]*0.5+0.5;
                dp[p[cur]][i] /= t1;
                cur = p[cur];
                t1 = t2;
            }
            dp[u][0] *= 0.5;
            cur = u;
            for (int i = 1; i <= 50 && p[cur]; i++) {
                dp[p[cur]][i] *= 0.5+0.5*dp[cur][i-1];
                cur = p[cur];
            }
        } else {
            double ans = dep[u];
            for (int i = 1; i <= 50; i++)
                ans += i*(dp[u][i]-dp[u][i-1]);
            printf("%.12f\n", ans);
        }
    }
    return 0;
}