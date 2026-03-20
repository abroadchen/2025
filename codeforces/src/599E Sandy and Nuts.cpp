//
// Created by Psy.C on 2026/3/20.
//
/**
N = 15：最大节点数（状态压缩限制）
M = 1e4：最大状态数
L = 105：最大约束数
in(i, s)：检查第i位是否在集合s中（返回第i位的值）
d[u][s]表示以u为终点、访问集合s的路径数量
n：节点数
e[N][N]：邻接矩阵
q：约束数量
c[L], a[L], b[L]：存储约束条件

使用引用避免重复计算
st = s-(1<<u)：去掉节点u的集合
t：找到st中第一个存在的节点（用于枚举子集的优化）
枚举st的所有子集k，且必须包含节点t（优化枚举）
k = (k-1)&st：枚举st的子集
检查子集k是否形成连通块（k内的边和k外的边）
in(i, k)^in(j, k)：i和j一个在k中一个不在k中
如果k和st-k之间有边，则不合法
cnt：u连接到k中的节点数
if (cnt >= 2) continue;：如果u连接到k中多个节点，跳过
c[i] == u && in(a[i], k) && in(b[i], k)：u为中间节点，a[i]和b[i]在两端
in(c[i], k) && (!in(a[i], k) || !in(b[i], k))：c[i]在k中，但a[i]和b[i]不全在
cnt == 1：u只连接k中的一个节点v
dfs(v, k) * dfs(u, s - k)：k中路径 + 剩余部分路径
cnt == 0：u不连接k中任何节点
枚举k中的每个节点作为连接点

ret = (1<<n) - 1：全集（包含所有节点）
d[i][1<<i] = 1：单节点路径数为1
dfs(0, ret)：计算从任意起点到节点0，访问所有节点的路径数
时间复杂度：O(n²·3ⁿ)（子集枚举） 空间复杂度：O(n·2ⁿ)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 15, M = 1e4, L = 105;

int in(int i, int s) { return s>>i&1; }

ll d[N][M];
int n, e[N][N], q, c[L], a[L], b[L];
ll dfs(int u, int s) {
    ll& ans = d[u][s];
    if (ans != -1) return ans;
    ans = 0;
    int st = s-(1<<u), t;
    for (t = 0; t < n; ++t)
        if (in(t, st)) break;
    for (int k = st; k; k = (k-1)&st) if (in(t, k)) {
        bool flag = true;
        for (int i = 0; i < n; ++i) if (i != u) {
            for (int j = 0; j < n; ++j) if (j != u) {
                if (e[i][j] && (in(i, k)^in(j, k))) {
                    flag = false;
                    break;
                }
            }
            if (!flag) break;
        }
        if (!flag) continue;
        int v = 0, cnt = 0;
        for (int i = 0; i < n; ++i)
            if (e[u][i] && in(i, k)) {
                cnt++; v = i;
            }
        if (cnt >= 2) continue;
        for (int i = 0; i < q; ++i) {
            if (c[i] == u && in(a[i], k) && in(b[i], k)) {
                flag = false; break;
            }
            if (in(c[i], k) && (!in(a[i], k) || !in(b[i], k))) {
                flag = false; break;
            }
        }
        if (!flag) continue;
        if (cnt == 1) ans += dfs(v, k) * dfs(u, s - k);
        else {
            for (v = 0; v < n; ++v) if (in(v, k))
                ans += dfs(v, k) * dfs(u, s - k);
        }
    }
    return ans;
}

int m;
int main() {
    fast;
    cin >> n >> m >> q;
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v; u--; v--;
        e[u][v] = e[v][u] = 1;
    }
    for (int i = 0; i < q; ++i) {
        cin >> a[i] >> b[i] >> c[i];
        a[i]--; b[i]--; c[i]--;
    }
    int ret = (1<<n) - 1;
    memset(d, -1, sizeof(d));
    for (int i = 0; i < n; ++i) d[i][1<<i] = 1;
    cout << dfs(0, ret) << '\n';
    return 0;
}