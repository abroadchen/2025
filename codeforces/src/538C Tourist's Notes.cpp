//
// Created by Psy.C on 2026/3/5.
//
/**
总长度n、关键点数量m、第一个关键点坐标(ld)和高度(lh)

x = d - ld - 1 - sgn(h - lh): 计算两个关键点之间可用的水平距离（减去必须的斜坡距离）
max(h, lh) + ((x+1)>>1): 在两个关键点之间可能达到的最大高度
max(h, lh)是两个关键点中较高的那个
((x+1)>>1)等价于(x+1)/2，是中间可以上升的最大高度
更新全局最大高度ans
更新上一个关键点信息

h + n - d: 从最后一个关键点到终点(n)能到达的最大高度
更新全局最大高度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

inline int sgn(const int x) {
    return x >= 0 ? x : -x;
}
int n, m, ld, lh, ans;
int main() {
    fast;
    cin >> n >> m >> ld >> lh;
    ans = ld + lh - 1;//起点到第一个关键点的最大可能高度
    int d = ld, h = lh;
    for (int i = 1; i < m; ++i) {
        cin >> d >> h;
        if (sgn(h - lh) > d - ld) {//高度差的绝对值不能超过水平距离
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        const int x = d - ld - 1 - sgn(h - lh);
        ans = max(ans, max(h, lh) + ((x+1)>>1));
        ld = d, lh = h;
    }
    ans = max(ans, h + n - d);
    cout << ans << '\n';
    return 0;
}