//
// Created by Psy.C on 2026/3/22.
//
/**
检查对于给定的mid值是否满足条件：

ans = 0: 记录配对数量
l = 1, r = n: 左右指针分别指向数组首尾
在while循环中：
如果a[l] + a[r] <= mid，说明这两个数可以配对，左右指针都移动，ans++
否则只能单独处理右边的元素，右指针左移，ans++
返回ans > k，即实际需要的操作数是否大于k

l = a[n]: 最小可能值
r = a[n] + a[n-1]: 最大可能值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;

int n, a[N], k;
bool ok(ll mid) {
    int ans = 0, l = 1, r = n;
    while (l <= r) {
        if (a[l] + a[r] <= mid) {
            l++; r--; ans++;
        } else {
            r--; ans++;
        }
    }
    return ans > k;
}

int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll l = a[n], r = a[n] + a[n-1];
    while (l <= r) {
        if (ll mid = (l + r) / 2; ok(mid)) l = mid + 1;
        else r = mid - 1;
    }
    cout << l;
    return 0;
}