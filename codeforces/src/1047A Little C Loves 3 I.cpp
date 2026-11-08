//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
情况 A：(n-2) % 3 == 0

输出三个数：1、2、n-3。
验证：
求和：1 + 2 + (n-3) = n ✅
两两不同：只要 n-3 ≠ 1 且 n-3 ≠ 2，即 n ≠ 4 且 n ≠ 5，就互异。对较大 n 成立。
为什么要这个分支？因为这样可以避免拆成 1,1, 或 1,2,** 时有重复。
情况 B：否则

输出 1、1、n-2。
求和：1 + 1 + (n-2) = n ✅
注意：前两个都是 1，相等。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    if ((n-2)%3 == 0) cout << "1 2 " << n-3 << '\n';
    else cout << "1 1 " << n-2 << '\n';
    return 0;
}