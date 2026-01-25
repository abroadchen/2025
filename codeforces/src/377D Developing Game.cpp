//
// Created by Psy.C on 2026/1/23.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 300010
#define inf 300000
#define ii pair<int, int>
using namespace std;

struct node { int l, r, v; } a[N];//左端点l、右端点r、中间值v
struct sgt {
#define ls(u) (u<<1)//左子节点索引 当前节点编号×2
#define rs(u) (u<<1|1)
#define mid ((tr[u].l + tr[u].r)>>1)//区间中点
    struct node {
        int l{}, r{}, tag{};//区间左右端点和懒惰标记
        ii mx;//最大值和对应位置的对
    } tr[N<<2];

    void push_up(const int u) {//更新当前节点最大值
        tr[u].mx = max(tr[ls(u)].mx, tr[rs(u)].mx);
    }
    void build(const int u, const int l, const int r) {
        tr[u] = {l, r};//初始化节点的区间
        if (l == r) return tr[u].mx.second = l, void();//叶子节点，设置位置为l
        build(ls(u), l, mid); build(rs(u), mid + 1, r);//递归构建左右子树
        push_up(u);//合并子节点信息
    }
    void calc(const int u, const int k) {//给节点u增加k
        tr[u].mx.first += k; tr[u].tag += k;//更新最大值 更新懒惰标记
    }
    void pushdown(const int u) {
        if (tr[u].tag) {
            calc(ls(u), tr[u].tag); calc(rs(u), tr[u].tag);//传播到左右子节点
            tr[u].tag = 0;//清除当前节点标记
        }
    }
    void modify(const int u, const int l, const int r, const int k) {//在区间[l,r]增加k
        if (l <= tr[u].l && tr[u].r <= r) return calc(u, k);//直接更新
        pushdown(u);//传播懒惰标记
        if (l <= mid) modify(ls(u), l, r, k);//递归修改左子树
        if (r > mid) modify(rs(u), l, r, k);
        push_up(u);//更新父节点
    }
#undef ls
#undef rs
#undef mid
} T;

int main() {
    fast;
    int n; cin >> n;
    vector<ii> q[N];//事件数组，用于扫描线算法
    for (int i = 1, l, r, v; i <= n; ++i) {
        cin >> l >> v >> r;
        a[i] = {l, r, v};
        q[l].emplace_back(1, i);//在位置l添加开始事件（+1）
        q[v+1].emplace_back(-1, i);//在位置v+1添加结束事件（-1）
    }
    T.build(1, 1, inf);
    int ans = 0, al = 0, ar = 0;//最优区间坐标
    for (int i = 1; i <= inf; ++i) {
        for (auto [fst, snd] : q[i]) {///处理位置i的所有事件
            const auto t = a[snd];
            T.modify(1, t.v, t.r, fst);//根据事件类型修改线段树区间[t.v, t.r]
        }
        if (auto [fst, snd] = T.tr[1].mx; fst > ans) {//获取全局最大值并更新答案
            ans = fst;
            al = i, ar = snd;
        }
    }
    cout << ans << '\n';//最大重叠数量
    for (int i = 1; i <= n; ++i) if (a[i].l <= al && ar <= a[i].r &&
        al <= a[i].v && a[i].v <= ar) cout << i << ' ';//在最优区间[al, ar]内的区间并输出编号
    return 0;
}