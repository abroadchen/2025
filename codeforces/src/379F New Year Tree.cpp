//
// Created by Psy.C on 2026/1/25.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2000010
using namespace std;

struct node { int to, nxt; } e[N];

int tot, head[N];//边的总数 邻接表头指针数组
void add(const int u, const int v) {
    //增加新边，目标为v 新边指向u的原有第一条边 更新u的头指针为新边
    e[++tot].to = v; e[tot].nxt = head[u]; head[u] = tot;
}

int dep[N], c[N][21];//节点x向上2^i步的祖先
void dfs(const int x, const int fa) {
    dep[x] = dep[fa] + 1;//当前节点深度
    c[x][0] = fa;//直接父节点 向上跳2^0=1步的祖先
    //x向上跳2^(i-1)步后再向上跳2^(i-1)步
    for (int i = 1; i < 21; ++i) c[x][i] = c[c[x][i-1]][i-1];//建立倍增表
    for (int i = head[x]; i; i = e[i].nxt) {//i不为0时继续（0表示没有更多边）
        if (e[i].to == fa) continue;
        dfs(e[i].to, x);//当前节点x成为子节点的父节点
    }
}

int lca(int x, int y) {//查找x和y的最近公共祖先 公共祖先的节点编号
    if (dep[x] != dep[y]) {
        if (dep[x] < dep[y]) swap(x, y);
        const int d = dep[x] - dep[y];
        for (int i = 0; i < 21; ++i)
            if (d & (1<<i)) x = c[x][i];//深度差的第i位为1，x向上跳2^i步
    }
    if (x == y) return x;//y是x的祖先
    for (int i = 20; i >= 0; --i) if (c[x][i] != c[y][i]) {//向上跳2^i步后到达不同节点
        x = c[x][i]; y = c[y][i];//同时向上跳2^i步
    }
    return c[x][0];//返回x的父节点
}

int main() {
    fast;
    add(1, 2); add(1, 3); add(1, 4);//添加固定的三条边
    //当前节点编号 查询次数 两个特殊节点 当前最长距离
    int cnt = 4, q, d1 = 2, d2 = 3, len = 2;
    cin >> q; dfs(1, 1);
    for (int i = 1, x; i <= q; ++i) {
        cin >> x;//本次查询的节点
        add(x, ++cnt); add(x, ++cnt); dfs(x, c[x][0]);// 从节点x开始重新DFS，父节点是x的直接父节点
        const int l1 = lca(x, d1), l2 = lca(x, d2),
        len1 = dep[x] + dep[d1] - (dep[l1]<<1),
        len2 = dep[x] + dep[d2] - (dep[l2]<<1);
        if (len1 + 1 <= len && len2 + 1 <= len) cout << len << '\n'; else {
            if (len1 > len2) {
                len = len1 + 1;
                cout << len << '\n';
                d2 = cnt;//更新d2为最新添加的节点
            } else {
                len = len2 + 1;
                cout << len << '\n';
                d1 = cnt;
            }
        }
    }
    return 0;
}