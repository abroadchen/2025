//
// Created by Psy.C on 2025/10/14.
//
/*
*读取n（目标数量）、k（最少需要击中的目标数）
读取eps（最大允许失败概率，以千分之一为单位，转换为小数）
读取发射器位置(x0, y0)
读取目标位置到整数对向量中
 *
*计算从发射器到每个目标的欧几里得距离
索引0未使用，目标编号从1到n
 *
*创建DP表，其中dp[i][j]表示在前i个目标中恰好击中j个目标的概率
初始状态下击中0个目标的概率为1.0
*计算击中第i个目标的概率：
如果距离≤功率(m)，概率=1.0（保证命中）
否则，概率=exp(1 - (距离/功率)²)
*据当前目标是否被击中更新概率：
dp[i][j] = P(未命中) × dp[i-1][j] + P(命中) × dp[i-1][j-1]
*计算击中少于k个目标的总概率
如果失败概率在可接受范围内则返回true
 *
 *
 */
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long double ld;
typedef pair<int, int> pii;

void solve() {
    int n, k; cin >> n >> k;
    double eps; cin >> eps; eps /= 1000.0;
    int x0, y0; cin >> x0 >> y0;
    vector<pii> segs(n);
    for (auto& x : segs) cin >> x.first >> x.second;
    vector<ld> dist(n + 1, 0);
    for (int i = 0; i < n; ++i)
        dist[i + 1] = sqrt((segs[i].first - x0) * (segs[i].first - x0) + (segs[i].second - y0) * (segs[i].second - y0));

    double l(0), r(10000);//初始化功率水平的搜索范围
    auto check = [&](ld m) {//检查功率水平'm'是否满足约束条件
        vector<vector<ld>> dp(n + 1, vector<ld>(n + 1, 0.0));
        dp[0][0] = 1.0;
        for (int i = 1; i <= n; ++i) {
            double prob = (dist[i] <= m ? 1.0 : exp(1.0 - (dist[i] * dist[i])/(m*m)));
            for (int j = 0; j <= i; ++j)
                dp[i][j] = dp[i - 1][j] * (1.0 - prob) + (j - 1 >= 0 ? dp[i - 1][j - 1] * prob : 0.0);
        }
        double ans(0);
        for (int i = 0; i < k; ++i) ans += dp[n][i];
        return (ans <= eps);
    };
    for (int i = 0; i < 100; ++i) {
        double m = l + (r - l) / 2;
        if (check(m)) r = m;
        else l = m;
    }
    cout << fixed << setprecision(17) << (l + r) / 2.0;
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    solve();
    return 0;
}