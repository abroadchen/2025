//
// Created by Psy.C on 2026/4/26.
//
/**
(i轮) × (每轮k瓶) = 总瓶数，然后取个位数作为余数存储在变量 x 中
余数 x 等于0（能被10整除）或者等于目标余数 r
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int k, r, i;
int main() {
    fast;
    cin >> k >> r;
    i = 1;
    for (; ; ++i) {
        int x = i*k%10;
        if (x == 0 || x == r) break;
    }
    cout << i << '\n';
    return 0;
}