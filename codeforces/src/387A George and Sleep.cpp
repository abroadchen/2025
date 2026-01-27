//
// Created by Psy.C on 2026/1/27.
//
/*
* cur/60: 计算小时数
cur%60: 计算分钟数
时间复杂度
O(1)，只进行常数次算术运算
空间复杂度
O(1)，只使用常数额外空间
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    char c;
    ll hh, mm, h, m; cin >> hh >> c >> mm;//读入第一个时间：hh:mm (小时:分钟)
    cin >> h >> c >> m;//读入第二个时间：h:m (小时:分钟)
    //时间转换为总分钟数
    const ll w = hh * 60 + mm, s = h * 60 + m; ll cur = w - s;//时间差（分钟）
    if (cur < 0) cur = 24 * 60 + cur;//跨天了，加上一天的分钟数(24*60)
    cout << setfill('0') << setw(2) << cur/60 << ':' << setw(2) << cur%60 << '\n';
    return 0;
}