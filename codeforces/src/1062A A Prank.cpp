//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
循环共执行 n+1 次（i 从 0 到 n）。
前 n 次读入真实数据；最后一次 i==n 用哨兵值 1001 收尾（保证最后一段能被结算）
若 y == x+1（比上一个正好大 1），说明还在同一个连续递增段内，len++。
否则段结束：len 个"连续 +1"的数对，能贡献的最大答案是 len-1（等差数列差 1 的项数 - 1），更新 ans 后重置 len=0

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, x, y, ans, len;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i <= n; i++) {
        if (i == n) y = 1001; else cin >> y;
        if (y == x+1) len++;
        else {
            if (len-1 > ans) ans = len-1;
            len = 0;
        }
        x = y;
    }
    if (len-1 > ans) ans = len-1;//处理最后一段
    cout << ans;
    return 0;
}