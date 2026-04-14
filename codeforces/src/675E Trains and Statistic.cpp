//
// Created by Psy.C on 2026/4/13.
//
/**
f[i]表示从位置i到终点的代价
v: 单调栈，存储索引

f[n-1] = 1: 从最后一个位置到终点的代价为1
ans = 1: 总代价初始化为1
v.push_back(n-1): 将最后位置加入单调栈

在单调栈v中从后往前查找第一个大于a[i]的位置
upper_bound(v.rbegin(), v.rend(), a[i])在逆序数组中查找第一个≤a[i]的位置
减1得到第一个>a[i]的位置

f[k]: 从k到终点的代价
(k-i): 从i跳到k的步数
(n-a[i]): 从位置a[i]到终点的额外代价
累加到总答案
弹出所有a值小于等于当前a[i]的索引
保持栈中a值单调递减
将当前索引i加入栈

时间复杂度：O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
int n, a[N];
ll f[N], ans;
vector<int> v;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i < n; ++i) cin >> a[i];
    f[n-1] = ans = 1; v.push_back(n-1);
    for (int i = n-2; i; --i) {
        int k = *(upper_bound(v.rbegin(), v.rend(), a[i])-1);
        f[i] = f[k] + (k-i) + (n-a[i]); ans += f[i];
        while (!v.empty() && a[i] >= a[v.back()])
            v.pop_back();
        v.push_back(i);
    }
    cout << ans << '\n';
    return 0;
}