//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
有 n 个位置（数组），每个位置当前被"某种颜色/标签"覆盖。
有 q 个操作，两类：
op=1：给区间 [l,r] 染色为颜色 k（之前该区间上的旧颜色会被覆盖）。
op=2：查询区间 [l,r] 的某种权的和。
每种颜色有个"行为"：被第一次覆盖上时，会对线段树区间产生「加 1」还是「乘 2」的影响（由 assign 中 itl->v 决定）。
用 ODT 维护"区间颜色"的连续段，用懒标记线段树维护区间加、区间乘、区间和
node{l,r,v}：ODT 的"区间段"：[l,r]，值/颜色 v。
重载 <：按 l 排序，供 set 使用
s[id] 是每个颜色/标签 id 自己的一套 ODT，维护"该颜色覆盖的区间段集合"。即对每个颜色分别开一个 set。
split(id, x)：保证颜色 id 的区间段在位置 x 处被打断（若某段 [l,r] 跨过 x，就拆成 [l,x-1] 和 [x,r]），返回指向从 x 开始的段的迭代器。
先 lower_bound({x,0,0}) 找第一个 l>=x 的段。
若该段 l==x，说明已从 x 处断开，直接返回。
否则 --it 取前一段 [l,r]，删除后拆成两段插入，返回新插入的 {x,r} 的迭代器
每个线段树结点维护：区间和 s、加法懒标记 add、乘法懒标记 mul。
upd：给整段加 add，更新和与 add 标记。
upd2：给整段乘 mul，和、add、mul 全部乘上 mul（乘法对加法标记也要乘）。
update：先乘后加（先 upd2 再 upd）。
push_down：把父节点的 add/mul 下传给子结点，并重置父标记（add=0, mul=1）
标准懒标记更新，覆盖判定 + push_down + 递归 + push_up。
mdy：区间加 s。
mdy2：区间乘 s
"颜色 id 覆盖区间 [l,r]"的处理：

split(id, r+1) 与 split(id, l)：确保颜色 id 的段在 l 和 r+1 处断开（注意 split 顺序，先 r+1 再 l 是经典避免迭代器失效的顺序）。
遍历颜色 id 在 [l,r] 区间内的每一段：
若该段旧值 v 非 0：mdy2(...,2)，线段树对应区间乘 2。
若该段旧值 v 为 0：mdy(...,1)，线段树对应区间加 1。
即：覆盖旧段时，根据旧颜色是"0"还是"非0"决定对线段树做"加1"还是"乘2"。
把这段区间从颜色 id 的 set 中删除（erase(tl, itr)），然后插入新的整体段 {l, r, 1}（值是 1，表示该颜色现在完整覆盖 [l,r]）
query：线段树区间求和（带 push_down）。
初始化：每个颜色 id 的 ODT 初始为一段 {1, n, 0}（值 0 = 空）‍。
q 次操作：
若 l>r 先交换。
op==1：读 k，assign(l,r,k) 把颜色 k 覆盖到 [l,r]。
op==2：query(1,l,r) 输出区间 [l,r] 的权重和
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+10, M = 8e5+10, mod = 998244353;

struct node { int l, r, v; };
inline bool operator<(const node& x, const node& y) { return x.l < y.l; }

set<node> s[N];
auto split(int id, int x) {
    auto it = s[id].lower_bound({x, 0, 0});
    if (it != s[id].end() && it->l == x) return it;
    --it;
    int l = it->l, r = it->r, v = it->v;
    s[id].erase(it);
    s[id].insert({l, x-1, v});
    it = s[id].insert({x, r, v}).first;
    return it;
}

struct sgt { int l, r; ll s, add, mul; } tr[M];

void push_up(int k) { tr[k].s = (tr[k<<1].s + tr[k<<1|1].s) % mod; }
void upd(int k, ll add) {
    tr[k].s = (tr[k].s + add*(tr[k].r-tr[k].l+1))%mod;
    tr[k].add = (tr[k].add + add)%mod;
}
void upd2(int k, ll mul) {
    tr[k].s = (tr[k].s*mul)%mod;
    tr[k].add = (tr[k].add*mul)%mod;
    tr[k].mul = (tr[k].mul*mul)%mod;
}
void update(int k, ll add, ll mul) { upd2(k, mul); upd(k, add); }
void push_down(int k) {
    if (tr[k].l != tr[k].r) {
        update(k<<1, tr[k].add, tr[k].mul);
        update(k<<1|1, tr[k].add, tr[k].mul);
        tr[k].add = 0, tr[k].mul = 1;
    }
}
void build(int k, int l, int r) {
    tr[k].l = l, tr[k].r = r, tr[k].add = 0, tr[k].mul = 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(k<<1, l, mid); build(k<<1|1, mid+1, r);
}
void mdy(int k, int l, int r, ll s) {
    if (l <= tr[k].l && tr[k].r <= r) {
        tr[k].add = (tr[k].add + s)%mod;
        tr[k].s = (tr[k].s + s*(tr[k].r-tr[k].l+1)%mod)%mod;
        return;
    }
    push_down(k);
    int mid = (tr[k].l + tr[k].r) >> 1;
    if (l <= mid) mdy(k<<1, l, r, s);
    if (mid < r) mdy(k<<1|1, l, r, s);
    push_up(k);
}
void mdy2(int k, int l, int r, ll s) {
    if (l <= tr[k].l && tr[k].r <= r) {
        tr[k].add = (tr[k].add*s)%mod;
        tr[k].mul = (tr[k].mul*s)%mod;
        tr[k].s = (tr[k].s*s)%mod;
        return;
    }
    push_down(k);
    int mid = (tr[k].l + tr[k].r) >> 1;
    if (l <= mid) mdy2(k<<1, l, r, s);
    if (mid < r) mdy2(k<<1|1, l, r, s);
    push_up(k);
}

void assign(int l, int r, int id) {
    auto itr = split(id, r+1), itl = split(id, l), tl = itl;
    for (; itl != itr; ++itl) {
        if (itl->v) mdy2(1, itl->l, itl->r, 2);
        else mdy(1, itl->l, itl->r, 1);
    }
    s[id].erase(tl, itr);
    s[id].insert({l, r, 1});
}
ll query(int k, int l, int r) {
    if (l <= tr[k].l && tr[k].r <= r) return tr[k].s;
    int mid = (tr[k].l + tr[k].r) >> 1;
    ll res = 0;
    push_down(k);
    if (l <= mid) res = query(k<<1, l, r);
    if (mid < r) res = (res + query(k<<1|1, l, r)) % mod;
    return res;
}

int n, q;
int main() {
    fast;
    cin >> n >> q; build(1, 1, n);
    for (int i = 1; i <= n; ++i) s[i].insert({1, n, 0});
    for (int op, l, r, k; q--; ) {
        cin >> op >> l >> r;
        if (r < l) swap(l, r);
        if (op == 1) { cin >> k; assign(l, r, k); }
        else cout << query(1, l, r) << '\n';
    }
    return 0;
}