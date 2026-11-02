//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
(x1, y1)：第一个出现黑格的位置——由于按行、列遍历，它就是黑格矩形的左上角。
(x2, y2)：最后一次更新的黑格位置——遍历到后面更大的行列时会被覆盖，最终是黑格矩形的右下角。
k 只是标记是否已记录第一个黑格的开关
矩形中心 = 左上角与右下角的坐标平均值，取整后输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); i++)
using namespace std;

int n, m;
char c;
int main() {
    fast;
    cin >> n >> m;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0, k = 1;
    rep(i,n) rep(j,m) {
        cin >> c;
        if (c == 'B') {
            if (k == 1) { x1 = i, y1 = j; k = 0; }
            x2 = i, y2 = j;
        }
    }
    cout << (x1+x2)/2 << ' ' << (y1+y2)/2 << '\n';
    return 0;
}