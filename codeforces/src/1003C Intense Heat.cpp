//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
p[0] = 0（全局变量默认），所以 p[i] = a[1]+…+a[i]。
任意子段 [i..j] 的和 = p[j] - p[i-1]
外层 i 是子段起点，范围 1..n-k+1（保证后面还有至少 k 个位置）。
内层 j 是子段终点，从 i+k-1（即长度刚好为 k）到 n。
对每个 (i,j)：
和 = p[j]-p[i-1]；
长度 = j-i+1；
平均值 = (和)/(长度)，用 *1. 转 double 做浮点除法；
与 ans 取 max。
循环结束后，ans 就是所有长度 ≥ k 子段的平均值的最大值
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= (n); i++)
using namespace std;
constexpr int N = 5e5+5;

int n, k;
double a[N], p[N], ans;
int main() {
    fast;
    cin >> n >> k;
    rep(i,n) { cin >> a[i]; p[i] = p[i-1] + a[i]; }
    rep(i,n-k+1) for (int j = i+k-1; j <= n; j++)
        ans = max(ans, ((p[j]-p[i-1])*1./(j-i+1)));
    cout << fixed << setprecision(15) << ans << '\n';
    return 0;
}