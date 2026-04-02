//
// Created by Psy.C on 2026/4/1.
//
/**
位置1和2的值互换（ans[2], ans[1]）
位置3保持不变
中间部分4到n-2保持不变
位置n-1和n的值互换（ans[n], ans[n-1]）
时间复杂度：O(n)，空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;
int n, k, a, b, c, d, ans[N];
int main() {
    fast;
    cin >> n >> k;
    cin >> a >> b >> c >> d;
    if (n < 5 || k < n+1) cout << "-1\n";
    else {
        ans[1] = a, ans[2] = c, ans[n-1] = d, ans[n] = b;
        for (int i = 3, j = 1; i <= n-2; ++i) {
            while (j == a || j == b || j == c || j == d) j++;//跳过a, b, c, d这些特殊值
            ans[i] = j++;//依次填充不重复的普通值
        }
        for (int i = 1; i <= n; ++i) cout << ans[i] << " \n"[i==n];
        cout << ans[2] << ' ' << ans[1] << ' ' << ans[3] << ' ';
        for (int i = 4; i <= n-2; ++i) cout << ans[i] << ' ';
        cout << ans[n] << ' ' << ans[n-1] << '\n';
    }
    return 0;
}