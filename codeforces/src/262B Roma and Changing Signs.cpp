//
// Created by Psy.C on 2025/12/20.
//
/*
*贪心策略的第一步：优先将负数变为正数 这样能最大程度增加总和
遍历数组，如果元素是负数且还有操作次数(k > 0)
将负数乘以-1变为正数
操作次数k减1
 *
 *最小的元素（可能是之前正数中最小的，或刚刚变为正数的）会排在最前面
*如果剩余操作次数是奇数
将数组中最小的元素（a[0]）乘以-1
这是因为奇数次符号变换最终相当于1次变换，要使和最大，应该变换绝对值最小的元素
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000000
using namespace std;


int main() {
    fast;
    ll n, k, sum = 0; cin >> n >> k;
    ll a[N];
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) if (a[i] < 0 && k > 0) {
        a[i] = a[i] * (-1);
        k--;
    }
    sort(a, a + n);
    if (k % 2 == 1) a[0] *= -1;
    for (int i = 0; i < n; ++i) sum += a[i];
    cout << sum;
    return 0;
}