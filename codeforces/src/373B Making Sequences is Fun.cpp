//
// Created by Psy.C on 2026/1/22.
//
/**
* w: 总预算
m: 起始数字
k: 每位数字的成本
 *
*外层无限循环，用i表示当前处理的数字位数

条件分支1：if (w - (num - m) * i >= 0)

含义：检查预算是否足够打印[m, num)范围内所有i位数
(num - m)：当前范围内数字的个数
i：每个数字的位数
i * (num - m)：打印这个范围内所有数字的总成本
 *
 *时间复杂度：O(log m)，主要是计算位数和分段处理的时间
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll w, m, k; cin >> w >> m >> k;
    w /= k;//将预算按每位数字成本标准化
    int len = 0;
    for (ll t = m; t; t /= 10) len++;//计算位数
    ll num = 1, i, res;
    for (i = 1; i <= len; ++i) num *= 10;//找到第一个比m大的10的幂次
    for (res = 0, i = len; ; ++i) {
        if (w - (num - m) * i >= 0) {
            w -= i * (num - m);//减去花费的预算
            res += num - m;//增加打印的数字个数
            m = num;//更新起始数字
            num *= 10;//更新范围上限
        } else {//预算不够打印整个i位数区间
            res += w / i;//用剩余预算打印尽可能多的i位数
            break;
        }
    }
    cout << res << '\n';
    return 0;
}