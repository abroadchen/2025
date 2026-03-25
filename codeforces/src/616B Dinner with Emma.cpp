//
// Created by Psy.C on 2026/3/25.
//
///O(n×m)，需要遍历矩阵中的每一个元素
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int inf = 1e9;
int n, m;
int main() {
    fast;
    cin >> n >> m;
    int ans = -inf;//所有行最小值中的最大值
    for (int i = 1; i <= n; ++i) {
        int mn = inf;//当前行的最小值
        for (int j = 1, x; j <= m; ++j) {
            cin >> x;
            mn = min(mn, x);//更新当前行的最小值
        }
        ans = max(ans, mn);
    }
    cout << ans;
    return 0;
}