//
// Created by Psy.C on 2025/12/18.
//
/*
*mon[]：每个月的天数数组（索引0无意义，1月31天，2月28天，等等）
day[510]：每天的访问量数组（最多约510天）
month[15]：每月累计天数前缀和数组（15是为了安全）
ans：记录最大访问量
 *访客数量n
 *
 *month[i]表示从1月到第i月的总天数
 *
*读取访客信息：月份m、日期d、访问人数p、停留天数t
m--：将月份转换为0基索引（便于计算）
month[m] + d：将(m,d)转换为一年中的第几天
+ 100：加上偏移量确保所有日期都是正数（处理跨年情况）
l = r - t：计算入住日期（开始日期）
r：离开日期（结束日期的后一天）
 *
*对于访客停留的每一天j（从l到r-1）
将该访客带来的访问量p加到day[j]上
更新最大访问量ans
 *
*时间复杂度：O(n × t_max)，其中t_max是最大停留天数
空间复杂度：O(天数范围)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int mon[] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
}, day[510], month[15], ans;
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int n; cin >> n;
    int l = 0, r = 0;
    for (int i = 1; i <= 12; ++i) month[i] = month[i-1] + mon[i];
    for (int i = 1, m, d, p, t; i <= n; ++i) {
        cin >> m >> d >> p >> t; m--;
        r = month[m] + d + 100; l = r - t;
        for (int j = l; j < r; ++j) {
            day[j] += p;
            ans = max(ans, day[j]);
        }
    }
    cout << ans << '\n';
    return 0;
}