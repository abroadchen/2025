//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
l, r：区间下标（这里指值范围）；
num：该值区间内当前有效的物品数量；
sum：该值区间内所有物品的值之和。
注意：num 存的是数量，sum 存的是 数量×该值 的累加。因为同一"值"上可能有多个物品。
in[i]：位置 i 开始生效的物品 (值, 数量)（即某物品第一个出现位置 l 这里）；
out[i]：位置 i 失效的物品 (值, 数量)（即末尾 r 要在这里被移除）
参数 num 是增量（数量，可为负）‍，pos 是值/权值位置。

到达叶子（值 = pos 的那个桶）时，num 数量 += 增量，sum 增量 = 增量 × 该值；
否则向左右递归（pos <= mid 走左，else 走右），回溯时 push_up 合并
若当前节点是叶子（值区间只剩一个点），说明这 num 个物品都落在这个值上，返回 值 × min(剩余需求数, 该桶数量)；
若左子树的物品总数 ≥ num，说明前 num 小全在左子树，递归左；
否则，左子树全要（p[cur<<1].sum），再从右子树里取剩下的 num - 左数量 个，递归右。
这本质是一个 权值线段树上二分找前 k 小、并累加和 的过程
到位置 i：先把这一位置才开始生效的物品加入树；
此时树上恰好存有在 i 处仍然有效的所有物品 → query(k, 1) 求最小的 k 个值之和，累加到 ans；
再把这一位置应失效的物品移除（update(-fst, ...) 即数量减回去）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define ii pair<int,int>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 1e6+1e2;

struct node { int l, r; ll sum, num; } p[N<<2];

int n;
vector<ii> in[N], out[N];
void init() { rep(i,n+1) { in[i].clear(); out[i].clear(); } }

inline void push_up(int cur) {
    p[cur].num = p[cur<<1].num + p[cur<<1|1].num;
    p[cur].sum = p[cur<<1].sum + p[cur<<1|1].sum;
}
inline void build(int l, int r, int cur) {
    p[cur].l = l; p[cur].r = r; p[cur].sum = 0; p[cur].num = 0;
    if (l == r) return;
    build(l, mid, cur<<1); build(mid+1, r, cur<<1|1);
}
inline void update(int num, int pos, int cur) {
    int l = p[cur].l, r = p[cur].r;
    if (l == r) { p[cur].num += num; p[cur].sum += (ll)num*(ll)l; return; }
    if (pos <= mid) update(num, pos, cur<<1);
    else update(num, pos, cur<<1|1);
    push_up(cur);
}
inline ll query(int num, int cur) {
    int l = p[cur].l, r = p[cur].r;
    if (l == r) return (ll)l*min(p[cur].num, (ll)num);
    if (num <= p[cur<<1].num) return query(num, cur<<1);
    return p[cur<<1].sum + query(num-p[cur<<1].num, cur<<1|1);
}

int k, m;
int main() {
    fast;
    int l, r, x, y;
    while (cin >> n >> k >> m) {
        init();
        for (int i = 1; i <= m; i++) {
            cin >> l >> r >> x >> y;
            in[l].emplace_back(x,y);
            out[r].emplace_back(x,y);
        }
        ll ans = 0; build(1,N,1);
        for (int i = 1; i <= n; i++) {
            for (auto &[fst, snd] : in[i])
                update(fst, snd, 1);
            ans += query(k, 1);
            for (auto &[fst, snd] : out[i])
                update(-fst, snd, 1);
        }
        cout << ans << '\n';
    }
    return 0;
}