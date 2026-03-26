//
// Created by Psy.C on 2026/3/26.
//
/**
ans：累计段数总和
外层循环遍历范围[l, r]内的每个数字i
内层while循环：
j%10：获取j的最后一位数字
c[j%10]：查表得到该数字所需段数
j/=10：去掉j的最后一位
循环直到j变为0
时间复杂度：O((r-l) × log₁₀(max(r,l))) 空间复杂度：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int c[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int main() {
    fast;
    int l, r; cin >> l >> r;
    ll ans = 0;
    for (int i = l; i <= r; ++i) {
        int j = i;
        while (j)
            ans += c[j%10], j/=10;
    }
    cout << ans;
    return 0;
}