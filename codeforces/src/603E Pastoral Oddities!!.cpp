//
// Created by Psy.C on 2026/3/21.
//
/**
u, v: 边的两个端点
w: 边的权重
id: 边的原始编号
按权重排序的比较函数
tot: 栈顶指针
st[N]: 操作栈，记录合并的节点
sz[N]: 每个连通分量的大小
num: 大小为奇数的连通分量个数
erase(x): 撤销到第x个操作的状态
按秩合并的并查集操作
维护奇数大小连通分量的计数

时间复杂度
整体二分：O(M log M)
每次并查集操作：O(α(N))
总体：O(M log M × α(N))
空间复杂度
O(N + M)：存储图结构和辅助数组


res = R + 1: 初始化临界点为R+1（如果没有找到满足条件的点）
nw2 = tot: 记录当前操作栈位置
遍历查询e[L..R]，添加权重≤b[mid].w的边
!num: 当所有连通分量大小都为偶数时，num=0
res: 记录第一个满足条件（num=0）的查询位置

erase(nw2): 撤销第二部分的操作，回到只处理左半部分询问后的状态
dfs(L, res - 1, mid + 1, r): 递归处理查询[L, res-1]，在权重范围[mid+1, r]内搜索
erase(nw): 撤销第一部分的操作，回到初始状态
重新添加边：为递归到右子树做准备

dfs(res, R, l, mid): 递归处理查询[res, R]，在权重范围[l, mid]内搜索
erase(nw): 撤销所有操作，恢复状态
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+5;

struct node {
    int u, v, w, id;
    bool operator<(const node &o) const {
        return w < o.w;
    }
} e[N], b[N];

int fa[N];
inline int find(int x) { return x == fa[x] ? x : find(fa[x]); }

int tot, st[N], sz[N], num;
inline void erase(int x) {
    while (tot > x) {
        int v = st[tot--], u = fa[v];
        fa[v] = v, sz[u] -= sz[v];
        if (sz[u]&1 && sz[v]&1)
            num += 2;
    }
}

inline void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);
    if (sz[x]&1 && sz[y]&1) num -= 2;
    sz[x] += sz[y], fa[y] = x, st[++tot] = y;
}

int ans[N];
inline void dfs(int L, int R, int l, int r) {
    if (L > R || r < l) return;//边界条件
    if (l == r) {//递归终止条件
        for (int i = L; i <= R; ++i)
            ans[i] = b[l].w;//所有查询的答案都是b[l].w
        return;
    }
    int mid = (l + r) >> 1, nw = tot;//记录当前操作栈位置，用于后续撤销
    //遍历排序后的边b[l..mid]，只处理那些在当前查询范围[L,R]之前添加的边
    for (int i = l; i <= mid; ++i)
        if (b[i].id < L) merge(b[i].u, b[i].v);
    int res = R + 1, nw2 = tot;
    for (int i = L; i <= R; ++i) {
        if (e[i].w <= b[mid].w) merge(e[i].u, e[i].v);
        if (!num) { res = i; break; }//找到第一个满足条件的位置
    }
    erase(nw2), dfs(L, res - 1, mid + 1, r), erase(nw);
    for (int i = L; i <= res - 1; ++i)
        if (e[i].w <= b[l].w) merge(e[i].u, e[i].v);
    dfs(res, R, l, mid), erase(nw);
}

int n, m;
int main() {
    fast;
    cin >> n >> m; num = n;
    for (int i = 1; i <= n; ++i) sz[i] = 1, fa[i] = i;
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        e[i].id = i, b[i] = e[i];
    }
    sort(b + 1, b + m + 1), b[m+1].w = -1;
    dfs(1, m, 1, m+1);
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
    return 0;
}