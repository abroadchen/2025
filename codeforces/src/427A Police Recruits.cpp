//
// Created by Psy.C on 2026/2/4.
//
/**
 *ans：需要用来抵消负数的正数数量
* a：正数总和
b：需要被抵消的负数总和（取绝对值）
d：当前读入的数字
 *
 *将所有正数累加到a
 *将负数的绝对值加到b
 *
*当负数绝对值总和超过正数总和时
*当前正数不足以抵消负数，需要消耗额外的正数
ans++：消耗一个正数（增加答案）
b--：减少需要抵消的负数数量
 *
*时间复杂度：O(n)，单次遍历
空间复杂度：O(1)，常数空间
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int ans = 0;
    for (int i = 0, a = 0, b = 0, d; i < n; ++i) {
        cin >> d;
        if (d > 0) a += d;
        if (d < 0) {
            b -= d;
            if (b > a) { ans++; b--; }
        }
    }
    cout << ans << '\n';
    return 0;
}