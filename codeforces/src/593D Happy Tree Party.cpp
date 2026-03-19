//
// Created by Psy.C on 2026/3/19.
//
/**
存储每个节点的深度
邻接表，存储树的边，每个元素为{相邻节点, 边的ID}
存储每个节点的父节点和连接边的ID，格式为{父节点, 边ID}

深度优先搜索，建立树结构
设置当前节点的深度为父节点深度+1
遍历当前节点的所有邻居
获取邻居节点y和边ID
跳过父节点（避免回溯）
记录y的父节点和边ID
递归访问子节点

并查集数组，用于路径压缩
存储每条边的权重
查找路径上权重不为1的最近祖先
获取到父节点的边ID
如果边权重不为1，返回当前节点
路径压缩
继续向上查找

向上移动一个节点，同时更新z值
获取父节点和边ID
如果边权重大于1
z除以边权重
返回父节点
否则返回路径压缩后的祖先

从x到y的路径查询函数
当z不为0且x≠y时循环
确保x更深，便于向上移动
x向上移动一步，同时更新z
返回最终的z值

if (op == 1)：查询操作，调用get函数
else：更新操作，更新第x条边的权重为y

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 2e5+5;

int dep[N];
vector<ii> v[N];
ii pre[N];
void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    for (int i = 0; i <= v[x].size()-1; ++i) {
        int y = v[x][i].first, id = v[x][i].second;
        if (y == fa) continue;
        pre[y] = {x, id};
        dfs(y, x);
    }
}

int f[N];
ll w[N];
int dfs2(int x) {
    int id = pre[x].second;
    if (w[id] != 1) return x;
    if (f[x] == x) return f[x] = dfs2(pre[x].first);
    return f[x] = dfs2(f[x]);
}

int up(int x, ll& z) {
    int t = pre[x].first, id = pre[x].second;
    if (w[id] > 1) {
        z /= w[id];
        return t;
    }
    return f[x] = dfs2(f[x]);
}

ll get(int x, int y, ll z) {
    while (z && x != y) {
        if (dep[x] < dep[y]) swap(x, y);
        x = up(x, z);
    }
    return z;
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, x, y; i <= n-1; ++i) {
        cin >> x >> y >> w[i];
        v[x].emplace_back(y, i);
        v[y].emplace_back(x, i);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1, op; i <= m; ++i) {
        cin >> op;
        if (op == 1) {
            int x, y; ll z;
            cin >> x >> y >> z;
            cout << get(x, y, z) << '\n';
        } else {
            int x; ll y; cin >> x >> y;
            w[x] = y;
        }
    }
    return 0;
}