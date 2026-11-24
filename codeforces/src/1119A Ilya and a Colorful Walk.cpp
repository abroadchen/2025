//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
从左往右扫：若 d[i] != d[0]，则以第一个元素为端点的区间长度可到达 i（下标距离就是 i-0），更新答案。一直扫到最右，i 最大时距离最大
从右往左扫：若 d[i] != d[n-1]，则以最后一个元素为端点时可到达 i，距离为 n-1-i，更新答案。
输出两个方向中的最大距离
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 3e5+5;
int n, d[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> d[i];
    int ans = 0;
    for (int i = 1; i < n; i++)
        if (d[i] != d[0]) ans = max(ans, i);
    for (int i = n-2; i >= 0; i--)
        if (d[i] != d[n-1]) ans = max(ans, n-1-i);
    cout << ans;
    return 0;
}