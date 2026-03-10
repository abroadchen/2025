//
// Created by Psy.C on 2026/3/10.
//
/**
get(10, x)：10^x，即位数相同的最小数
x + 1：当前数的位数
n - get(10, x) + 1：从10^x到n的数字个数
这部分计算最高位数段的数字总位数
如果n=1234
x=3，x+1=4（4位数）
10^3=1000
从1000到1234有235个数
这235个4位数贡献的总位数：235×4

循环处理更低位数的数字
9 * get(10, x)：x+1位数的个数
例如：x=2时，9*10^2=900，表示有900个3位数(100-999)
(x + 1)：当前位数
累加所有低位数段的总位数

O(log₁₀n)，即n的位数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

///n^k（n的k次方）
ll get(int n, int k) {
    ll s = 1;
    for (int i = 1; i <= k; ++i) s *= n;
    return s;
}

ll n;
int main() {
    fast;
    cin >> n;
    int x = log10(n);//n的位数-1
    ll sum = (x + 1) * (n - get(10, x) + 1);
    while (x) {
        x--;
        sum += 9 * get(10, x) * (x + 1);
    }
    cout << sum << '\n';
    return 0;
}