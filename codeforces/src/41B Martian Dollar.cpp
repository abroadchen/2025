//
// Created by Psy.C on 2025/9/25.
//
/*
*ans初始化为初始资金b，存储最大收益
t初始化为第一个元素arr[1]，表示当前遇到的最低价格
 *
 *如果当前价格arr[i]小于等于已知最低价格t，则更新最低价格t
 *
*k = b / t：计算用所有资金能购买多少单位的商品
a = k * t：购买这些商品需要的资金
x = k * arr[i]：如果在当前价格卖出能获得的资金
b - a + x：剩余资金 + 卖出所得 = 总资金
更新最大收益ans为当前最大值
 *
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int n, b; cin >> n >> b;

    int arr[n + 5];
    for (int i = 1; i <= n; ++i) cin >> arr[i];


    int ans(b), t(arr[1]);
    for (int i = 2; i <= n; ++i) {
        if (arr[i] <= t) t = arr[i];
        else {
            int k = b / t;
            int a = k * t;
            int x = k * arr[i];
            ans = max(ans, b - a + x);
        }
    }
    cout << ans;

    return 0;
}