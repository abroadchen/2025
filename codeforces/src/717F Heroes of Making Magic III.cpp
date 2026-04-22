//
// Created by Psy.C on 2026/4/21.
//
/**
差分数组d，用于线段树维护
l, r：节点区间范围
siz：区间长度
sum：区间和（未使用）
tag[2]：懒标记数组，用于区间更新
d[2]：存储两种状态的值
f：标记（未使用）
向上更新父节点信息
tr[now].d[0]：取左子节点d[0]和右子节点d[o]的最小值
tr[now].d[1]：取左子节点d[1]和右子节点d[o^1]的最小值
o参数决定右子节点使用的索引
将懒标记下推给子节点
如果是叶子节点则返回
如果有tag[0]标记，将其传递给左右子节点对应位置
如果有tag[1]标记，将其传递给左右子节点对应位置
清除当前节点的标记
构建线段树
设置当前节点区间和大小
如果是叶子节点，初始化d[0]=d[l], d[1]=inf
递归构建左右子树
更新父节点信息，根据左子树大小奇偶性决定参数
区间更新操作
如果区间无效则返回
下推懒标记
如果完全覆盖区间，则更新标记和值
否则递归更新左右子树
根据左子树大小奇偶性调整参数
区间查询操作
如果区间无效返回inf
下推懒标记
如果完全包含在查询区间内，返回对应值
否则递归查询左右子树并返回最小值

[R+1, n-1]区间减k（抵消影响）
[R+2, n-1]区间加k（恢复正确影响）

x代表L-1位置的前缀和值
y代表R位置的前缀和值
y±x计算的是区间[L, R]的和（根据区间长度奇偶性决定符号）
最后的判断条件检查是否满足某些约束条件（如单调性、非负性等）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e5+7, inf = 0x7fffffff;

int d[N];

namespace sgt {
    struct node {
        int l, r, siz; ll tag[2], d[2];
    } tr[N<<2];
#define ls now<<1
#define rs (now<<1|1)
    void push_up(int now, bool o) {
        tr[now].d[0] = min(tr[ls].d[0], tr[rs].d[o]);
        tr[now].d[1] = min(tr[ls].d[1], tr[rs].d[o^1]);
    }
    void pushdown(int now, bool o) {
        if (tr[now].l == tr[now].r) return;
        if (tr[now].tag[0]) {
            tr[ls].d[0] += tr[now].tag[0], tr[ls].tag[0] += tr[now].tag[0];
            tr[rs].d[o] += tr[now].tag[0], tr[rs].tag[o] += tr[now].tag[0];
            tr[now].tag[0] = 0;
        }
        if (tr[now].tag[1]) {
            tr[ls].d[1] += tr[now].tag[1], tr[ls].tag[1] += tr[now].tag[1];
            tr[rs].d[o^1] += tr[now].tag[1], tr[rs].tag[o^1] += tr[now].tag[1];
            tr[now].tag[1] = 0;
        }
    }
    void build(int now, int l, int r) {
        tr[now].l = l, tr[now].r = r; tr[now].siz = r - l + 1;
        if (l == r) {
            tr[now].d[0] = d[l]; tr[now].d[1] = inf;
            return;
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
        push_up(now, tr[ls].siz&1);
    }
    void update(int now, int L, int R, ll x, bool o) {
        if (L > R) return;
        int l = tr[now].l, r = tr[now].r;
        pushdown(now, tr[ls].siz&1);
        if (L<=l && r<=R) {
            tr[now].tag[o] += x; tr[now].d[o] += x;
            return;
        }
        int mid = (l + r) >> 1;
        if (L <= mid) update(ls, L, R, x, o);
        if (R > mid) update(rs, L, R, x, o^tr[ls].siz&1);
        push_up(now, tr[ls].siz&1);
    }
    ll query(int now, int L, int R, bool o) {
        if (L > R) return inf;
        int l = tr[now].l, r = tr[now].r;
        pushdown(now, tr[ls].siz&1);
        if (L <= l && r <= R) return tr[now].d[o];
        int mid = (l + r) >> 1;
        ll ret = inf;
        if (L <= mid) ret = min(ret, query(ls, L, R, o));
        if (R > mid) ret = min(ret, query(rs, L, R, o^tr[ls].siz&1));
        return ret;
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, a[N], q;
int main() {
    fast;
    n = rd();
    for (int i = 0; i <= n-1; ++i) a[i] = rd(); d[0] = a[0];
    for (int i = 1; i <= n-1; ++i)
        d[i] = a[i] - a[i-1], a[i] -= a[i-1];
    sgt::build(1, 0, n-1);
    q = rd();
    while (q--) {
        int op = rd(), L = rd(), R = rd(), k;
        if (op == 1) {
            k = rd();
            sgt::update(1, L, R, k, L&1);
            //当区间长度为奇数时才执行
            if (R-L+1&1) sgt::update(1, R+1, n-1, -k, R+1&1),
                sgt::update(1, R+2, n-1, k, R+2&1);
        }
        if (op == 2) {
            //查询单点L-1的值
            ll x = L > 0 ? sgt::query(1, L-1, L-1, L-1&1) : 0,
            y = sgt::query(1, R, R, R&1);//查询单点R的值
            if (R-L+1&1) y += x; else y -= x;
            if (y != (R-L+1&1) || sgt::query(1, L, R, L&1) + x < 1 ||
                sgt::query(1, L, R, (L&1)^1) - x < 0)
                cout << "0\n";
            else cout << "1\n";
        }
    }
    return 0;
}