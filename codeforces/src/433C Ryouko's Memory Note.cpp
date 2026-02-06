//
// Created by Psy.C on 2026/2/6.
//
/**
n（节点数）和m（序列长度）
res：初始总距离
g[N]：邻接表，存储每个节点的相邻节点

读入序列a
对于相邻不相等的元素，在邻接表中建立双向边
累加初始相邻元素的距离和
构建图结构，相邻不同元素之间连边

对于有相邻节点的节点i
找到相邻节点的中位数（最优替换值）
计算将所有相邻节点都改为中位数时的总距离变化
更新全局最优解

时间复杂度
建图：O(m)
对每个节点排序：O(k log k)，k为相邻节点数
总体：O(m + n × k log k)
空间复杂度：O(n + m)
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100007
using namespace std;


int main() {
    fast;
    int n, m, a[N]; cin >> n >> m;
    ll res = 0;
    vector<int> g[N];
    for (int i = 1; i <= m; ++i) {
        cin >> a[i];
        if (i > 1 && a[i] != a[i-1]) {
            g[a[i]].push_back(a[i-1]);
            g[a[i-1]].push_back(a[i]);
            res += abs(a[i] - a[i-1]);
        }
    }
    ll ans = res;
    for (int i = 1; i <= n; ++i) {
        if (!g[i].empty()) {
            ll  t = res;
            ranges::sort(g[i]);
            const int mid = g[i][g[i].size()/2];
            for (int j = 0; j < g[i].size(); ++j)
                t += abs(mid - g[i][j]) - abs(i - g[i][j]);
            ans = min(ans, t);
        }
    }
    cout << ans << '\n';
    return 0;
}