//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
对 a[1] 到 a[n] 进行升序排序（默认从小到大）。
参数是左闭右开区间：a+1 指向第一个元素，a+n+1 是最后一个元素的后一个位置
n>>1：n 右移一位，即 n/2（整除）。
n&1：n 与 1 按位与，即 n%2（n 是否为奇数，奇数得 1，偶数得 0）
a[(n>>1)+(n&1)] 就是 a[(n+1)/2]，即排序后的下中位数（奇数时是正中间，偶数时是偏小的那个）。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e3+5;

int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a+1, a+n+1);
    cout << a[(n>>1)+(n&1)] << '\n';
    return 0;
}