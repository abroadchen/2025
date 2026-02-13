//
// Created by Psy.C on 2026/2/13.
//
/**
需求量n、批量大小m、单价a、批量价格b

当需求量小于批量大小时
比较两种选择：
按单价购买：a*n
按批量购买（即使多余）：b
选择较小的方案

步骤1： ans = n/m*b;
计算能整除的批次数量：n/m
按批量购买这些整批：n/m * b
步骤2： if (const int r = n - n/m*m)
计算余数：r = n % m（剩余需要单独购买的数量）
如果有余数，需要处理剩余部分
步骤3： ans += min(r*a, b);
剩余r个的处理选择：
按单价购买：r*a
再买一批：b
选择更便宜的方案

当单价低于批量单价时（a < b/m）
直接按单价购买全部：a*n

 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m, ans;
double a, b;

int main() {
    fast;
    cin >> n >> m >> a >> b;
    if (n < m) ans = a*n > b ? b : a*n;
    else if (a >= b/m) {//单价相对较高
        ans = n/m*b;
        if (const int r = n - n/m*m) ans += min(r*a, b);
    } else ans = a*n;
    cout << ans << "\n";
    return 0;
}