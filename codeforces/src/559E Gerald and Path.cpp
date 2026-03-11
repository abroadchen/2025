//
// Created by Psy.C on 2026/3/11.
//
/**
v: 存储所有关键点，用于离散化
find: 将原坐标映射到离散化后的索引
读入n个区间
每个区间由中心点a和半径l构成
d[i].l = a-l, d[i].r = a+l, d[i].p = a
将所有关键点加入离散化数组
m: 离散化后的最大索引
按特殊点p排序区间

f[i][j]: 前i个区间处理完后，覆盖到位置j的最大收益
g[j]: 辅助数组，临时计算状态
复制上一行状态
初始化：在位置p放置，从位置l开始覆盖
向前搜索，更新覆盖范围
扩展到区间的右端点
从右向左更新状态
传递覆盖状态
更新区间[p,r]内的状态
从位置p扩展到r
确保状态单调性

排序和离散化：O(n log n)
DP计算：O(n²m)
总体：O(n²m)，其中m是离散化后的大小
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105, inf = 1e9;

struct node {
    int l, r, p;
    bool operator<(const node &o) const {
        return p < o.p;
    }
} d[N];
vector<int> v;
void find(int& x) { x = ranges::lower_bound(v, x) - v.begin(); }

int n, f[N][N*3], g[N*3];
int main() {
    fast;
    cin >> n; v.push_back(-inf);
    for (int i = 1, a, l; i <= n; ++i) {
        cin >> a >> l;
        d[i] = {a-l, a+l, a};
        v.push_back(d[i].l); v.push_back(d[i].r);
        v.push_back(d[i].p);
    }
    ranges::sort(v); v.erase(ranges::unique(v).begin(), v.end());
    for (int i = 1; i <= n; ++i)
        find(d[i].l), find(d[i].r), find(d[i].p);
    int m = v.size() - 1;
    sort(d + 1, d + n + 1);
    for (int i = 1; i <= n; ++i) {
        memcpy(f[i], f[i-1], sizeof *f);
        int l = d[i].l, r = d[i].r, p = d[i].p;
        memset(g, 0, sizeof g);
        int x = p;
        g[x] = f[i-1][l] + v[x] - v[l];
        for (int j = i - 1; j; --j) {
            x = max(x, d[j].r);
            g[x] = max(g[x], f[j-1][l] + v[x] - v[l]);
        }
        for (int j = m; j >= l; --j) {
            f[i][j] = max(f[i][j], g[j]);
            g[j-1] = max(g[j-1], g[j] - v[j] + v[j-1]);
        }
        for (int j = p; j <= r; ++j)
            f[i][j] = max(f[i][j], f[i-1][p] + v[j] - v[p]);
        for (int j = 1; j <= m; ++j)
            f[i][j] = max(f[i][j], f[i][j-1]);
    }
    cout << f[n][m] << '\n';
    return 0;
}