//
// Created by Psy.C on 2026/3/23.
//
/**
计算有多少个月份的天数大于等于x：

遍历12个月
如果m[i] >= x，计数器加1
计算在闰年中，星期x出现的次数：
366/7 = 52（整数除法），表示每周都有52个完整的周期
闰年有366天，52周余2天（366 = 52×7 + 2）
对于星期五(x=5)和星期六(x=6)，会额外出现1次（因为余数的2天会增加这两天的出现次数）
所以星期五和星期六会出现53次，其他星期出现52次
时间复杂度：
O(1)，常数时间复杂度。
空间复杂度：
O(1)，只使用了固定大小的数组。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
int m[] = {
    0,31,29,31,30,31,30,31,31,30,31,30,31
}, x, ans;
char t[5], op[10];
int main() {
    fast;
    cin >> x >> t >> op;
    if (op[0] == 'm') {
        for (int i = 1; i <= 12; ++i)
            if (m[i] >= x) ans++;
        cout << ans << '\n';
    } else {
        ans = 366/7;
        if (x == 5 || x == 6) ans++;
        cout << ans << '\n';
    }
    return 0;
}