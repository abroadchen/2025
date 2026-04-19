//
// Created by Psy.C on 2026/4/18.
//
/**
n: 数组长度
k: 操作次数
计算所有相邻元素的乘积和
(i+1)%n 确保最后一个元素与第一个元素相邻（环形数组）
输入要删除的索引（1-based转换为0-based）
从总和中减去该位置的值
如果右边邻居未被删除，从sum中减去其值
(-1+n)%n 处理负数取模，确保得到正确的左边邻居索引
a[x]与所有未被删除的相邻元素的乘积之和
将之前减去的相邻元素值加回来
标记位置x已被删除
O(n + k): 一次初始化 + k次操作
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
ll n, k;
int main() {
    fast;
    cin >> n >> k;
    ll a[n+10], sum = 0, i, ans = 0;
    for (i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    for (i = 0; i < n; ++i) ans += a[i]*a[(i+1)%n];
    vector<ll> vis(n+10, 0);
    for (i = 1; i <= k; ++i) {
        ll x; cin >> x; x--; sum -= a[x];
        if (!vis[(x+1)%n]) sum -= a[(x+1)%n];
        if (!vis[(x-1+n)%n]) sum -= a[(x-1+n)%n];
        ans += a[x]*sum;
        if (!vis[(x+1)%n]) sum += a[(x+1)%n];
        if (!vis[(x-1+n)%n]) sum += a[(x-1+n)%n];
        vis[x] = 1;
    }
    cout << ans;
    return 0;
}