//
// Created by Psy.C on 2026/9/22.
//
/**
设第一份为 x，则第二份为 k*x，第三份为 n - x - k*x = n - (k+1)x。因为要"分出至少三份、且第三份 ≥ 第一份（题意要求三者都为正且有序）"，最关键的约束是总价值至少要用掉一半给前两份……更直接地，经典题意是：前两段（x 和 kx）加起来不能超过总的一半，即 (k+1)x ≤ n/2，故 x ≤ n/2/(k+1)，取最大整数解，即 ans = n/2/(k+1)
第一份：ans
第二份：ans*k（正好是第一份的 k 倍）
第三份：n - ans - ans*k（把剩下的全部给第三份）
由于 ans 是整数、且 (k+1)*ans ≤ n/2 ≤ n，所以三份都为非负整数，且恰好相加等于 n
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, k, ans;
int main() {
    fast;
    cin >> n >> k;
    ans = n/2/(k+1);
    cout << ans << ' ' << ans*k << ' ' << n-ans-ans*k;
    return 0;
}