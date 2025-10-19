//
// Created by Psy.C on 2025/10/19.
//
/*
*abs(x - 1): 到上边界的距离
abs(y - m): 到右边界的距离
abs(x - n): 到下边界的距离
abs(y - 1): 到左边界的距离
取这四个距离的最小值，判断是否小于等于4
使用|=操作符，只要有一个点满足条件，ans就变为true并保持为true
 */
#include <ios>
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int n, m, k;
bool ans;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1, x, y; i <= k; ++i) {
        cin >> x >> y;
        ans |= min({abs(x - 1), abs(y - m),
        abs(x - n), abs(y - 1)}) <= 4;
    }
    cout << (ans ? "YES" : "NO");
    return 0;
}