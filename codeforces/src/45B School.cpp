//
// Created by Psy.C on 2025/9/28.
//
/*
*N = 1e5: 最大节点数
n, m: 图的节点数和查询数
a, res: 临时变量，a用于当前节点，res用于结果
g[N]: 每个节点的后继节点数组（形成函数映射）
v[N], b[N]: 查询参数数组

 *
*p: 父节点
d: 到父节点的距离
DSU[N + 1]: 并查集数组，大小为N+1
 *
*实现路径压缩的查找操作：

如果u是根节点，直接返回
递归查找父节点
更新当前节点到根的距离（累加路径上的距离）
将当前节点直接连接到根节点（路径压缩）
 *
*将节点u连接到节点v：

设置u到v的距离为1
设置u的父节点为v

 *
*处理每个查询：

计算起始节点a = (v[i] + 上次结果 - 1) % n
对节点a执行get操作（路径压缩和距离更新）
初始化结果res为0
 *
*条件：当前节点的父节点不是n（虚拟根节点）且距离小于b[i]
步数增加：res++
对当前节点的后继节点执行get操作
合并操作：
如果当前节点父节点和后继节点的父节点相同，将其连接到虚拟根节点n
否则将其连接到后继节点
再次对a执行get操作更新状态
 *
 *
 */
#include <ios>
#include <iostream>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

const int N = 1e5;
int n, m, a, res;
int g[N], v[N], b[N];

struct Item {
    int p, d;
    Item(int p=0, int d=0) : p(p), d(d) {}
} DSU[N + 1];

void get(int u) {
    if (DSU[u].p == u) return;
    get(DSU[u].p);
    DSU[u].d += DSU[DSU[u].p].d;
    DSU[u].p = DSU[DSU[u].p].p;
}

void unite(int u, int v) {
    DSU[u].d = 1;
    DSU[u].p = v;
}

void solve() {
    cin >> n >> m;
    rep(i, n) { cin >> g[i]; g[i]--; }
    rep(i, m) cin >> v[i];
    rep(i, m) cin >> b[i];
    rep(i, n + 1) DSU[i] = Item(i);//初始化并查集：每个节点初始时父节点是自己，距离为0
    rep(i, m) {
        a = (v[i] + res - 1) % n;
        get(a);
        res = 0;
        while (DSU[a].p != n && DSU[a].d < b[i]) {
            res++;
            get(g[DSU[a].p]);
            if (DSU[a].p == DSU[g[DSU[a].p]].p)
                unite(DSU[a].p, n);
            else
                unite(DSU[a].p, g[DSU[a].p]);
            get(a);
        }
        cout << res << '\n';
    }
}




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();

    return 0;
}