//
// Created by Psy.C on 2026/1/27.
//
/**
* l, r: 区间左右边界
lz[2]: 懒惰标记数组，lz[0]和lz[1]对应不同状态
sum[2]: 区间和数组，sum[0]和sum[1]对应不同状态
*dfn[N]: DFS序时间戳
num: DFS序计数器
mp[N]: 时间戳到节点的映射
flag[N]: 标志数组，用于区分奇偶层
ed[N]: 子树结束时间戳
 *
*计算DFS序
dfn[x]: 节点x的进入时间
ed[x]: 节点x的子树结束时间
flag[v] = flag[x] ^ 1: 标记节点在奇数层还是偶数层
通过DFS建立子树的连续区间
 *
 *向上更新：合并左右子树的和
 *
*下传懒惰标记
将父节点的标记传递给子节点
清空父节点标记
 *
*区间更新操作
如果完全覆盖区间，打懒惰标记
否则递归更新左右子树
 *
*单点查询操作
先下传懒惰标记
递归查询目标位置
 *
*读入节点数n和操作数m
读入初始值数组a
构建邻接表表示的树
*操作1：update(1, dfn[x], ed[x], y, flag[x])

对节点x的子树进行区间更新
更新值为y
根据节点所在层数选择状态（flag[x]）
操作2：查询

query(1, dfn[x], flag[x]): 查询x节点在对应状态下的累积值
query(1, dfn[x], flag[x]^1): 查询x节点在相反状态下的累积值
最终结果 = 原始值 + 累积值 - 相反状态的累积值
 *
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 200007
using namespace std;

struct node { ll l, r, lz[2], sum[2]; } t[N<<2];

int dfn[N], num, mp[N], flag[N], ed[N];
vector<int> g[N];
void dfs(const int x, const int fa) {
    dfn[x] = ++num;
    mp[num] = x;
    for (int i = 0; i < g[x].size(); ++i) {
        const int v = g[x][i];
        if (v == fa) continue;
        flag[v] = flag[x] ^ 1;
        dfs(v, x);
    }
    ed[x] = num;
}

void push_up(const int i, const int fg) {
    t[i].sum[fg] = t[i<<1].sum[fg] + t[i<<1|1].sum[fg];
}

void build(const int i, const int l, const int r) {
    t[i].l = l, t[i].r = r;
    if (l == r) return;
    const int mid = (l + r) >> 1;
    build(i<<1, l, mid); build(i<<1|1, mid+1, r);
    push_up(i, 0); push_up(i, 1);
}

void pushdown(const int i, const int fg) {
    if (t[i].lz[fg] != 0) {
        t[i<<1].lz[fg] += t[i].lz[fg];
        t[i<<1].sum[fg] += (t[i<<1].r - t[i<<1].l + 1) * t[i].lz[fg];
        t[i<<1|1].lz[fg] += t[i].lz[fg];
        t[i<<1|1].sum[fg] += (t[i<<1|1].r - t[i<<1|1].l + 1) * t[i].lz[fg];
        t[i].lz[fg] = 0;
    }
}

void update(const int i, const int x, const int y, const int v, const int fg) {
    if (x > y) return;
    if (x <= t[i].l && t[i].r <= y) {
        t[i].lz[fg] += v;
        t[i].sum[fg] += (t[i].r - t[i].l + 1) * v;
        return;
    }
    const int mid = static_cast<int>((t[i].l + t[i].r) >> 1);
    pushdown(i, fg);
    if (x <= mid) update(i<<1, x, y, v, fg);
    if (y > mid) update(i<<1|1, x, y, v, fg);
    push_up(i, fg);
}

int query(const int i, const int x, const int fg) {
    if (t[i].l == t[i].r) return static_cast<int>(t[i].sum[fg]);
    pushdown(i, fg);
    if (const int mid = static_cast<int>((t[i].l + t[i].r) >> 1); x <= mid) return query(i<<1, x, fg);
    return query(i<<1|1, x, fg);
}

int main() {
    fast;
    int n, m, a[N]; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    dfs(1, 0); build(1, 1, num);
    for (int i = 1, op, x, y; i <= m; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> x >> y;
            update(1, dfn[x], ed[x], y, flag[x]);
        } else {
            cin >> x;
            cout << a[x] + query(1, dfn[x], flag[x]) - query(1, dfn[x], flag[x]^1) << '\n';
        }
    }
    return 0;
}