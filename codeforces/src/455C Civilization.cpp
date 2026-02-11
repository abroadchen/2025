//
// Created by Psy.C on 2026/2/11.
//
///时间复杂度约为 O(nα(n) + m + q) 其中 α 是阿克曼函数的反函数
#include <iostream>
#include <vector>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 300005
using namespace std;

int fa[N];
inline int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
inline void uni(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    fa[x] = y;
}
//两个节点是否在同一连通分量中
inline bool ok(const int x, const int y) { return find(x) == find(y); }

int n, m, t;
vector<int> e[N];
void init() {
    cin >> n >> m >> t;//节点数 边数 查询次数
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        e[x].push_back(y); e[y].push_back(x);
        uni(x, y);//合并节点到同一集合
    }
}

int mx;

/**
 *
 * @param now 当前节点
 * @param p 父节点（避免走回头路）
 * @param nd 当前深度
 * @param v 存储最远节点
 */
void dfs(const int now, const int p, const int nd, int& v) {
    if (nd > mx) { mx = nd; v = now; }
    for (int i = 0; i < e[now].size(); ++i) {
        if (const int to = e[now][i]; to != p)
            dfs(to, now, nd+1, v);
    }
}

///op: 第一次 DFS 找到的最远节点
///ed: 直径的终点
///d[N]: 存储每个连通分量的直径长度
int op, ed, d[N];
int main() {
    fast;
    init();
    for (int i = 1; i <= n; ++i) if (find(i) == i) {
        mx = -1;
        dfs(i, -1, 0, op);//从任意点出发找到最远点 op
        mx = -1;
        dfs(op, -1, 0, ed);//从 op 出发找到最远点 ed，距离就是直径
        d[i] = mx;
    }
    int opt, x, y;
    while (t--) {
        cin >> opt;
        if (opt == 1) {
            cin >> x;
            cout << d[find(x)] << '\n';//节点 x 所在连通分量的直径
        } else {
            cin >> x >> y;
            if (!ok(x, y)) {
                ///新直径 = max(旧直径1, 旧直径2, ceil(直径1/2) + ceil(直径2/2) + 1)
                d[find(y)] = max(max(d[find(x)], d[find(y)]),
                    static_cast<int>(ceil(d[find(x)]/2.)+ceil(d[find(y)]/2.)+1));
                uni(x, y);
            }
        }
    }
    return 0;
}