//
// Created by Psy.C on 2026/3/10.
//
/**
cnt: 非特殊节点的数量
g[N]: 标记节点是否在当前考虑集合中
c[N]: 存储非特殊节点
deg[N]: 节点度数
in[N]: 节点入度（在当前剩余图中）
ir[N]: 被特殊节点影响的度数
ans[N]: 存储结果节点
v[N]: 邻接表存储图

num: 当前剩余节点数
初始化：将所有非特殊节点标记为在集合中
计算初始入度（总度数减去被特殊节点影响的度数）
将满足条件 in[i]/deg[i] < x 的节点加入队列
这些节点的安全度低于阈值x，需要删除
拓扑排序过程：删除节点now会影响其邻居
对每个邻居减少入度，如果安全度仍低于x则继续删除
如果还有剩余节点，说明存在满足条件的集合
将剩余节点存入ans数组并返回true

n个节点，m条边，k个特殊节点
b[x] = 1 标记节点x为特殊节点
构建无向图的邻接表
统计每个节点的度数
如果x是特殊节点，则y受到x的影响（ir[y]++）
二分搜索：在[0,1]范围内搜索最大安全度阈值
将所有非特殊节点存入c数组
二分迭代100次达到所需精度
输出结果：剩余节点数量及具体节点编号

二分搜索：O(log(1/ε))
每次check：O(n + m)
总时间复杂度：O((n+m) × log(1/ε))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-8
using namespace std;
constexpr int N = 1e5+5;

int cnt, g[N], c[N], deg[N], in[N], ir[N], ans[N];
vector<int> v[N];
bool check(const double x) {
    int num = cnt;
    queue<int> q;
    for (int i = 1; i <= cnt; ++i) g[c[i]] = 1;
    for (int i = 1; i <= cnt; ++i) in[c[i]] = deg[c[i]] - ir[c[i]];
    for (int i = 1; i <= cnt; ++i) {
        if ((double)in[c[i]]/(double)deg[c[i]] < x) {
            q.push(c[i]);
            g[c[i]] = 0;
            --num;
        }
    }
    while (!q.empty()) {
        const int now = q.front(); q.pop();
        for (auto u : v[now]) if (g[u]) {
            --in[u];
            if ((double)in[u]/(double)deg[u] < x) {
                q.push(u);
                g[u] = 0;
                --num;
            }
        }
    }
    if (num) {
        int tot = 0;
        for (int i = 1; i <= cnt; ++i) if (g[c[i]])
            ans[++tot] = c[i];
        ans[0] = num;
        return true;
    }
    return false;
}

int n, m, k, b[N];
int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1, x; i <= k; ++i) {
        cin >> x; b[x] = 1;
    }
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        v[x].push_back(y); v[y].push_back(x);
        ++deg[x], ++deg[y];
        if (b[x]) ++ir[y];
        if (b[y]) ++ir[x];
    }
    double l = 0., r = 1.;
    for (int i = 1; i <= n; ++i) if (!b[i]) c[++cnt] = i;
    for (int i = 1; i <= 100; ++i) {
        if (const double mid = (l + r) / 2; check(mid)) l = mid;
        else r = mid - eps;
    }
    cout << ans[0] << '\n';
    for (int i = 1; i <= ans[0]; ++i) cout << ans[i] << ' ';
    return 0;
}