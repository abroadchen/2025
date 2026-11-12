//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
L/V	在 1..L 中所有 V 的倍数的个数，即总可用数
r/V	落在 [1, r] 中 V 的倍数个数，即要扣掉的上半段部分
(l-1)/V	落在 [1, l-1] 中 V 的倍数个数，即区间起点前该保留的部分
因为区间 [l, r] 里被毁掉的数是：r 以内所有优先级数 减去 l-1 以内所有优先级数（即 r/V - (l-1)/V）。

所以最终答案 = 总可用数 − 区间内损坏数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll T, L, V, l, r;
int main() {
    fast;
    cin >> T;
    while (T--) {
        cin >> L >> V >> l >> r;
        cout << L/V-r/V+(l-1)/V << '\n';
    }
    return 0;
}