//
// Created by Psy.C on 2026/4/13.
//
/**
n: 数组长度
k: 可操作次数

找最小值的上界
l = a[0]: 最小值不可能小于原数组最小值
r = sum/n: 最小值不可能大于平均值
对于每个候选值mid，计算将其余小于mid的元素提升到mid所需的步数
如果步数超过k，则mid太大，调整右边界
否则，mid可能，调整左边界
最终a1 = r是最小值的最大可能值

找最大值的下界
l = sum/n（如果不能整除则+1）：最大值不可能小于平均值
r = a[n-1]: 最大值不可能小于原数组最大值
从大到小遍历数组，计算将大于mid的元素降低到mid所需的步数
如果步数超过k，则mid太小，调整左边界
否则，mid可能，调整右边界
最终a2 = l是最大值的最小可能值

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e5+5;
int n, k, a[N];
int main() {
    fast;
    cin >> n >> k;
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; sum += a[i];
    }
    sort(a, a + n);
    int l = a[0], r = sum/n, mid;
    while (l <= r) {
        mid = (l + r)>>1;
        ll t = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] < mid) t += mid - a[i];
            else break;
        }
        if (t > k) r = mid - 1; else l = mid + 1;
    }
    int a1 = r; l = sum/n;
    if (sum%n != 0) ++l;
    r = a[n-1];
    while (l <= r) {
        mid = (l + r)>>1;
        ll t = 0;
        for (int i = n-1; i >= 0; --i) {
            if (a[i] > mid) t += a[i] - mid;
            else break;
        }
        if (t > k) l = mid + 1; else r = mid - 1;
    }
    int a2 = l;
    cout << a2 - a1 << '\n';
    return 0;
}