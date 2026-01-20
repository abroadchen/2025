//
// Created by Psy.C on 2026/1/20.
//
/**
 * n（物品数量）和d（每日重量增量上限）
 *dp[0] = 1：重量0总是可达的（不选任何物品）
 *
*DP阶段：O(n × 总重量)
贪心阶段：O(天数 × 重量范围)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, d; cin >> n >> d;
    int dp[51*10001]={}; dp[0] = 1;
    for (int i = 0, x, sum = 0; i < n; ++i) {
        cin >> x;//当前物品重量
        for (int j = sum += x; j >= x; --j)//从当前总重量向下遍历
            if (dp[j-x]) dp[j] = 1;//如果重量j-x可达，则j也可达
    }
    int w = 0, day = 0;//初始重量为0，天数为0
    while (true) {//找不到更重的
        int j = w + d;//从当前重量w+d开始寻找（最大可能增加量）
        while (!dp[j] && j > w) j--;//向下搜索第一个可达的重量
        if (j == w) break;//没找到更重的
        w = j;//更新当前重量
        day++;
    }
    cout << w << ' ' << day << '\n';
    return 0;
}