//
// Created by Psy.C on 2026/4/18.
//
/**
c: 价格/成本
v: 价值/评分
重载比较运算符：按价值降序排列，价值相同时按成本升序
tag[N]: 延迟标记数组
val[N]: 节点值
sum[N]: 节点权值和
res[N]: 结果数组
add: 更新节点的延迟标记和值
cnt: 节点计数器
r[N]: 随机优先级（用于维持平衡）
build: 创建新节点，分配随机优先级
ls[N]: 左子树
rs[N]: 右子树
将当前节点的标记下推到左右子树
清除当前节点的标记
合并两棵Treap
按优先级维护堆性质
按值k分割Treap
x: 所有值<k的节点
y: 所有值≥k的节点
遍历Treap，确保所有标记都被处理
n: 物品数量
m: 查询数量
rt: 根节点
a,b,c,d: 临时变量
Q: 队列，用于处理节点
输入物品的价格和价值
按价值降序、价格升序排序
输入查询数量
对每个查询值x，在Treap中创建对应节点
按价值顺序处理每个物品
将Treap按价格q[i].c和2*q[i].c分割
更新相应区间的值和计数
使用队列处理节点，将它们重新整合到Treap中
最后处理所有剩余标记
输出结果


按价值降序遍历所有物品（已排序）
split(rt, a, b, q[i].c): 将Treap按价格q[i].c分割
a: 价格 < q[i].c 的查询点集合
b: 价格 ≥ q[i].c 的查询点集合
split(b, b, c, 2*q[i].c): 将b部分按价格2*q[i].c分割
b: 价格 ∈ [q[i].c, 2*q[i].c) 的查询点集合
c: 价格 ≥ 2*q[i].c 的查询点集合
add(b, -q[i].c, 1): 对b区间内的每个节点，减去价格q[i].c，计数+1
add(c, -q[i].c, 1): 对c区间内的每个节点，减去价格q[i].c，计数+1
这表示选择了物品i，消耗了价格，增加了计数
将b区间根节点加入队列
BFS遍历b区间的所有子节点：
pushdown(now): 下推标记
if (ls[now]) Q.push(ls[now]); if (rs[now]) Q.push(rs[now]);: 将子节点加入队列
ls[now] = rs[now] = 0;: 断开子节点连接，将其变为独立节点
split(a, a, d, val[now]): 将独立节点now插入到a区间合适位置
a = merge(merge(a, now), d);: 重新合并a区间
将处理后的a区间和c区间合并，形成新的Treap根


x, y: 两个Treap的根节点
假设x的所有节点值 < y的所有节点值（合并前提）
边界条件: if (!x || !y) return x + y;
如果x为空，返回y
如果y为空，返回x
如果都为空，返回0
标记下推: pushdown(x); pushdown(y);
将x和y的延迟标记传递给子节点
按优先级合并:
r[x] < r[y]: x的优先级更低（随机堆性质）
将x的右子树与y合并
x成为新的根（保持BST性质）
将x与y的左子树合并
y成为新的根

rt: 要分割的Treap根节点
x, y: 分割后的两个Treap根节点
k: 分割阈值
结果: x中所有节点值 < k，y中所有节点值 ≥ k
边界条件: if (!rt) { x = y = 0; return; }
空节点直接返回
标记下推: pushdown(rt);
情况1: if (val[rt] >= k)
当前节点值≥k，应归入y
将当前节点设为y的根
递归分割左子树，结果分别赋给x和y的左子树
情况2:
当前节点值<k，应归入x
将当前节点设为x的根
递归分割右子树，结果分别赋给x的右子树和y

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
struct node {
    int c, v;
    bool operator<(const node &o) const {
        return v == o.v ? c < o.c : v > o.v;
    }
} q[N];

int tag[N], val[N], sum[N], res[N];
void add(int rt, int x, int y) {
    tag[rt] += x; val[rt] += x; sum[rt] += y; res[rt] += y;
}
int cnt, r[N];
int build(int v) {
    int rt = ++cnt;
    r[rt] = rand(); val[rt] = v;
    return rt;
}

int ls[N], rs[N];
void pushdown(int rt) {
    if (tag[rt] && sum[rt]) {
        add(ls[rt], tag[rt], sum[rt]);
        add(rs[rt], tag[rt], sum[rt]);
        tag[rt] = sum[rt] = 0;
    }
}
int merge(int x, int y) {
    if (!x || !y) return x + y;
    pushdown(x); pushdown(y);
    if (r[x] < r[y]) {
        rs[x] = merge(rs[x], y);
        return x;
    }
    ls[y] = merge(x, ls[y]);
    return y;
}

void split(int rt, int& x, int& y, int k) {
    if (!rt) { x = y = 0; return; }
    pushdown(rt);
    if (val[rt] >= k) {
        y = rt;
        split(ls[rt], x, ls[y], k);
    } else {
        x = rt;
        split(rs[rt], rs[x], y, k);
    }
}
void dfs(int rt) {
    pushdown(rt);
    if (ls[rt]) dfs(ls[rt]);
    if (rs[rt]) dfs(rs[rt]);
}

int n, m, rt, a, b, c, d;
queue<int> Q;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> q[i].c >> q[i].v;
    sort(q + 1, q + n + 1);
    cin >> m;
    for (int i = 1, x; i <= m; ++i) {
        cin >> x; split(rt, a, b, x);
        rt = merge(merge(a, build(x)), b);
    }
    for (int i = 1; i <= n; ++i) {
        split(rt, a, b, q[i].c);
        split(b, b, c, 2*q[i].c);
        add(b, -q[i].c, 1);
        add(c, -q[i].c, 1);
        Q.push(b);
        while (!Q.empty()) {
            int now = Q.front(); Q.pop();
            pushdown(now);
            if (ls[now]) Q.push(ls[now]);
            if (rs[now]) Q.push(rs[now]);
            ls[now] = rs[now] = 0;
            split(a, a, d, val[now]);
            a = merge(merge(a, now), d);
        }
        rt = merge(a, c);
    }
    dfs(rt);
    for (int i = 1; i <= m; ++i) cout << res[i] << ' ';
    return 0;
}