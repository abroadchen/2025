//
// Created by Psy.C on 2026/10/7.
//
/**
n：数组长度，a[N]：数组元素（数值），st：当前擂主连续获胜的场数，k：要达到的连胜目标
初始化：第一元素 a[0] 是当前"擂主"，连胜计数 st=0
逐个扫描第 2 个元素及以后：

若已达成 k 连胜（st>=k）‍：直接输出当前擂主 ans 并结束。
若当前擂主 ans 比 a[i] 大：擂主继续获胜，st++。
否则（a[i] 更大）‍：a[i] 夺权成为新擂主 ans=a[i]，且它已经赢了一场，重置 st=1。
循环结束后（扫完整个数组仍没达到 k 连胜），输出最终擂主 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 600;
int n, a[N], st;
ll k;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int ans = a[0]; st = 0;
    for (int i = 1; i < n; ++i) {
        if (st >= k) { cout << ans << '\n'; return 0; }
        if (ans > a[i]) st++;
        else {
            st = 1;
            ans = a[i];
        }
    }
    cout << ans << '\n';
    return 0;
}