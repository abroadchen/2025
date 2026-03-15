//
// Created by Psy.C on 2026/3/15.
//
/**
N = 5e5+5：最大节点数
M = 55：最大颜色数
fa[N]：父亲节点
sz[N]：子树大小（用于启发式合并）
dis[N]：到根节点的距离奇偶性
find()：非递归路径压缩查找
get(x)：获取从x到根节点的异或路径值
用于维护二分图染色的状态

边信息（端点x,y，颜色col）
vc[N<<2]：线段树数组，每个节点存储该时间段的边
在时间段[L,R]内添加边(u,v)，颜色为cl
使用线段树区间更新，将操作分配到对应节点

top：撤销栈指针
X[i], Y[i]：第i次询问的边ID和颜色
U[i], V[i]：第i条边的端点
nxt[i]：下一次相同边的出现时间
lst[i] = 上一次边i出现的时间点
nxt[i] = 从时间i开始，这条边下次消失的时间点
c[N]：边的颜色
st[N]：撤销栈，存储(col, y)对

处理当前线段树节点中的所有操作
启发式合并：将小集合合并到大集合
更新距离奇偶性：g[col].dis[y] = g[col].get(u)^g[col].get(v)^1
将操作记录压入撤销栈
在叶子节点处理询问
dis：判断(u,v)是否应该在同一集合
如果在同一集合但应不同色，输出"NO"
否则输出"YES"并更新颜色
递归处理左右子区间
撤销栈顶操作直到tp位置
恢复并查集状态，实现"时光倒流"

O((m + q) * k * α(n) * log q)，其中α是阿克曼函数的反函数


if (lst[X[i]]) nxt[lst[X[i]]] = i;：
如果边X[i]之前出现过（lst[X[i]]非0）
那么上一次出现的位置的nxt值设为当前位置i
即：从上次出现时间到这次出现时间，这条边是活跃的
lst[X[i]] = i;：更新边X[i]最后出现的时间为i
如果某个询问的nxt值仍为0（意味着这条边在此后没有再次出现）
将其nxt值设为q（活跃到最后一个时刻）


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 5e5+5, M = 55;

int n;
struct node {
    int fa[N], sz[N]; bool dis[N];
    int find(int x) const {
        while (x != fa[x]) x = fa[x];
        return x;
    }
    int get(int x) const {
        int y = 0;
        while (x != fa[x])
            y ^= dis[x], x = fa[x];
        return y;
    }
    void init() {
        for (int i = 1; i <= n; ++i) fa[i] = i, sz[i] = 1;
    }
} g[M];

struct node2 { int x, y, col; };
vector<node2> vc[N<<2];
void add(int l, int r, int o, const int& L, const int& R,
    const int& u, const int& v, const int& cl) {
    if (L <= l && r <= R) vc[o].push_back({u, v, cl});
    else {
        int mid = (l + r) >> 1;
        if (L <= mid) add(l, mid, o<<1, L, R, u, v, cl);
        if (mid < R) add(mid+1, r, o<<1|1, L, R, u, v, cl);
    }
}

int top, X[N], Y[N], U[N], V[N], nxt[N], c[N], q;
ii st[N];
void dfs(int l, int r, int o) {
    int tp = top;
    for (int i = 0; i < vc[o].size(); ++i) {
        int col = vc[o][i].col, u = vc[o][i].x, v = vc[o][i].y;
        int x = g[col].find(u), y = g[col].find(v);
        if (x != y) {
            if (g[col].sz[x] < g[col].sz[y]) swap(x, y);
            g[col].sz[x] += g[col].sz[y];
            g[col].dis[y] = g[col].get(u)^g[col].get(v)^1;
            g[col].fa[y] = x;
            st[++top] = {col, y};
        }
    }
    if (l == r) {
        int id = X[l], col = Y[l], u = U[id], v = V[id];
        bool dis = g[col].get(u)^g[col].get(v)^1;
        if (dis && g[col].find(u) == g[col].find(v)) {
            cout << "NO\n";
            if (l + 1 <= nxt[l]) add(1, q, 1, l+1, nxt[l], u, v, c[id]);//使用原颜色
        } else {
            cout << "YES\n";
            if (l + 1 <= nxt[l]) add(1, q, 1, l+1, nxt[l], u, v, c[id]=col);
        }
    } else {
        int mid = (l + r) >> 1;
        dfs(l, mid, o<<1); dfs(mid+1, r, o<<1|1);
    }
    while (top > tp) {
        auto f = st[top--];
        int col = f.first, y = f.second;
        g[col].sz[g[col].fa[y]] -= g[col].sz[y];
        g[col].dis[y] = 0;
        g[col].fa[y] = y;
    }
}

int m, k, lst[N];
int main() {
    fast;
    cin >> n >> m >> k >> q;
    for (int i = 1; i <= m; ++i) cin >> U[i] >> V[i];
    for (int i = 1; i <= q; ++i) {
        cin >> X[i] >> Y[i];
        if (lst[X[i]]) nxt[lst[X[i]]] = i;
        lst[X[i]] = i;
    }
    for (int i = 1; i <= q; ++i)
        if (!nxt[i]) nxt[i] = q;
    for (int i = 1; i <= k; ++i) g[i].init(); dfs(1, q, 1);
    return 0;
}