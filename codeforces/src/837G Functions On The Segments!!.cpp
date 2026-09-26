//
// Created by Psy.C on 2026/9/26.
//
/**
lp、rp：左右儿子指针（动态开点）。
f1、f2：标记左右儿子"是否已实际开出来"。
v1、v2：两棵不同含义的统计值（一条线段贡献两条信息）
主席树（可持久化）经典实现：新建节点时把上一版本对应节点的信息（v1、v2 及儿子指针）复制过来，然后只沿路径修改，实现历史版本共享。
lok / rok：当要往左/右儿子写入且该儿子还未实际开点时，从旧版本里"复制"出一个新节点。f1/f2 记录是否已开。
这样保证每次 update 只新增 O(log m) 个节点，即"可持久化"
在位置 X 处加 val，flg 决定加在 v1 还是 v2。
先改当前节点值，再递归单侧儿子，过程中用 lok/rok 动态开新节点
返回区间 [L,R] 内两棵线段数组 v1 与 v2 的和（用 node{a,b} 返回）。
可持久化查询
收集所有会用到的坐标（每条线段的左右端点及其 +1）→ 排序去重 → 得到离散化坐标轴长度 m。
这里把 x[i]（左端）、xx[i]（右端）及其相邻位置都加入离散化点集。
每个 rt[i] 表示处理完前 i 条线段后的"累积状态"——这正是主席树的时间维（按线段序号建版本）‍。
通过多个 update，把每条线段的参数 (x, xx, y, a, b, yy) 拆成对坐标区间的区间加（用差分思想：左端 +v、右端之后 −v），一次性地编码进 v1 与 v2 两棵值。
整体把"每条线段"抽象成一条以 u（查询横坐标）为变量的一次函数：v1*u + v2
对于查询 (l, r, u)：用主席树的减法 rt[r] − rt[l-1] 得到"只包含第 l..r 条线段"状态的贡献。
对每条线段，其贡献是一个关于 u 的一次式 A*u + B（A 存于 v1，B 存于 v2）。前缀和求得 a1.a, a1.b 代表前 l-1 条的总一次式；a2 代表前 r 条的总一次式；两者相减得到区间内线段的总一次式。
代入 u 求值 A*u+B，得到答案 lst；同时 u 用上一答案加密（+lst mod）使查询强制在线
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 75005, mod = 1e9;

struct Tr { int lp, rp, f1, f2; ll v1, v2; } tr[N*200];

void init(int p, int lst) {
    tr[p].v1 = tr[lst].v1; tr[p].v2 = tr[lst].v2;
    tr[p].lp = tr[lst].lp; tr[p].rp = tr[lst].rp;
}

int cnt;
void lok(int p) {
    if (tr[p].f1 == 0) {
        int lst = tr[p].lp;
        tr[p].lp = ++cnt;
        init(cnt, lst);
    }
    tr[p].f1 = 1;
}
void rok(int p) {
    if (tr[p].f2 == 0) {
        int lst = tr[p].rp;
        tr[p].rp = ++cnt;
        init(cnt, lst);
    }
    tr[p].f2 = 1;
}

void update(int p, int l, int r, int X, ll val, int flg) {
    if (flg == 1) tr[p].v1 += val; else tr[p].v2 += val;
    if (l == r) return;
    int mid = (l+r)>>1;
    if (X <= mid) {
        lok(p);
        update(tr[p].lp, l, mid, X, val, flg);
    } else {
        rok(p);
        update(tr[p].rp, mid+1, r, X, val, flg);
    }
}

struct node { ll a, b; };
node query(int p, int l, int r, int L, int R) {
    if (L <= l && R >= r) return {.a = tr[p].v1, .b = tr[p].v2};
    int mid = (l+r)>>1;
    node a1 = {.a = 0, .b = 0}, a2 = {.a = 0, .b = 0};
    if (L <= mid && tr[p].lp)
        a1 = query(tr[p].lp, l, mid, L, R);
    if (mid < R && tr[p].rp)
        a2 = query(tr[p].rp, mid+1, r, L, R);
    return {.a = a1.a+a2.a, .b = a1.b+a2.b};
}

int n, n1, re[N<<3], x[N], xx[N], a[N], b[N], rt[N<<1];
ll y[N], yy[N];
int main() {
    fast;
    cin >> n; re[++n1] = 0; re[++n1] = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> xx[i] >> y[i] >> a[i] >> b[i] >> yy[i];
        re[++n1] = x[i]; re[++n1] = xx[i];
        re[++n1] = xx[i] + 1; re[++n1] = x[i] + 1;
    }
    sort(re+1, re+1+n1);
    int m = unique(re+1, re+1+n1) - re - 1;
    int t, tt;
    for (int i = 1; i <= n; ++i) {
        rt[i] = ++cnt;
        init(rt[i], rt[i-1]);
        update(rt[i], 1, m, 1, y[i], 2);
        t = upper_bound(re+1, re+m+1, x[i]) - re;
        update(rt[i], 1, m, t, -y[i], 2);
        t = upper_bound(re+1, re+1+m, x[i]) - re;
        tt = upper_bound(re+1, re+1+m, xx[i]) - re;
        update(rt[i], 1, m, t, a[i], 1);
        update(rt[i], 1, m, t, b[i], 2);
        update(rt[i], 1, m, tt, -a[i], 1);
        update(rt[i], 1, m, tt, -b[i], 2);
        t = upper_bound(re+1, re+1+m, xx[i]) - re;
        update(rt[i], 1, m, t, yy[i], 2);
    }
    node a1{}, a2{}; ll a3, a4, lst = 0;
    int T, l, r, u; cin >> T;
    while (T--) {
        cin >> l >> r >> u;
        u = (u + lst) % mod;
        t = upper_bound(re+1, re+m+1, u) - re - 1;
        a1 = query(rt[l-1], 1, m, 1, t);
        a2 = query(rt[r], 1, m, 1, t);
        a3 = a1.a*u + a1.b;
        a4 = a2.a*u + a2.b;
        lst = a4 - a3;
        cout << lst << '\n';
    }
    return 0;
}