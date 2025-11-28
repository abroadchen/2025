//
// Created by Psy.C on 2025/11/28.
//
/*
*将一个正整数的各位数字反转
ans：存储反转后的结果，初始为0
循环处理x的每一位数字：
x % 10：获取x的最后一位数字
10 * ans + x % 10：将这一位添加到ans的末尾
x /= 10：去掉x的最后一位
直到x变为0为止
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int inv(int x) {
    int ans = 0;
    while (x > 0) {
        ans = 10 * ans + x % 10;
        x /= 10;
    }
    return ans;
}

int main() {
    fast;
    int x, y; cin >> x >> y;
    cout << x + inv(y) << '\n';
    return 0;
}