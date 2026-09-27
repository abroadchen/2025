//
// Created by Psy.C on 2026/9/27.
//
/**
r：大圆半径；d：环带厚度；n：小圆个数。
每个小圆：圆心 (x, y)，半径 R。
cnt：满足条件的小圆个数
x*x+y*y >= (r-d+R)*(r-d+R)：圆心距平方 ≥ (r-d+R)²，即 dist >= r-d+R —— 内边界（最外沿不进入挖空区，边界算合法）。
x*x+y*y <= (r-R)*(r-R)：圆心距平方 ≤ (r-R)²，即 dist <= r-R —— 外边界（最外沿不超出大圆，边界算合法）。
两者同时成立 → 小圆完全在环带内 → cnt++
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int r, d, n, x, y, R, cnt;
int main() {
    fast;
    cin >> r >> d >> n;
    while (n--) {
        cin >> x >> y >> R;
        if (x*x+y*y >= (r-d+R)*(r-d+R) && x*x+y*y <= (r-R)*(r-R))
            ++cnt;
    }
    cout << cnt;
    return 0;
}