//
// Created by Psy.C on 2025/12/2.
//
/*
*n: 元素个数
k: 需要选择的元素个数
a[N]: 原始数组
val[N]: 用于排序的数组副本
b: 预算值（使用long long类型）
 *
 *从最大的k个元素中扣除它们的值（计算购买这些元素后的剩余预算）
 *如果剩余预算非负，说明可以购买所有元素，输出n
 *
 *如果当前元素大于等于第k大的元素，或者即使加上第k大元素再减去当前元素仍然不够预算
 *记录当前位置并跳出循环
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
using namespace std;

int n, k, a[N], val[N];
ll b;

int main() {
    fast;
    cin >> n >> k >> b;
    for (int i = 1; i <= n; ++i) { cin >> a[i]; val[i] = a[i]; }
    sort(val + 1, val + n);
    ll sum = b;
    for (int i = n - 1; i >= n - k; --i) sum -= val[i];
    if (sum >= 0) cout << n;
    else {
        int ans = -1;
        for (int i = 1; i <= n; ++i) {
            if (a[i] >= val[n-k] || sum + val[n-k] - a[i] < 0) {
                ans = i; break;
            }
        }
        cout << ans;
    }
    return 0;
}