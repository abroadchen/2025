//
// Created by Psy.C on 2026/2/8.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll a[20];
void init() {
    a[0] = 1;
    for (int i = 1; i < 16; ++i) a[i] = a[i-1]*10+1;//1, 11, 111, 1111, ...
}
ll sgn(const ll t) { return t < 0 ? -t : t; }

/**
 *a[d] 本身包含 d+1 个数字 1
 *num 中最多包含 p1 个 a[d]
 *选择 p1 个 a[d]：剩余 num - p1*a[d]
 * @param num 当前处理的数字
 * @param d   当前的位数索引
 * @return
 */
ll dfs(const ll num, const int d) {//最小操作数
    if (d == 0) return num;
    // 当前数字除以特殊数的商（向下取整）
    const ll p1 = num/a[d], p2 = p1 + 1,
    //余数部分的递归成本
    r1 = dfs(sgn(num - p1*a[d]), d - 1),//选择p1时的递归结果
    r2 = dfs(sgn(num - p2*a[d]), d - 1);
    ///选择p1时的成本（p1次操作，每次d+1位）
    return min(p1*(d+1) + r1, p2*(d+1) + r2);
}

int main() {
    fast;
    ll n; cin >> n; init();
    cout << dfs(n, 15) << '\n';
    return 0;
}