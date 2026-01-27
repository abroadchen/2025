//
// Created by Psy.C on 2026/1/28.
//
/**
* n: 矩阵大小
a[N][N]: 邻接矩阵
vis[N]: 访问标记数组
match[N]: 匹配数组
 *
*匈牙利算法的DFS部分
尝试为节点u寻找增广路径
遍历所有相邻节点i
如果i未访问且未匹配或能重新匹配，更新匹配关系
 *
*m: 边的数量
x[M], y[M]: 存储边的端点
重新构建邻接矩阵
 *
*tot: 不在第u行/列的边数
ans: 第u行/列中需要添加的边数
清空第u行/列的边
*初始化匹配数组
对除u外的每个节点执行DFS寻找匹配
统计匹配数量
*n - 1 - cnt: 无法匹配的节点数
tot - cnt: 未被匹配覆盖的边数
总操作数 = 需要添加的边数 + 未匹配节点数 + 未覆盖边数
 *
*尝试删除每一行/列
取最小操作数
 *
*时间复杂度
外层循环：O(n)
每次匹配：O(n³)（匈牙利算法）
总体：O(n⁴)
空间复杂度
O(n²)，用于存储邻接矩阵
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 600
#define M 4545
#define inf 0x3f3f3f3f
using namespace std;

int n, a[N][N], vis[N], match[N];
int dfs(const int u) {
    for (int i = 1; i <= n; ++i) if (a[u][i] == 1 && vis[i] == 0) {
        vis[i] = 1;
        if (match[i] == -1 || dfs(match[i])) {
            match[i] = u;
            return 1;
        }
    }
    return 0;
}

int m, x[M], y[M];
int get(const int u) {
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= m; ++i) a[x[i]][y[i]] = 1;
    int ans = 0, tot = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        if (a[i][j] == 1 && i != u && j != u) tot++;
        if (a[i][j] == 0 && (i == u || j == u)) ans++;
        if (i == u || j == u) a[i][j] = 0;
    }
    memset(match, -1, sizeof(match));
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        if (i == u) continue;
        if (dfs(i)) cnt++;
    }
    ans += n - 1 - cnt;
    ans += tot - cnt;
    return ans;
}


int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) cin >> x[i] >> y[i];
    int ans = inf;
    for (int i = 1; i <= n; ++i) {
        int t = get(i);
        ans = min(ans, t);
    }
    cout << ans << '\n';
    return 0;
}