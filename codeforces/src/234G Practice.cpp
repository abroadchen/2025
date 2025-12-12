//
// Created by Psy.C on 2025/12/12.
//
/*
 *
*初始化ans为1
循环条件：1左移ans位的结果小于n
每次循环ans自增1
这个循环实际上是在找最小的ans，使得2^ans >= n
换句话说，ans是能够表示n个不同数字所需的最少二进制位数
 *
*统计在0到n-1中，第i位为1的数字个数：
1<<i：将1左移i位，得到只有第i位为1的数
1<<i & j：按位与操作，检查j的第i位是否为1
如果为1，计数器cnt加1
 *
*输出所有第i位为1的数字（从1开始编号）：
遍历0到n-1的所有数字j
检查j的第i位是否为1
如果是，则输出j+1（因为题目要求从1开始编号）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int n, ans; cin>>n;
    for (ans = 1; 1<<ans < n; ++ans) {}
    cout << ans << '\n';
    for (int i = 0, cnt; i < ans; ++i) {//i表示当前处理的是第几位（从最低位开始）
        cnt = 0;
        for (int j = 0; j < n; ++j) if (1<<i & j) cnt++;
        cout << cnt;
        for (int j = 0; j < n; ++j) if (1<<i & j)
            cout << ' ' << j + 1;
        cout << '\n';
    }
    return 0;
}