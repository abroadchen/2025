//
// Created by Psy.C on 2025/11/27.
//
/*
*x: 上限值
d: 底数
如果d≤1，返回-1（无效情况）
*ans: 累加结果，初始化为0
div: 除数，初始化为1
循环条件：当除数不超过x时继续
每次将x/div加到结果中
除数乘以d（即d的幂次递增：1, d, d², d³, ...）
 *
 *⌊x/1⌋ + ⌊x/d⌋ + ⌊x/d²⌋ + ⌊x/d³⌋ + ...
 *
*循环条件：l+1 < r（确保区间内至少有一个整数）
计算中点mid
计算sum(mid, k)的值
如果结果小于n，说明mid太小，调整左边界
如果结果大于等于n，说明mid可能太大或刚好，调整右边界
 *
 *时间复杂度为O(log²n)
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;

ll sum(const ll x, const ll d) {
    if (d <= 1) return -1;
    ll ans(0), div(1);
    while (div <= x) {
        ans += x / div;
        div *= d;
    }
    return ans;
}

int main() {
    fast;
    ll n, k; cin >> n >> k;
    ll l(1), r(n);
    while (l + 1 < r) {
        const ll mid = (l + r) / 2, t = sum(mid, k);//x在k进制表示下，各个位数的数字之和
        if (t < n) l = mid;
        else if (t >= n) r = mid;
    }
    cout << r << '\n';
    return 0;
}