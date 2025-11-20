//
// Created by Psy.C on 2025/11/20.
//
/*
*N = 501: 数组大小常量
dp[N]: 动态规划数组，存储每个物品的最小成本
n: 物品数量
l, w: 临时变量，用于读取长度和宽度
h[N]: 存储每个物品的高度
a[N]: 存储每个物品的周长（初始化为0）
q: 查询数量
p: 价格
ans: 最终答案
 *
*(a[i]-1)/w + 1: 计算需要的宽度单位数（向上取整）
l/h[i]: 计算在长度l内可以放置多少层该物品
((a[i]-1)/w)/(l/h[i]) + 1: 计算需要的总块数（向上取整）
乘以单价p得到总成本
 */
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 501;
int dp[N], n, l, w, h[N], a[N], q, p, ans;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(dp, 0x3f, sizeof(dp));
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> l >> w >> h[i], a[i] += (l+w)*2;
    cin >> q;
    while (q--) {
        cin >> l >> w >> p;
        for (int i = 1; i <= n; ++i) if (l >= h[i]) {
            dp[i] = min(dp[i], (((a[i]-1)/w)/(l/h[i])+1)*p);
        }
    }
    for (int i = 1; i <= n; ++i) ans += dp[i];
    cout << ans;
    return 0;
}