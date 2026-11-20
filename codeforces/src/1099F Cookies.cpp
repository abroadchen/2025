//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
modify(u,l,r,pos,cnt)

单点修改：在叶子 pos 加 cnt 个数。
sum[u] += cnt*pos：这一桶的总耗时。
num[u] += cnt：这一桶的总数。
up(u) / build(u,l,r)

up：父节点 num、sum 取左右子之和。
build：把值域 [1, N-5] 全部清零建树（N=1e6，值域按时间分桶）。
qry(u,l,r,s) —— 最 slick 处

功能：给定预算 s（剩余时间），贪心地尽量多取：优先取耗时小的桶，求最多能取到多少个数
逻辑：左侧（时间更小）优先取完，剩下时间再取右侧——这是最优贪心（耗时小的先填满）
(A)(D)：进点加权、出点减权——维护"从根到 u 这条链上所有点的集合"（路径上只能走一条边，但 ? 的语义中这里用全局集合叠加了链上各点）。
(B)：用全局集合在剩余时间 rem 内做最大收割。
(C)：遍历儿子，扣除走到该儿子的路径开销 snd（边权 ×2），递归。
(D) 回溯时把点 u 移除，保持集合只含当前路径。
(E)：根节点特殊处理，因为根没有"走向"，可整体最大值。
(F)：对每个节点返回「本站值」和「子树统计值」的较大者
建图用邻接表 to[p]：节点 i 挂在父 p 下，路径耗时 l*2。
从根跑 dfs(1, T)，返回最终答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
#define ii pair<int, int>
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 1e6+5;

struct sgt {
    ll num[N<<2], sum[N<<2];
    void up(int u) {
        num[u] = num[u<<1]+num[u<<1|1];
        sum[u] = sum[u<<1]+sum[u<<1|1];
    }
    void build(int u, int l, int r) {
        sum[u] = num[u] = 0;
        if (l == r) return;
        build(u<<1,l,mid); build(u<<1|1,mid+1,r);
        return up(u);
    }
    ll qry(int u, int l, int r, ll s) {
        if (sum[u] == 0) return 0;
        if (l == r) return min(s/l, num[u]);//只剩一个桶:能取 min(时间/单价, 数量)
        if (sum[u<<1] >= s) return qry(u<<1,l,mid,s);
        return num[u<<1]+qry(u<<1|1,mid+1,r,s-sum[u<<1]);//左子树全取,剩余时间走右
    }
    void modify(int u, int l, int r, int pos, ll cnt) {
        if (l == r) { num[u] += cnt; sum[u] += cnt*pos; return; }
        if (pos <= mid) modify(u<<1,l,mid,pos,cnt);
        else modify(u<<1|1,mid+1,r,pos,cnt);
        return up(u);
    }
} tr;

int t[N], x[N];
vector<ii> to[N];
ll dfs(int u, ll rem) {
    tr.modify(1,1,N-5,t[u],x[u]);//(A)把当前点 u 加入全局集合
    ll res = tr.qry(1,1,N-5, rem), m1 = 0, m2 = 0;//(B)在剩余时间 rem 内的最大可取数
    for (auto [fst, snd] : to[u]) {// (C)遍历子节点
        if (rem - snd <= 0) continue;//扣除走子节点的路径开销,装不下就跳过
        ll t = dfs(fst, rem-snd);
        if (t >= m1) m2 = m1, m1 = t;//记录子树里最大、次大返回值
        else if (t > m2) m2 = t;
    }
    tr.modify(1,1,N-5,t[u],-x[u]);//(D)回溯:把这个点拿出全局集合
    if (u == 1) res = max(res, m1);// (E)根:可直接取全体中最大
    return max(res, m2);//(F)返回 max(本站结果, 子树统计)
}

int n;
ll T;
int main() {
    fast;
    cin >> n >> T; tr.build(1,1,N-5);
    rep(i,n) cin >> x[i];
    rep(i,n) cin >> t[i];
    for (int i = 2, p, l; i <= n; ++i) {
        cin >> p >> l;
        to[p].emplace_back(i,l*2);
    }
    cout << dfs(1,T) << '\n';
    return 0;
}