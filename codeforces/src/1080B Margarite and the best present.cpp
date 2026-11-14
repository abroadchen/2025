//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
i/2	i 整除 2（向下取整）
i%2?i:0	若 i 为奇数则取 i，偶数取 0
多组测试。
对区间 [l, r] 求某种"特征值累加和"，用 前缀和差分：前缀(r) − 前缀(l−1)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll get(int i) { return i/2-(i%2?i:0); }

int T, l, r;
int main() {
    fast;
    cin >> T;
    while (T--) {
        cin >> l >> r;
        cout << get(r)-get(l-1) << '\n';
    }
    return 0;
}