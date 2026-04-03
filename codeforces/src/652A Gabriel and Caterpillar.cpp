//
// Created by Psy.C on 2026/4/2.
//
/**
h1: 初始高度
h2: 目标高度
a: 上升速度
b: 下降速度

如果上升速度≤下降速度
检查第一天是否能达到目标高度
如果不能达到，输出-1（不可能）
如果第一天（8小时上升）就能达到目标
输出0（不需要额外天数）
h: 还需要爬升的高度 = h2 - h1 - 8*a
d: 每天净爬升高度 = 12 * (a - b)
白天12小时上升：12*a
夜晚12小时下降：12*b
净效果：12*(a-b)
ans = h/d: 需要的天数（向下取整）
if (h%d) ans++: 如果有余数，天数加1（向上取整）
时间复杂度：O(1)，空间复杂度：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int h1, h2, a, b;
int main() {
    fast;
    cin >> h1 >> h2 >> a >> b;
    if (a <= b) {
        if (h1 + 8*a < h2) {
            cout << -1 << '\n';
            return 0;
        }
    }
    if (h1 + 8*a >= h2) {
        cout << 0 << '\n';
        return 0;
    }
    int h = h2 - h1 - 8*a, d = 12 * (a - b), ans = h/d;
    if (h%d) ans++;
    cout << ans << '\n';
    return 0;
}