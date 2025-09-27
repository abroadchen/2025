//
// Created by Psy.C on 2025/9/26.
//
/*
 *
*n：目标数值
a, b, c：三个限制参数
cnt：计数器，初始化为0
 *
 *对于每个i值，j会遍历从0到c的所有值
 *
 *
*i是偶数且0 ≤ i ≤ a
0 ≤ j ≤ c
0 ≤ n - (i/2 + 2*j) ≤ b
换句话说，就是统计方程n = i/2 + 2*j + k在约束条件下有多少组非负整数解，其中i为偶数
 *
 *
 *
 */
#include <ios>
#include <iostream>
using namespace std;


int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, a, b, c, cnt(0); cin >> n >> a >> b >> c;

    for (int i = 0; i <= a; i += 2)
        for (int j = 0; j <= c; ++j) {
            int t = (i*0.5)+2*j, cur = n - t;
            if (cur >= 0 && cur <= b) cnt++;
        }
    cout << cnt;
    return 0;
}