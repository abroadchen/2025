//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
每读一个 x，计算 (x-i+n)/n。
用 < 严格比较，只更新"严格更小"的情况，因此若并列取第一个（较小的 i）
等价地也可以写成 ceil((x-i)/n)，即 (x-i) 除以 n 后向上取整
如果 x 表示该位置的"目标轮数边界"，(x-i+n)/n 就是"从起点 i 出发，绕 n 一圈一圈走，要花 ceil((x-i)/n) 圈才能覆盖到 x"，最小值对应最优起点
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int inf = 0x3f3f3f3f;

int n, ans;
int main() {
    fast;
    cin >> n;
    int mn = inf;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        if (mn > (x-i+n)/n) {
            mn = (x-i+n)/n;
            ans = i;
        }
    }
    cout << ans << '\n';
    return 0;
}