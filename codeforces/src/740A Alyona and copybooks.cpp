//
// Created by Psy.C on 2026/4/28.
//
/**
n: 输入的数字
a, b, c: 三种操作的代价
mn: 最小代价，初始化为无穷大
如果n已经是4的倍数，则不需要任何操作，输出0
否则，枚举所有可能的操作组合：
i: 增加1的次数，代价为i*a
j: 增加2的次数，代价为j*b
k: 增加3的次数，代价为k*c
检查 (n+i+j*2+k*3)%4 == 0 是否成立（即操作后变成4的倍数）
如果成立，更新最小代价 mn
注意：由于模4的性质，只需要考虑0~4的范围就足够了

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int inf = 0x3f3f3f3f;
ll n, a, b, c, mn = inf;
int main() {
    fast;
    cin >> n >> a >> b >> c;
    if (n%4 == 0) cout << '0' << '\n';
    else {
        for (int i = 0; i <= 4; ++i)
            for (int j = 0; j <= 4; ++j)
                for (int k = 0; k <= 4; ++k)
                    if ((n+i+j*2+k*3)%4 == 0)
                        mn = min(mn, i*a+j*b+k*c);
        cout << mn << '\n';
    }
    return 0;
}