//
// Created by Psy.C on 2026/1/12.
//
/**
 *
*ans：累计总距离
cur=1：当前位置，初始在位置1
g：目标位置
 *
*情况1：g - cur >= 0
目标位置g在当前位置cur之后（或相同）
顺时针移动距离为 g - cur
累加距离，更新当前位置
情况2：g - cur < 0
目标位置g在当前位置cur之前
需要跨越圆环边界
距离为 g - cur + n（等价于 (n - cur) + g）
累加距离，更新当前位置
 *
 * O(m)，其中m是目标点数量
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    unsigned long long ans = 0;
    for (int i = 0, g, cur=1; i < m; ++i) {
        cin >> g;
        if (g - cur >= 0) ans += g - cur, cur = g; else {
            ans += g - cur + n; cur = g;
        }
    }
    cout << ans;
    return 0;
}