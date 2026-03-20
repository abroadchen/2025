//
// Created by Psy.C on 2026/3/20.
//
///算法的时间复杂度为 O(n)，空间复杂度为 O(n)
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;
int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int t = 0; ll ans = 0;
    for (int i = 1; i <= n; ++i)
        if (t != a[i]) {//当前元素与目标值不同
            int x = a[i] - t;
            ans += abs(a[i] - t);//累加操作数（距离）
            t += x;//更新目标值为a[i]
        }
    cout << ans << '\n';
    return 0;
}