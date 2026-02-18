//
// Created by Psy.C on 2026/2/18.
//
/**
n: 节点数
p[N]: 位置数组
b[N]: 权值数组
m: 目标距离
pre[N]: 前驱数组，用于路径重构
dp[N]: DP数组

dp[i]: 到达i的代价
sqrt(abs(p[j]-p[i]-m))*x: 距离惩罚项
b[j]: 节点j的收益

二分搜索：O(log(1/ε))
DP：O(n²)
总体：O(n² * log(1/ε))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define inf 1e19
#define eps 1e-9
using namespace std;
constexpr int N = 1001;

int n, p[N], b[N], m, pre[N];
double dp[N];
bool check(const double x) {
    for (int i = 1; i <= n; ++i) dp[i] = inf; dp[0] = 0.;
    for (int i = 0; i <= n; ++i)//枚举起始节点
        for (int j = i + 1; j <= n; ++j) {//枚举终点
            if (const double t = dp[i]+sqrt(abs(p[j]-p[i]-m))*x-b[j]; dp[j] > t) {//新路径更优
                dp[j] = t; pre[j] = i;
            }
        }
    if (dp[n] < 0) return false;//最终代价为负
    return true;
}

void dfs(const int x) {
    if (!x) return;//到达起点0
    dfs(pre[x]);//递归访问前驱
    cout << x << ' ';//输出当前节点
}


int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> p[i] >> b[i];
    double l = 0, r = 1e6;
    while (abs(l - r) > eps) {
        if (const double mid = (l + r) / 2.; check(mid)) r = mid;
        else l = mid;
    }
    dfs(n);//从终点n开始重构路径并输出
    return 0;
}