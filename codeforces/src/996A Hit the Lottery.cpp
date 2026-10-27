//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
ans += n/面额：用当前最大面额尽量多取；
n = n%面额：取完后剩的余数进入下一面额。
按从大到小 100 → 20 → 10 → 5 → 1 依次遍历，累加得到最少张数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, ans;
int main() {
    fast;
    cin >> n;
    ans += n/100; n = n%100;
    ans += n/20; n = n%20;
    ans += n/10; n = n%10;
    ans += n/5; n = n%5;
    ans += n;
    cout << ans << '\n';
    return 0;
}