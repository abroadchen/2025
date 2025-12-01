//
// Created by Psy.C on 2025/11/30.
//
/*
*n：节点数量
k：边的数量
t：目标方案数阈值
e[N][N]：邻接矩阵，存储图的边和权重
vis[M]：访问标记数组
cnt：计数器，记录满足条件的方案数
 *
*pos：当前处理的位置/节点
sum：当前累计的权重和
mid：当前二分查找的中间值（权重上限）
*如果处理完所有位置（pos > n），说明找到一种有效方案
将计数器cnt加1，然后返回
 *不选择任何节点的分支（跳过当前位置）
 *遍历所有可能的节点，同时进行剪枝优化（当方案数已达阈值时停止）
*!vis[i]：节点i未被访问过
e[pos][i]：从位置pos到节点i存在边（权重不为0）
sum + e[pos][i] <= mid：加上这条边后总权重不超过限制
 *
*如果找到的方案数达到或超过阈值：
缩小右边界
更新答案
 *时间复杂度约为O(log(n*C) × n!)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 25, M = 50, C = 1e3;
int n, k, t, e[N][N], vis[M], cnt;

void dfs(const int pos, const int sum, const int mid) {
    if (pos > n) { cnt++; return; }
    dfs(pos + 1, sum, mid);
    for (int i = 1; i <= n && cnt < t; ++i) {
        if (!vis[i] && e[pos][i] && sum + e[pos][i] <= mid) {
            vis[i] = 1;
            dfs(pos + 1, sum + e[pos][i], mid);//递归处理下一个位置，累计权重
            vis[i] = 0;
        }
    }
}

int main() {
    fast;
    cin >> n >> k >> t;
    for (int i = 1, x, y, z; i <= k; ++i) {
        cin >> x >> y >> z;
        e[x][y] = z;
    }
    int l = 0, r = n * C, ans = 0;//右边界（最大可能的权重和）
    while (l <= r) {
        const int mid = (l + r) >> 1; cnt = 0;
        for (auto& x : vis) x = 0;
        dfs(1, 0, mid);//从位置1开始DFS，初始权重和为0，限制为mid
        if (cnt >= t) { r = mid - 1; ans = mid; }
        else l = mid + 1;
    }
    cout << ans << '\n';
    return 0;
}