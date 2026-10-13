//
// Created by Psy.C on 2026/10/13.
//
/**
把整数不断 %10 取最后一位、/10 丢弃最后一位，逐位检查是否出现数字 7，出现即返回 true。例如 17→取到 7 → true；8→各位都非 7 → false
输入 n h m：n 是每次倒推的分钟数，h:m 是初始时刻。
循环条件：当前的小时和分钟都不含 7 时继续倒推。
每次：分钟 m 减 n；若分钟变负则向小时借位（--h，m+=60）；若小时变负则回到前一天 23 点（h=23，即按 24 小时制回绕）。每倒推一次 ans++。
一旦小时或分钟里出现数字 7，循环立即停止
输出需要往前倒推多少次，才能让时刻（时或分）里出现数字 7。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

bool check(int x) {
    while (x) {
        if (x%10 == 7) return true;
        x /= 10;
    }
    return false;
}

int n, h, m, ans;
int main() {
    fast;
    cin >> n >> h >> m;
    while (!check(h) && !check(m)) {
        m -= n;
        if (m < 0) --h, m += 60;
        if (h < 0) h = 23;
        ++ans;
    }
    cout << ans << '\n';
    return 0;
}