//
// Created by Psy.C on 2026/10/6.
//
/**
标准带按秩/大小合并的并查集。
f 父节点、rk 连通块大小（初值 1，合并时 rk[x]+=rk[y]）。
find 带路径压缩，siz(x) 返回 x 所在连通块大小，merge 按大小合并（大的做父）
读入 n 个点、m 条边，每条边存 {w, i, a, b}（边权、边的编号 i、两个端点，均转 0-based）。
sort 后 reverse，即按边权从大到小排序
并查集大小为 n+m：前 n 个代表原图节点 0..n-1，后 m 个代表"边节点" n..n+m-1（第 i 条边对应节点 i+n）。
按边权降序遍历每条边，判断 siz(a) 或 siz(b) 是否为奇数：
若端点 a 或 b 所在连通块大小是奇数，则选择这条边：ans += w，并把边节点 i+n 分别与 a、b 合并。
若两端所在块大小都是偶数，则跳过（不选这条边）。
输出累加的 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

struct DSU {
    vector<int> f, rk;
    int n;
    DSU(int _n) {
        n = _n; f.resize(n); rk.resize(n, 1);
        for (int i = 0; i < n; ++i) f[i] = i;
    }

    int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
    int siz(int x) { return rk[find(x)]; }

    void merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (rk[x] < rk[y]) swap(x, y);
        f[y] = x; rk[x] += rk[y];
    }
};



int main() {
    fast;
    int n, m; cin >> n >> m;
    vector<vector<int>> v;
    for (int i = 0, a, b, w; i < m; ++i) {
        cin >> a >> b >> w; a--, b--;
        v.push_back({w, i, a, b});
    }
    ranges::sort(v); ranges::reverse(v);
    auto x = DSU(n+m);
    ll ans = 0;
    for (auto t : v) {
        int w = t[0], i = t[1], a = t[2], b = t[3];
        if (x.siz(a) % 2 == 1 || x.siz(b) % 2 == 1) {
            ans += w;
            x.merge(i+n, a); x.merge(i+n, b);
        }
    }
    cout << ans << '\n';
    return 0;
}