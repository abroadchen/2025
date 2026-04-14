//
// Created by Psy.C on 2026/4/13.
//
/**
v: 节点值
siz: 子树大小
key: 随机优先级（Treap特性）
l, r: 左右子树

更新节点k的子树大小
构建新节点，随机生成优先级
将以k为根的树分裂为两部分：
左树：所有值 < val
右树：所有值 ≥ val
合并两棵平衡树，保持Treap性质

插入操作：分裂后合并
查找排名：分裂后返回左子树大小+1
查找第t小的节点
pre(val): 查找val的前驱
nxt(val): 查找val的后继

设置随机种子
插入±inf作为哨兵节点
读入n和第一个数x，插入到平衡树
从第二个数开始循环：
读入x
输出x的前驱或后继中较大的那个的值
将x插入平衡树
时间复杂度：期望O(log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5, inf = 2147483647;
struct node { ll v, siz, key, l, r; } p[N];

void comb(ll k) { p[k].siz = p[p[k].l].siz + p[p[k].r].siz + 1; }
ll tot;
ll build(ll val) {
    p[++tot].v = val;
    p[tot].key = rand()*rand()%inf + 1;
    p[tot].l = p[tot].r = 0;
    p[tot].siz = 1;
    return tot;
}
void split(ll k, ll val, ll& l, ll& r) {
    if (!k) { l = r = 0; return; }
    if (p[k].v < val) {
        split(p[k].r, val, p[k].r, r);
        comb(k);
        l = k;
    } else {
        split(p[k].l, val, l, p[k].l);
        comb(k);
        r = k;
    }
}
ll merge(ll l , ll r) {
    if (!l || !r) return l + r;
    if (p[l].key < p[r].key) {
        p[l].r = merge(p[l].r, r);
        comb(l);
        return l;
    }
    p[r].l = merge(l, p[r].l);
    comb(r);
    return r;
}

ll rt;
void insert(ll val) {
    ll l, r; split(rt, val, l, r);
    rt = merge(merge(l, build(val)), r);
}
ll fdr(ll val) {
    ll x, y, ans; split(rt, val, x, y);
    ans = p[x].siz + 1; rt = merge(x, y);
    return ans;
}
ll fdv(ll t, ll k) {
    if (t == p[p[k].l].siz + 1) return k;
    if (t <= p[p[k].l].siz) return fdv(t, p[k].l);
    return fdv(t - p[p[k].l].siz - 1, p[k].r);
}
ll pre(ll val) { return fdv(fdr(val)-1, rt); }
ll nxt(ll val) { return fdv(fdr(val+1), rt); }

ll n, x;
int main() {
    fast;
    srand(time(0));
    insert(inf), insert(-inf);
    cin >> n >> x; insert(x);
    for (ll i = 2; i <= n; ++i) {
        cin >> x;
        cout << p[max(pre(x), nxt(x))].v << '\n';
        insert(x);
    }
    return 0;
}