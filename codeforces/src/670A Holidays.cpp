//
// Created by Psy.C on 2026/4/12.
//
/**
第一部分：计算n天内的休息日数量
每完整的一周有2天休息日
如果余数≤5，说明剩余天数中没有额外休息日
如果余数>5（即为6），说明还有1天额外休息日
第二部分：计算n-2天内的工作日数量，然后加2
n-2天的工作日数量 + 2天初始工作日
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    if (n == 1) {
        cout << "0 1\n";
        return 0;
    }
    if (n % 7 <= 5) cout << n/7*2 << ' ';
    else cout << n/7*2+1 << ' ';
    n -= 2;
    if (n % 7 <= 5) cout << n/7*2+2 << '\n';
    else cout << n/7*2+1+2 << '\n';
    return 0;
}