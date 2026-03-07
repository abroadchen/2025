//
// Created by Psy.C on 2026/3/7.
//
/**
n：输入的数据项数量
T：时间段总数
g[N]：二维向量数组，g[i]存储第i个时间段的数据
将g[t]按降序排列
以步长2遍历当前时间t的数据
如果还有配对元素：将两个相邻元素相加，结果放入下一时间t+1
如果只剩一个元素：直接将该元素放入下一时间t+1
输出T时刻后g[T]中的第一个元素（通常是最大值）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int n, T;
vector<int> g[N];
int main() {
    fast;
    cin >> n >> T;
    for (int i = 1, t, q; i <= n; ++i) {
        cin >> t >> q; g[t].push_back(q);
    }
    for (int t = 1; t <= T; ++t) {
        ranges::sort(g[t], greater<>());
        for (int i = 0; i < g[t].size(); i += 2) {
            if (i + 1 < g[t].size())
                g[t+1].push_back(g[t][i] + g[t][i+1]);
            else
                g[t+1].push_back(g[t][i]);
        }
    }
    cout << g[T][0] << '\n';
    return 0;
}