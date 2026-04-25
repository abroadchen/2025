//
// Created by Psy.C on 2026/4/25.
//
/**
x: 查询节点
t: 时间参数
org: 原始查询序号
top[N]: 重链的顶部节点
p[N]: 节点在DFS序中的位置
q[N]: DFS序数组
son[N]: 重儿子
to[], head[], nxt[]: 邻接表存储树
s[]: 线段树维护的最大值
tag[]: 懒标记
sd[]: 初始深度值
dep[]: 节点深度

第一步: ++q[0]
将q[0]自增1
返回自增后的值
第二步: p[x] = ++q[0]
将节点x在DFS序中的位置设为当前的计数值
第三步: q[q[0]] = x
在DFS序数组的相应位置记录节点x

目的: 从节点x向上走，找到最远的可达节点u
变量含义:
u: 当前考虑的节点
top[u]: u所在重链的顶端
dep[x] + t: 从节点x出发的时间预算
判断逻辑:
query(1, n, 1, p[top[u]], p[u]): 查询当前重链上的最大值
如果最大值 ≤ dep[x] + t，说明整条重链都可达，向上跳到父节点
否则在当前重链上进行二分查找
目的: 在当前重链上找到第一个不可达的节点
二分逻辑:
l = p[top[u]]+1, r = p[u] + 1: 在重链范围内二分
query(1, n, 1, mid, p[u]): 查询从mid到u的最大值
如果查询结果 > dep[x] + t，说明mid位置不可达，向右搜索
否则向左搜索
最终q[l-1]就是找到的关键节点
ret = 2*(dep[x] - dep[u]) + t
2*(dep[x] - dep[u]): 从x到u再到x的距离（往返）
+ t: 额外时间预算
沿着重链向上更新，直到到达u所在的重链
ret-dep[x]: 更新的值（可能是某种约束条件）
每条重链用区间更新，复杂度O(log n)



将树分解为重链和轻边
使得任意路径可以分解为O(log n)条重链段

预处理: O(n)
单次查询: O(log²n)
总体: O(m log²n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+7, inf = 2e9;

struct node { int x, t, org; } t[N];

int top[N], p[N], q[N], son[N], to[N], head[N], nxt[N];
void dfs(int x, int tp) {//构建重链
    top[x] = tp; p[x] = ++q[0], q[q[0]] = x;
    if (son[x]) dfs(son[x], tp);
    for (int i = head[x]; i != -1; i = nxt[i])
        if (to[i] != son[x])
            dfs(to[i], to[i]);
}

int cnt;
void add(int a, int b) {
    to[cnt] = b; nxt[cnt] = head[a]; head[a] = cnt++;
}

int s[N<<2], tag[N<<2], sd[N<<2], dep[N];
void build(int l, int r, int x) {
    s[x] = tag[x] = -inf;
    if (l == r) {
        sd[x] = dep[q[l]]<<1;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, x<<1), build(mid+1, r, x<<1|1);
    sd[x] = max(sd[x<<1], sd[x<<1|1]);
}

/**
s[x]: 线段树节点x维护的最大值
sd[x]: 节点x对应的初始深度值（2*depth）
tag[x]: 节点x的懒惰标记
y: 要添加的值（更新量）
 */
void modify(int x, int y) {
    s[x] = max(s[x], sd[x]+y), tag[x] = max(tag[x], y);
}

void pushdown(int x) {
    if (tag[x] != -inf)
        modify(x<<1, tag[x]), modify(x<<1|1, tag[x]), tag[x] = -inf;
}
void update(int l, int r, int x, int a, int b, int c) {
    if (a <= l && r <= b) {
        modify(x, c);
        return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if (a <= mid) update(l, mid, x<<1, a, b, c);
    if (b > mid) update(mid+1, r, x<<1|1, a, b, c);
    s[x] = max(s[x<<1], s[x<<1|1]);
}
int query(int l, int r, int x, int a, int b) {
    if (a <= l && r <= b) return s[x];
    pushdown(x);
    int mid = (l + r) >> 1;
    if (b <= mid) return query(l, mid, x<<1, a, b);
    if (a > mid) return query(mid+1, r, x<<1|1, a, b);
    return max(query(l, mid, x<<1, a, b), query(mid+1, r, x<<1|1, a, b));
}

bool cmp(const node& a, const node& b) {
    return dep[a.x] + a.t == dep[b.x] + b.t ? a.x < b.x :
        dep[a.x] + a.t < dep[b.x] + b.t;
}

int n, fa[N];
int get(int x, int t) {
    int u = x;
    while (u) {
        if (query(1, n, 1, p[top[u]], p[u]) <= dep[x] + t) {
            u = fa[top[u]]; continue;
        }
        int l = p[top[u]]+1, r = p[u] + 1, mid;
        while (l < r) {
            mid = (l + r) >> 1;
            if (query(1, n, 1, mid, p[u]) > dep[x] + t)
                l = mid + 1;
            else r = mid;
        }
        u = q[l-1];
        break;
    }
    if (!u) u = 1;
    int ret = 2*(dep[x] - dep[u]) + t, v = x;
    while (top[v] != top[u])
        update(1, n, 1, p[top[v]], p[v], ret-dep[x]), v = fa[top[v]];
    update(1, n, 1, p[u], p[v], ret-dep[x]);
    return ret;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int m, i, siz[N], ans[N];
int main() {
    fast;
    n = rd() + 1, m = rd(); dep[1] = 1;//根节点深度为1
    memset(head, -1, sizeof(head));
    for (i = 2; i <= n; ++i) fa[i] = rd()+1, add(fa[i], i), dep[i] = dep[fa[i]] + 1;//节点深度
    for (i = n; i >= 2; --i) {
        //初始化子树大小为1 累加子树大小到父亲节点
        siz[i]++, siz[fa[i]] += siz[i];
        if (siz[i] > siz[son[fa[i]]]) son[fa[i]] = i;//找到重儿子（子树最大的儿子）
    }
    //从根节点1开始进行树链剖分DFS，重链顶部也是1
    //建立线段树，区间[1,n]，根节点为1
    dfs(1, 1); build(1, n, 1);
    for (i = 1; i <= m; ++i) t[i].x = rd()+1, t[i].t = rd(), t[i].org = i;
    sort(t + 1, t + m + 1, cmp);//深度+时间参数排序
    for (i = 1; i <= m; ++i)
        ans[t[i].org] = get(t[i].x, t[i].t);//结果存储在ans数组的原始位置上
    for (i = 1; i <= m; ++i) cout << ans[i] << ' ';
    return 0;
}