//
// Created by Psy.C on 2025/11/15.
//
/*
*定义树状数组类Nw(Fenwick Tree)
n：数组大小
bit：树状数组存储
构造函数初始化大小和数组
*在位置i添加值val
树状数组的标准更新操作
i & -i获取i的最低位1所代表的值
*查询前缀和[1,i]
树状数组的标准查询操作
 *
*定义线段树类
tree：存储区间最大值
lazy：懒惰标记数组
构造函数初始化大小和数组
*下传懒惰标记
如果当前节点有标记，将其值加到节点上
如果不是叶子节点，将标记传递给子节点
*区间更新[L,R]加上val
标准线段树区间更新实现
 *单点更新：将位置idx的值设为val
 *区间查询[L,R]的最大值
 *对外接口函数，简化调用
 *
*c：存储原始数组
s：前缀和数组，s[i]表示c[1]到c[i]的和
 *
*e：事件数组，e[r]存储所有在位置r结束的区间操作
读入m个操作：区间[l,r]增加权值p
 *
*创建树状数组f和线段树seg
初始化线段树第一个位置为0
dp：动态规划数组
g：辅助数组，g[i] = dp[i] + s[i]
 *
 *遍历每个位置i（从1到n）
*处理所有在位置i结束的区间操作：
在树状数组中添加区间更新：[1,u]增加p
在线段树中更新区间[1,u]增加p
*查询线段树[1,i]区间的最大值，减去前缀和得到当前最优解
dp[i]取前一个最优解和当前解的最大值
*更新辅助数组g
如果不是最后一个位置，查询树状数组在i+1位置的值
在线段树中更新点i+1的值
 *
 *时间复杂度：O((n+m)log n)
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define rep1(i,n) for(int i=1;i<=(n);++i)
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

typedef long long ll;
const int N = 2e5+5;
const ll inf = 1e18;

class Nw {
public:
    int n;
    vector<ll> bit;
    Nw(int size) { n = size; bit.resize(n + 1, 0); }
    void add(int i, ll val) {
        while (i <= n) { bit[i] += val; i += (i & -i); }
    }
    ll point_query(int i) {
        ll res(0);
        while (i) { res += bit[i]; i -= (i & -i); }
        return res;
    }
};

class SegmentTree {
public:
    int n;
    vector<ll> tree, lazy;
    SegmentTree(int size) {
        n = size;
        tree.resize(4*n, -inf);
        lazy.resize(4*n, 0);
    }
    void push(int rt, int l, int r) {
        if (lazy[rt] != 0) {
            tree[rt] += lazy[rt];
            if (l != r) {
                lazy[rt<<1] += lazy[rt];
                lazy[rt<<1|1] += lazy[rt];
            }
            lazy[rt] = 0;
        }
    }
    void update_range(int rt, int l, int r, int L, int R, ll val) {
        push(rt, l, r);
        if (L > r || R < l) return;
        if (L <= l && r <= R) {
            lazy[rt] += val;
            push(rt, l, r);
            return;
        }
        int mid = (l+r)>>1;
        update_range(rt<<1, l, mid, L, R, val);
        update_range(rt<<1|1, mid+1, r, L, R, val);
        tree[rt] = max(tree[rt<<1], tree[rt<<1|1]);
    }
    void update_point(int rt, int l, int r, int idx, ll val) {
        push(rt, l, r);
        if (l == r) { tree[rt] = val; return; }
        int mid = (l+r)>>1;
        if (idx <= mid) update_point(rt<<1, l, mid, idx, val);
        else update_point(rt<<1|1, mid+1, r, idx, val);
        tree[rt] = max(tree[rt<<1], tree[rt<<1|1]);
    }
    ll query(int rt, int l, int r, int L, int R) {
        push(rt, l, r);
        if (L > r || R < l) return -inf;
        if (L <= l && r <= R) return tree[rt];
        int mid = (l+r)>>1;
        ll left_val = query(rt<<1, l, mid, L, R),
        right_val = query(rt<<1|1, mid+1, r, L, R);
        return max(left_val, right_val);
    }
    void update_range(int L, int R, ll val) { update_range(1, 1, n, L, R, val); }
    void update_point(int idx, ll val) { update_point(1, 1, n, idx, val); }
    ll query(int L, int R) { return query(1, 1, n, L, R); }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<ll> c(n + 1), s(n + 1, 0);
    rep1(i,n) { cin >> c[i]; s[i] = s[i - 1] + c[i]; }
    vector<vector<pair<int, ll>>> e(n + 1);
    rep(i,m) {
        int l, r; ll p; cin >> l >> r >> p;
        e[r].push_back({l, p});
    }
    Nw f(n);
    SegmentTree seg(n);
    seg.update_point(1, 0);
    vector<ll> dp(n + 1, 0), g(n + 1, 0);

    rep1(i,n) {
        for (auto& x : e[i]) {
            int u = x.first; ll p = x.second;
            f.add(1, p);
            if (u + 1 <= n) f.add(u + 1, -p);
            seg.update_range(1, u, p);
        }
        ll ans = seg.query(1, i) - s[i];
        dp[i] = max(dp[i - 1], ans);
        g[i] = dp[i] + s[i];
        if (i < n) {
            ll cur = f.point_query(i + 1);
            seg.update_point(i + 1, g[i] + cur);
        }
    }
    cout << dp[n] << '\n';
    return 0;
}