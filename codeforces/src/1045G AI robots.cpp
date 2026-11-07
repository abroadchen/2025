//
// Created by Psy.C on 2026/11/7.
//

/**
真正学会的起点..
每个点记录 p（位置）、r（半径/范围）、q（类别值）。
离散化：用 map 把 q 的原始值统一映射成紧凑编号 cnt，存进 id。这样后面只需处理最多 cnt 种不同的 q
cmp2 用于按 p 排序建表；cmp 用于按 r 排序做后续处理
v[id] 存的是"离散编号为 id 的点"的所有 p 坐标（升序向量）。
ranges::lower_bound(v[id], x) 返回第一个 >= x 的位置（迭代器）。
lower_bound(v[id], r+1) - lower_bound(v[id], l)：在 [l, r] 区间内的元素个数（r+1 保证右边界是闭区间）。
即：在类别 id 中统计位置处于 [l, r] 的点数，计入 ans
先按 p 排序，把每个点按其 id 归入 v[id]，保证每个向量内 p 升序。
此时每个 v[id] 是"拥有该 q 值的所有点的位置 p 的有序列表"
重新按 r 升序处理每个点 i：

先从自己类别 v[id] 中删掉自己的 p（避免和自身配对）。
对 k 遍历 [q-K, q+K] 的每一种 q 值，调用 get：
统计"q 值 = k"的点中，p 落在 [p[i]-r[i], p[i]+r[i]] 区间内的个数。
累加入 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
using namespace std;

constexpr int N = 1e5+10;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

map<int,int> mp;
int cnt;
struct node {
    int p, r, q, id;
    void in() {
        p = rd(), r = rd(), q = rd();
        if (!mp[q]) mp[q] = ++cnt;
        id = mp[q];
    }
} q[N];
bool cmp(node a, node b) { return a.r < b.r; }
bool cmp2(node a, node b) { return a.p < b.p; }

ll ans;
vector<int> v[N];
void get(int p, int l, int r) {
    if (!mp.contains(p)) return;
    int id = mp[p];
    ans += ranges::lower_bound(v[id], r+1) - ranges::lower_bound(v[id], l);
}

int n, K;
int main() {
    fast;
    n = rd(), K = rd();
    rep(i,n) q[i].in();
    sort(q+1,q+1+n,cmp2);
    rep(i,n) v[q[i].id].push_back(q[i].p);
    sort(q+1,q+1+n,cmp);
    rep(i,n) {
        v[q[i].id].erase(ranges::lower_bound(v[q[i].id], q[i].p));
        for (int k = q[i].q-K; k <= q[i].q+K; ++k)
            get(k,q[i].p-q[i].r,q[i].p+q[i].r);
    }
    cout << ans << '\n';
    return 0;
}