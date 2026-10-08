//
// Created by Psy.C on 2026/10/8.
//
/**
先读入 n 和 x。
再读入 n 个数，全部累加到 ans（即 ans = 这 n 个数的和）。
判断 ans 是否等于 (x+1) - n。
相等输出 Yes，否则输出 No
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, x, y, ans;
int main() {
    fast;
    cin >> n >> x;
    for (int i = 0; i < n; ++i) {
        cin >> y; ans += y;
    }
    if (ans == (x+1)-n) cout << "Yes"; else cout << "No";
    return 0;
}