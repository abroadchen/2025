//
// Created by Psy.C on 2026/2/7.
//
/**
sum: 需要表示/分解的目标值
limit: 解集中允许的最大数字
ans[N]: 数组标记哪些数字被选中（1=选中，0=未选中）
tot: 选中的数字计数器

对于偶数i：

通过不断除以2计算i的二进制表示中的尾随零数量
num = i可以被2整除的次数（2的幂次因子）
t = 2^num（2的幂次部分）
如果sum >= t，从sum中减去t，标记i为选中，增加计数器

对于奇数i：

简单地从sum中减去1
标记i为选中
增加计数器
当sum达到0时停止（目标达成）。
 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;


int main() {
    fast;
    int sum, limit; cin >> sum >> limit;
    int ans[N]{}, tot = 0;
    for (int i = limit, t; i >= 1; --i) {
        if (!(i&1)) {
            int num = 0;
            for (int j = i; !(j&1); j >>= 1) num++;
            t = pow(2., num);
            if (sum - t >= 0) {
                sum -= t;
                ans[i] = 1;
                tot++;
            }
        } else {
            sum--;
            ans[i] = 1;
            tot++;
        }
        if (!sum) break;
    }
    if (sum) cout << "-1\n"; else {
        cout << tot << '\n';
        for (int i = 1; i <= limit; ++i)
            if (ans[i]) cout << i << ' ';
        cout << '\n';
    }
    return 0;
}