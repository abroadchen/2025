//
// Created by Psy.C on 2026/3/14.
//
/**
随机平衡二叉搜索树
key[]: 节点随机优先级
tot: 节点总数
siz[]: 子树大小
lc[], rc[]: 左右子节点
v[]: 节点值
rv[]: 子树最右节点值（最大值）

创建新节点，分配随机优先级
初始化节点值和相关信息
返回节点编号

更新节点p的子树大小
更新节点p子树的最大值（最右节点值）

对以p为根的子树应用等差数列增量
a0: 首项增量
d: 公差增量
更新延迟标记

将节点p的懒惰标记下传给左右子树
左子树使用原首项，右子树首项需要考虑左子树大小

将以p为根的Treap分裂成两棵树
前k个元素放入x，其余放入y
保持BST性质

合并两棵Treap，保持堆性质
优先级高的作为根节点

在Treap中查找满足条件的位置
检查节点p是否满足单调性要求
mx: 最优位置，mxx: 对应值

在pos位置插入值vv
先分裂再合并

对pos之后的所有节点应用等差数列修改

遍历Treap找到最大值

逐个读入元素
找到最佳插入位置
插入新值并对后续位置应用等差数列修改
最后找出整个序列的最大值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define TO(T,x) static_cast<T>(x)
using namespace std;
constexpr int N = 1e5+5;
mt19937 rd(20090212);

int key[N], tot, siz[N], lc[N], rc[N];
ll v[N], rv[N];
int build(ll val) {
    return key[++tot] = rd(), siz[tot] = 1,
        v[tot] = rv[tot] = val, tot;
}

void push_up(int p) {
    siz[p] = siz[lc[p]] + siz[rc[p]] + 1;
    rv[p] = rc[p] ? rv[rc[p]] : v[p];
}

ll a_0[N], d_[N];
void add(int p, ll a0, ll d) {
    v[p] += a0 + TO(ll, siz[lc[p]] + 1) * d;
    rv[p] += a0 + TO(ll, siz[p]) * d;
    a_0[p] += a0, d_[p] += d;
}

void pushdown(int p) {
    add(lc[p], a_0[p], d_[p]);
    add(rc[p], a_0[p] + TO(ll, siz[lc[p]] + 1)*d_[p], d_[p]);
    a_0[p] = d_[p] = 0;
}

void split(int p, int k, int& x, int& y) {
    if (!p) return x = y = 0, void();
    pushdown(p);
    if (siz[lc[p]] >= k) split(lc[y=p], k, x, lc[p]);
    else split(rc[x=p], k-siz[lc[p]]-1, rc[p], y);
    push_up(p);
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (key[x] > key[y])
        return pushdown(x), rc[x] = merge(rc[x], y), push_up(x), x;
    return pushdown(y), lc[y] = merge(x, lc[y]), push_up(y), y;
}

int a, mx;
ll mxx;
void fd(int p, int k, ll vv) {
    if (!p) return; pushdown(p);
    int rk = k + siz[lc[p]] + 1;
    if (v[p] >= (lc[p] ? rv[lc[p]] : vv) + TO(ll, rk)*a)
        mx = rk, mxx = v[p], fd(rc[p], rk, v[p]);
    else
        fd(lc[p], k, vv);
}

int rt, x;
void insert(int pos, ll vv) {
    split(rt, pos, rt, x);
    rt = merge(merge(rt, build(vv)), x);
}

void modify(int pos, ll a0, int d) {
    split(rt, pos, rt, x);
    add(x, a0, d);
    rt = merge(rt, x);
}

ll ans;
void dfs(int p) {
    ans = max(ans, v[p]), pushdown(p);
    if (lc[p]) dfs(lc[p]);
    if (rc[p]) dfs(rc[p]);
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a, mx = mxx = 0, fd(rt, 0, 0);
        insert(mx, mxx);
        modify(mx, TO(ll, mx)*a, a);
    }
    dfs(rt);
    cout << ans << '\n';
    return 0;
}