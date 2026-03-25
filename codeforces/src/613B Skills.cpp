//
// Created by Psy.C on 2026/3/24.
//
/**
值和原始索引
sum[N]: 前缀和数组
ans: 存储最优解（总收益，{改变数量，最小值}）
n（数组长度）、a（最大值）、ma（改变的收益）、mi（最小值的收益）、k（操作预算）
读入数组元素，同时记录原始索引
按值从小到大排序，保持原始索引信息
计算前缀和数组

i: 改变为a的元素个数
dt = k - i*a + sum[n] - sum[n-i]: 剩余预算
k: 总预算
i*a: 改变i个元素的成本
sum[n] - sum[n-i]: 最大i个元素的和
p = min(p, n-i): 剩余元素数量
while (p > 1 && dt < p*d[p].x - sum[p]) p--: 找到可以统一提升到相同值的最大位置
dt -= p*d[p].x - sum[p]: 更新剩余预算
kt = min(a, i == n ? a : (d[p].x + dt/p)): 计算统一的最小值
ans = max(...): 更新最优解

输出最大收益
for (int i = 0; i < ans.second.first; ++i) d[n-i].x = a;: 将最大的i个元素改为a
for (int i = 1; i <= n; ++i) d[i].x = max(d[i].x, ans.second.second);: 将其他元素提升到最小值
按原始索引排序
输出最终数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pl pair<ll, ll>
using namespace std;
constexpr int N = 1e5+5;
struct node { ll x, id; } d[N];
ll n, a, ma, mi, k, sum[N];
pair<ll, pl> ans;
int main() {
    fast;
    cin >> n >> a >> ma >> mi >> k;
    for (ll i = 1; i <= n; ++i) {
        cin >> d[i].x; d[i].id = i;
    }
    sort(d + 1, d + n + 1, [](node x, node y) {
        return x.x < y.x;
    });
    sum[0] = 0;
    for (ll i = 1; i <= n; ++i) sum[i] = sum[i-1] + d[i].x;
    ll p = n;
    for (int i = 0; i <= n; ++i) {
        ll dt = k - i*a + sum[n] - sum[n-i];
        if (dt < 0) break;
        p = min(p, n-i);
        while (p > 1 && dt < p*d[p].x - sum[p]) p--;
        dt -= p*d[p].x - sum[p];
        ll kt = min(a, i == n ? a : (d[p].x + dt/p));
        ans = max(ans, {i*ma + kt*mi, {i, kt}});
    }
    cout << ans.first << '\n';
    for (int i = 0; i < ans.second.first; ++i) d[n-i].x = a;
    for (int i = 1; i <= n; ++i) d[i].x = max(d[i].x, ans.second.second);
    sort(d + 1, d + n + 1, [](node x, node y) {
        return x.id < y.id;
    });
    for (ll i = 1; i <= n; ++i) cout << d[i].x << ' ';
    cout << '\n';
    return 0;
}