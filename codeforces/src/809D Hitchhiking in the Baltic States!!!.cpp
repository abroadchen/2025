//
// Created by Psy.C on 2026/9/20.
//
/**
sum[x] = 左子树不同值数 + 右子树不同值数 + 自己节点的 cnt（出现次数）。
*(ls[x]!=0) 是因为用 0 表示空指针（下标 0 节点 sum[0]=0），避免访问空。
维护子树聚合
惰性区间加：tag[x] 表示"整棵子树每个节点的 val 都要加 tag[x]"。
push_down 时把 tag 传给两个孩子并清空自己的 tag。
这样区间整体 +1 不用逐点改，只需打标
一次单旋转（zig/zag），把 x 提升到其父 y 的位置，再调整子链接和 fa 指针，最后 push_up 更新聚合
先把从 x 到 rt 的路径存栈里从上到下 push_down，确保惰性标记在旋转前处理。
然后不断把 x 提升到 rt：
双旋（zig-zig / zig-zag）：((ls[y]==x)^(ls[fa[y]]==y))?x:y 判断是同向（zig-zig，先旋 y）还是反向（zig-zag，先旋 x）。
rt=0 时把 x 旋到根（root = x）
二叉搜索：若 x < val[u] 走左子树（此时 u 可能是"第一个 ≥ x"的候选，记录 ret），否则走右子树。
最后找到的节点 splay 到根，返回 ret（第一个 ≥ x 的位置）。
类似地 get_front 找 > x 的最小值（第一个 > x / 后继）
从节点 u 开始按 BST 向下走到值为 x 的位置；若不存在则新建节点。
到达后 cnt[u]++（可能出现重复值，count 累加），sum[u]++，把该节点伸展到根。
add(root, l) 即插入新值 l
用 get_front/get_back 定位到 x 的前驱 u 和后继 v，把区间 (u..v) 单独旋出来：v 的左子树就是值恰好为 x 的节点集合。
将该节点 cnt 减 1，整条链 sum 减 1；若该节点 sum 变 0（没有值了）就断开删除。
这正是"碰撞去重/删除某个值"的操作。
定位区间边界，把区间所在子树（y 的左子树）整体打 +1 惰性标记。
这样整段值一次 +1，O(log n)
先插入两个哨兵 -INT_MAX、+INT_MAX（避免边界判断）。
每个区间 (l, r)：
对 [l, r-1] 所有现存值整体 +1（modity）。
找出 r-1 的"后继/第一个 ≥ r-1"的节点 x，若它不是哨兵就把 x 删掉（因为区间 [l, r-1] 整体 +1 后，原先等于 r-1 的值会变成 r，等于越界被删——这是"这个值加到 r 之后退出区间"的语义）。
把左端点 l 插入集合。
最后 sum[root] - 2 减去两个哨兵，即为当前不同值的个数。
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 3e5+7;

ll sum[N], ls[N], rs[N], cnt[N];
void push_up(ll x) {
    sum[x] = sum[ls[x]]*(ls[x]!=0) + sum[rs[x]]*(rs[x]!=0) + cnt[x];
}

ll val[N], tag[N];
void push_down(ll x) {
    if (ls[x]) val[ls[x]] += tag[x], tag[ls[x]] += tag[x];
    if (rs[x]) val[rs[x]] += tag[x], tag[rs[x]] += tag[x];
    tag[x] = 0;
}

ll fa[N];
void merge(ll x) {
    ll y = fa[x], z = fa[y]; fa[x] = z, fa[y] = x;
    if (ls[z] == y) ls[z] = x; else rs[z] = x;
    if (ls[y] == x) ls[y] = rs[x], rs[x] = y, fa[ls[y]] = y;
    else rs[y] = ls[x], ls[x] = y, fa[rs[y]] = y;
    push_up(y), push_up(x);
}

ll top, st[N], root;
void splay(ll x, ll rt) {
    top = 1; st[top] = x;
    for (ll y = x; y != rt; y = fa[y]) st[++top] = fa[y];
    for (ll i = top; i >= 1; --i) push_down(st[i]);
    for (ll y = 0; (y=fa[x])!=rt; merge(x))
        if (fa[y] != rt) merge(((ls[y]==x)^(ls[fa[y]]==y))?x:y);
    if (!rt) root = x;
}

ll get_back(ll u, ll x) {
    ll lst = 0, ret = 0;
    while (u) {
        if (x < val[u]) lst = u, push_down(u), u = ls[ret=u];
        else lst = u, push_down(u), u = rs[u];
    }
    splay(lst, 0);
    return ret;
}

ll get_front(ll u, ll x) {
    ll lst = 0, ret = 0;
    while (u) {
        if (x > val[u]) lst = u, push_down(u), u = rs[ret=u];
        else lst = u, push_down(u), u = ls[u];
    }
    splay(lst, 0);
    return ret;
}

ll tot;
void add(ll u, ll x) {
    while (x != val[u]) {
        push_down(u);
        if (x < val[u]) {
            if (!ls[u]) ls[u] = ++tot, fa[tot] = u, val[tot] = x;
            u = ls[u];
        } else {
            if (!rs[u]) rs[u] = ++tot, fa[tot] = u, val[tot] = x;
            u = rs[u];
        }
    }
    ++cnt[u], ++sum[u];
    splay(u, 0);
}

void det(ll x) {
    ll u = get_front(root, x), v = get_back(root, x);
    splay(u, 0), splay(v, u);
    if (!ls[v]) return;
    --cnt[ls[v]], --sum[ls[v]], --sum[v], --sum[u];
    if (!sum[ls[v]]) { fa[ls[v]] = 0; ls[v] = 0; }
}

void modity(ll l, ll r) {
    ll x = get_front(root, l), y = get_back(root, r-1);
    splay(x, 0), splay(y, x);
    if (ls[y]) val[ls[y]]++, tag[ls[y]]++;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    ll n = rd(); add(root, INT_MAX), add(root, -INT_MAX);
    for (int i = 1; i <= n; ++i) {
        ll l = rd(), r = rd();
        if (i == 1) { add(root, l); continue; }
        ll x = get_back(root, r-1);
        modity(l, r);
        if (val[x] < INT_MAX) det(val[x]);
        add(root, l); splay(1, 0);
    }
    printf("%lld\n", sum[root]-2);
    return 0;
}