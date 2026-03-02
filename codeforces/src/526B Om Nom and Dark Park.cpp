//
// Created by Psy.C on 2026/3/2.
//
/**
num：完全二叉树的节点总数
dp[N]：动态规划数组，存储每个节点的最优值
a[N]：输入数组，存储边权或转移成本
ans：最终答案，累计差异值

k表示当前节点编号（按完全二叉树编号）
边界条件：if (k > num) return 超出范围则返回
递归处理：dfs(k<<1); dfs(k<<1|1) 递归处理左子树(k<<1)和右子树(k<<1|1)
状态转移：dp[k] = max(...) 计算当前节点的最优值
左子树贡献：dp[k<<1] + a[(k<<1)-1]
右子树贡献：dp[k<<1|1] + a[k<<1]
差异计算：计算左右子树贡献的差值绝对值并累加到ans

计算深度为n+1的完全二叉树的节点总数
计算过程：num = 1 << (n+1) - 1，即2^(n+1) - 1

读取深度：n表示树的深度
计算节点数：调用get(n)计算num
读取边权：读取num-1个边权值到数组a
开始DFS：从根节点1开始执行DFS

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e3;
inline int sgn(const int x) {///返回整数的绝对值
    if (x >= 0) return x;
    return -x;
}

int num, dp[N], a[N], ans;
void dfs(const int k) {
    if (k > num) return;
    dfs(k<<1); dfs(k<<1|1);
    dp[k] = max(dp[k<<1] + a[(k<<1)-1], dp[k<<1|1] + a[k<<1]);
    const int t1 = dp[k<<1] + a[(k<<1)-1], t2 = dp[k<<1|1] + a[k<<1];
    ans += sgn(t1 - t2);
}

void get(const int n) {
    num = 1;
    for (int i = 1; i <= n+1; ++i) num <<= 1;
    num--;
}

int n;
int main() {
    fast;
    cin >> n; get(n);
    for (int i = 1; i < num; ++i) cin >> a[i]; dfs(1);
    cout << ans << '\n';
    return 0;
}