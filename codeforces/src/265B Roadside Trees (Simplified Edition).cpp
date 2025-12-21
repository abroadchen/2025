//
// Created by Psy.C on 2025/12/21.
//
/*
*h：当前楼层高度变量
h0 = 0：初始楼层高度为0
 *
 *累加从上一楼层h0到当前楼层h的距离 累加所有楼层间移动的距离
 *更新上一楼层为当前楼层
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int ans = (n<<1) - 1, h, h0 = 0;
    while (n--) {
        cin >> h;
        ans += abs(h - h0);
        h0 = h;
    }
    cout << ans << '\n';
    return 0;
}