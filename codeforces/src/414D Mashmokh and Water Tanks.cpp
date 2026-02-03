//
// Created by Psy.C on 2026/2/3.
//
/**
* to[]：边的目标节点
nxt[]：同一起点的下一条边
head[]：每个节点的第一条边
cnt：边的计数器
*d[N]：节点的深度（相对于根节点1）
mp[N]：每个深度的节点数量统计
 *m（节点数），k（最大选择数），p（最大代价）
 *
 *从节点1开始，计算所有节点的深度
 *滑动窗口算法，用于找到满足条件的最大连续子数组
 *cost计算：调整这些节点到相同深度的代价
*约束条件：
cost <= p（总代价不超过p）
r - l + 1 <= k（选择节点数不超过k）
*扩展右边界：r++
更新代价：如果新深度不同，增加 r-l 的代价
收缩左边界：当违反约束时，减少代价并移动左边界
更新答案：记录最大窗口大小
 *
 *时间复杂度：O(m log m)（主要是排序）
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int to[N<<1], nxt[N<<1], head[N], cnt;
void add(const int u, const int v) {
    to[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}

int d[N], mp[N];
void dfs(const int fa, const int u) {
    d[u] = d[fa] + 1;
    mp[d[u]]++;
    for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i]) {
        if (v == fa) continue;
        dfs(u, v);
    }
}

int main() {
    fast;
    int m, k, p; cin >> m >> k >> p;
    for (int i = 1, u, v; i < m; ++i) {
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    dfs(0, 1);
    sort(d + 1, d + m + 1);
    int l = 2, r = 2, ans = 1, cost = 0;
    while (l < m && r < m) {
        r++;
        if (d[r] != d[r-1]) cost += r - l;
        while (cost > p || r - l + 1 > k) {
            cost -= d[r] - d[l];
            ++l;
        }
        ans = max(ans, r - l + 1);
    }
    cout << ans;
    return 0;
}