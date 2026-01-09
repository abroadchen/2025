//
// Created by Psy.C on 2026/1/9.
//
/**
* 使用 num % 10 提取每一位数字
使用 max(t, num % 10) 记录最大数字
通过 num /= 10 移动到下一位
 *
*从当前数字中减去最大数字
用结果递归调用
加 1 来计数这次操作
 *计算需要多少次操作才能通过重复减去当前数字中的最大数字将一个数字减少到 0
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll dfs(const ll n) {
    if (n == 0) return 0;
    ll t = 0, num = n;
    while (num) {
        t = max(t, num % 10);
        num /= 10;
    }
    return dfs(n - t) + 1;
}

int main() {
    fast;
    ll n; cin >> n;
    cout << dfs(n) << '\n';
    return 0;
}