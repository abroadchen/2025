//
// Created by Psy.C on 2026/3/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 55, inf = 0x3f3f3f3f;
int n, a[N], b[N], x[N];
int main() {
    fast;
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        cin >> a[i];
        a[i] += a[i-1];//从第1个元素到第i个元素的累积和
    }
    for (int i = 1; i <= n-1; ++i) cin >> b[i];
    for (int i = n-1; i >= 1; --i) b[i] += b[i+1];//从第i个元素到第n-1个元素的累积和
    for (int i = 1; i <= n; ++i) cin >> x[i];//位置i的基础成本
    int ans = inf;
    for (int i = 1; i <= n; ++i)//遍历所有可能的索引对(i,j)
        for (int j = 1, sum; j <= n; ++j) {
            if (i == j) continue;//确保选择两个不同的位置
            sum = a[i] + x[i] + b[i];//位置i的成本
            sum += a[j] + x[j] + b[j];//加上位置j的成本
            ans = min(ans, sum);
        }
    cout << ans << '\n';
    return 0;
}