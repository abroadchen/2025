//
// Created by Psy.C on 2026/1/10.
//
/**
 * n（节点数）、k（参数）、ans（答案，初始化为0）
 * pair 包含邻居节点和边权
 *
*外层循环：i 从 1 到 n
内层循环：j 从 i+1 到 n（避免重复处理无向边）
 *
*如果 k=1：
循环每个节点，累加第一个邻居的边权（v[i][0].second）
输出平均值（总和除以节点数）
返回结束程序
*如果 k=2：
循环每个节点 i
views::values：C++20 范围视图，提取 pair 的第二个元素（边权）
计算节点 i 的邻居数量 cnt 和边权总和 sum
ans += (cnt - 1) * sum：每个节点贡献 (邻居数-1) × 邻居权值和
输出结果除以 n*(n-1)/2（所有可能的边数）
*对于 k≥3 的情况：
遍历所有节点和其所有边权值
累加所有边权到 ans
输出平均值（总和除以节点数）
 *
 *v[i] | views::values：管道操作符，将邻接表转换为只包含值的视图
 */
#include <iostream>
#include <ranges>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 2005
#define rep(i,n) for (int i=1; i<=(n); ++i)
using namespace std;


signed main() {
    fast;
    int n, k, ans = 0; cin >> n >> k;
    vector<pair<int, int>> v[N];
    rep(i,n) for (int j = i + 1, x; j <= n; ++j) {
        cin >> x;//读入边权
        if (x == -1) continue;//如果权重为-1则跳过
        v[i].emplace_back(j, x);//在节点i的邻接表中添加(j, x)
        v[j].emplace_back(i, x);
    }
    if (k == 1) {
        rep(i,n) ans += v[i][0].second;
        cout << ans / n << '\n';
        return 0;
    }
    if (k == 2) {
        rep(i,n) {
            int cnt = 0, sum = 0;
            for (const auto &val: v[i] | views::values) {
                cnt++, sum += val;
            }
            ans += (cnt - 1) * sum;
        }
        cout << ans / (n * (n - 1) / 2) << '\n';
        return 0;
    }
    rep(i,n) for (const auto &val: v[i] | views::values) ans += val;
    cout << ans / n << '\n';
    return 0;
}