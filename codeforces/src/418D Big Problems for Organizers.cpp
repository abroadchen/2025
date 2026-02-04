//
// Created by Psy.C on 2026/2/3.
//
/**
* mxl: 记录最大距离
mx: 记录最远点
fa[N]: 父节点数组
vis[N]: 访问标记数组
to[N]: 邻接表存储树结构
 *
*寻找从now开始的最远节点
参数：当前节点now、父节点ff、距离dis
如果当前距离大于记录的最大距离，则更新mxl和mx
设置当前节点的父节点为ff
遍历邻接节点，递归调用DFS（避免回到父节点和已访问节点）
 *
*t1[22][N]是ST表（Sparse Table）的第一维
query函数实现区间最大值查询，使用RMQ算法
如果左边界大于右边界，返回负无穷
计算区间长度的对数，查询对应范围内的最大值
 *
*从节点1开始DFS找到最远点d1（直径一端）
从d1开始DFS找到最远点d2（直径另一端）
*从直径终点d2回溯到起点d1，记录路径
标记路径上所有节点为已访问
a数组存储直径上的节点序列，an是节点总数
mp映射节点到其在直径上的位置索引
 *
*对直径上每个节点进行DFS，计算以其为根的子树最大深度
t1[0][i] = mxl + i：考虑节点在直径上的位置
t2[0][i] = mxl + an - i：考虑节点到直径末端的距离
建立节点到直径位置的映射
 *
*构建两维ST表，支持O(1)区间最大值查询
使用倍增的思想构建表
*对每个查询的两个点x,y：
向上移动直到到达直径上的点，记录移动步数
将节点转换为其在直径上的索引
 *
*确保x ≤ y
如果两点在同一直径节点上，调整距离
计算通过不同路径到达目标点的距离
 */
#include <iostream>
#include <vector>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;

int mxl, mx, fa[N], vis[N];
vector<int> to[N];
void dfs(const int now, const int ff, const int dis) {
    if (dis > mxl) mxl = dis, mx = now; fa[now] = ff;
    for (const int v : to[now]) if (v != ff && !vis[v])
        dfs(v, now, dis + 1);
}

constexpr int inf = 1e9;
int t1[22][N];
int query(const int l, const int r) {
    if (l > r) return -inf;
    const int k = static_cast<int>(log2(r - l + 1));
    return max(t1[k][l], t1[k][r-(1<<k)+1]);
}

int t2[22][N];
int query2(const int l, const int r) {
    if (l > r) return -inf;
    const int k = static_cast<int>(log2(r - l + 1));
    return max(t2[k][l], t2[k][r-(1<<k)+1]);
}


int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        to[u].push_back(v); to[v].push_back(u);
    }
    int d1, d2;
    dfs(1, 0, 0), d1 = mx, mxl = 0;
    dfs(d1, 0, 0), d2 = mx;
    int t = d2, a[N], an = 0, mp[N];
    while (t != d1) vis[t] = 1, a[++an] = t, t = fa[t];
    vis[d1] = 1, a[++an] = d1;
    for (int i = 1; i <= an; ++i) mxl = 0, dfs(a[i], 0, 0),
        t1[0][i] = mxl + i, t2[0][i] = mxl + an - i, mp[a[i]] = i;
    for (int k = 1; k < 20; ++k) for (int i = 1; i+(1<<k)-1 <= an; ++i) {
        t1[k][i] = max(t1[k-1][i], t1[k-1][i+(1<<(k-1))]);
        t2[k][i] = max(t2[k-1][i], t2[k-1][i+(1<<(k-1))]);
    }
    int m; cin >> m;
    while (m--) {
        int x, y, xl = 0, yl = 0; cin >> x >> y;
        while (!vis[x]) x = fa[x], xl++; x = mp[x];
        while (!vis[y]) y = fa[y], yl++; y = mp[y];
        if (x > y) swap(x, y), swap(xl, yl);
        if (x == y) xl = yl = min(xl, yl);
        int ans = max(min(xl + x - 1, yl + y - 1), min(yl + an - y, xl + an - x));
        const int res = (x + y + yl - xl) >> 1;
        ans = max(ans, max(xl + query(x + 1, res) - x,
                           yl + query2(res + 1, y - 1) - (an - y)));
        cout << ans << '\n';
    }
    return 0;
}