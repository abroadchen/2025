//
// Created by Psy.C on 2026/10/13.
//
/**
树有 n 个点、n-1 条边；每条边存两端点 fr, to、以及两端点权值中的较小值 mn 和较大值 mx。

第一遍排序用 mn 降序（mn 大的在前），用于求"路径最小值边之和"。
第二遍排序用 mx > （按 mx 升序）‍，用于求"路径最大值边之和"
并查集带路径压缩；sz[i] 记录以 i 为根的连通块点数。合并时把两个块拼一起，sz 累加（小团并入大团）
按 mn 从大到小依次合并边。当合并当前边时，它的两端点所在连通块为 A、B，大小 a*b；这条边mn恰恰是"跨越这两块之间所有路径的最小边权"，因为此时所有比它大的边都已被合并（已连接，说明路径中最小权值就是当前这个 mn）。所以贡献是 sz[fr] * sz[to] * mn。

遍历完所有边后，mn 就累加了"所有点对路径的最小值边"总和
重置并查集后，按 mx 从小到大合并。此时当前边是"跨越两块之间所有路径的最大边权"（因为比它小的边已全部合并），贡献为 sz[fr] * sz[to] * mx。最终 mx 为所有点对路径的最大值边总和
最终输出 （路径最大值和 − 路径最小值和）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define ll long long
using namespace std;

constexpr int N = 1e6+51;

struct edge {
    int fr, to, mn, mx;
    bool operator<(const edge& o) const { return mn > o.mn; }
    bool operator>(const edge& o) const { return mx < o.mx; }
} ed[N];

int fa[N];
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int sz[N];
inline void merge(int x, int y) {
    x = find(x), y = find(y);
    x != y ? fa[y] = x, sz[x] += sz[y], sz[y] = 0 : 1;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int x[N], fr, to;
ll mn, mx;
int main() {
    fast;
    int n = rd();
    rep(i,1,n) x[i] = rd(), fa[i] = i, sz[i] = 1;
    rep(i,1,n-1) {
        fr = rd(), to = rd();
        ed[i] = {fr, to, min(x[fr], x[to]), max(x[fr], x[to])};
    }
    sort(ed+1, ed+n);
    rep(i,1,n-1) {
        mn += 1ll*sz[find(ed[i].fr)]*sz[find(ed[i].to)]*ed[i].mn;
        merge(ed[i].fr, ed[i].to);
    }
    sort(ed+1, ed+n, greater());
    rep(i,1,n) fa[i] = i, sz[i] = 1;
    rep(i,1,n-1) {
        mx += 1ll*sz[find(ed[i].fr)]*sz[find(ed[i].to)]*ed[i].mx;
        merge(ed[i].fr, ed[i].to);
    }
    cout << mx-mn << '\n';
    return 0;
}