//
// Created by Psy.C on 2025/12/6.
//
/*
 *两个变量 a1 和 a2 交替更新
*时间复杂度：O(n) - 循环执行n次
空间复杂度：O(1) - 只使用常数额外空间
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int p = 1000000007;
int n, a1, a2;

int main() {
    fast;
    cin >> n;
    while (n--) {
        if (n & 1) a1 = (a1 + a2 + 1) % p;
        else a2 = (a1 + a2 + 1) % p;
    }
    cout << (a1 + a2) % p;
    return 0;
}