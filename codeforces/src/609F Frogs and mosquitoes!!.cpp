//
// Created by Psy.C on 2026/3/23.
//
/**
b[i]：第i个区间的起始位置
len[i]：第i个区间的长度
ret[N]：排序后的区间索引
线段树节点，存储区间范围和最大值
更新父节点的最大值
构建线段树，叶子节点存储区间右端点（起始位置+长度）
修改操作：在指定位置增加长度val
查询操作：找到包含位置p的区间编号

n：区间数量
m：操作数量
to[N]：原始索引到排序后索引的映射
tot[N]：每个区间被扩展的次数
s：存储待处理的扩展请求

查询位置p属于哪个区间
如果不属于任何区间，将请求存入multiset
否则，对该区间扩展x长度，并增加计数
检查multiset中是否有请求现在落在该区间范围内，如果有则处理它们
O((n + m) log n)，其中n是区间数量，m是操作数量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 4e5+5;
int b[N], len[N], ret[N];
namespace sgt {
    struct node {
        int l, r, mx;
#define l(x) tr[x].l
#define r(x) tr[x].r
#define mxx(x) tr[x].mx
    } tr[N<<1];
    void push_up(int x) { mxx(x) = max(mxx(x<<1), mxx(x<<1|1)); }
    void build(int x, int l, int r) {
        l(x) = l, r(x) = r;
        if (l == r) { mxx(x) = b[ret[l]] + len[ret[l]]; return; }
        int mid = (l + r) >> 1;
        build(x<<1, l, mid); build(x<<1|1, mid+1, r);
        push_up(x);
    }
    void modify(int x, int p, int val) {
        if (!l(x) || !r(x)) return;
        if (l(x) == r(x) && l(x) == p) {
            mxx(x) += val;
            len[ret[l(x)]] += val;
            return;
        }
        int mid = (l(x) + r(x)) >> 1;
        if (p <= mid) modify(x<<1, p, val); else modify(x<<1|1, p, val);
        push_up(x);
    }
    int query(int x, int p) {
        if (l(x) == r(x)) {
            if (b[ret[l(x)]] <= p && b[ret[l(x)]] + len[ret[l(x)]] >= p)
                return ret[l(x)];
            return -1;
        }
        if (mxx(x<<1) >= p) return query(x<<1, p);
        return query(x<<1|1, p);
    }
}


int n, m, to[N], tot[N];
ii t[N];
multiset<ii> s;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> b[i] >> len[i]; t[i] = {b[i], i};
    }
    sort(t + 1, t + n + 1);
    for (int i = 1; i <= n; ++i) {
        ret[i] = t[i].second; to[ret[i]] = i;
    }
    sgt::build(1, 1, n);
    for (int i = 1, p, x; i <= m; ++i) {
        cin >> p >> x;
        int id = sgt::query(1, p);
        if (!~id) {
            s.insert({p, x});
            continue;
        }
        tot[id]++; sgt::modify(1, to[id], x);
        auto it = s.lower_bound({b[id], -1});
        while (it != s.end() && it->first <= b[id] + len[id]) {
            int tx = it->second;
            tot[id]++; s.erase(it);
            sgt::modify(1, to[id], tx);
            it = s.lower_bound({b[id], -1});
        }
    }
    for (int i = 1; i <= n; ++i)
        cout << tot[i] << ' ' << len[i] << '\n';
    return 0;
}