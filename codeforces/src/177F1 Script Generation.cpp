//
// Created by Psy.C on 2025/11/30.
//
/*
*cnt: 边的计数器
head[N]: 每个节点的第一条边在邻接表中的位置
nxt[N]: 下一条边的索引（链式前向星结构）
ve[N]: 边的终点
ed[N]: 边的权重或代价
 *
 *起点u，终点v，权重c
*++cnt：增加边计数器
nxt[cnt] = head[u]：将新边链接到原有边链表
ve[cnt] = v：设置边的终点
ed[cnt] = c：设置边的权重
head[u] = cnt：更新节点u的第一条边为当前边
 *
*dep: 当前深度或处理到第几个节点
sum: 当前累计的权重和
x: 限制条件（最大允许的权重和）
 *如果当前权重和超过限制，返回0
 *如果处理完所有节点，返回1（找到一种有效方案）
 *不选择当前节点的方案数
 *遍历从当前节点出发的所有边
 *获取边的终点u和权重v
 *如果已找到足够多的方案，跳过后续计算
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 405
#define inf 20005
using namespace std;

int n, k, t;

int cnt, head[N], nxt[N], ve[N], ed[N];
void add(const int u, const int v, const int c) {
    nxt[++cnt] = head[u]; ed[cnt] = v; ve[cnt] = c; head[u] = cnt;
}

int vis[N];
int dfs(const int dep, const int sum, const int x) {
    if (sum > x) return 0;
    if (dep == n + 1) return 1;
    int ans = dfs(dep + 1, sum, x);//不选择当前节点的方案数
    for (int i = head[dep]; i; i = nxt[i]) {
        const int u = ed[i], v = ve[i];
        if (ans >= t) continue;//如果已找到足够多的方案，跳过后续计算
        if (vis[u]) continue;
        vis[u] = 1;
        ans += dfs(dep + 1, sum + v, x);//递归计算选择当前边的方案数并累加
        vis[u] = 0;//回溯，取消标记
    }
    return ans;
}

bool ok(const int x) {//检查限制条件x是否可行
    if (dfs(1, 0, x) >= t) return true;//找到至少t种方案
    return false;
}

int main() {
    fast;
    cin >> n >> k >> t;
    for (int i = 1, x, y, z; i <= k; ++i) {
        cin >> x >> y >> z;
        add(x, y + n, z);//终点偏移n 二分图节点编号
    }
    int l = 0, r = inf, ans = -1;
    while (l <= r) {
        const int mid = (l + r) >> 1;
        if (ok(mid)) r = mid - 1, ans = mid;//如果mid可行，尝试更小的值，并更新答案
        else l = mid + 1;//如果mid不可行，需要更大的值
    }
    cout << ans;
    return 0;
}