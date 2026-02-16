//
// Created by Psy.C on 2026/2/16.
//
/**
k = n/m: 平均分配时每组的基本元素数
t = k + 1: 较大组的元素数（可能）
r = n%m: 余数，表示有多少个组需要多分配1个元素
l = m - r: 有l个组包含k个元素
r * get(t): r个组，每组t个元素的内部组合数
l * get(k): l个组，每组k个元素的内部组合数
mn = r * get(t) + l * get(k): 总的最小组合数
x = n - (m - 1): 最大组的元素数（其他组都是1个元素）
mx = get(x): 最大组的内部组合数

mn: 在m组中平均分配n个元素时的最小配对数
mx: 在m组中极端分配n个元素时的最大配对数
多数组有⌊n/m⌋个元素，少数组有⌈n/m⌉个元素
1组有n-m+1个元素，其余组各有1个元素 极端分配
O(1): 常数时间复杂度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
///C(x,2) = x*(x-1)/2，即x个元素中选2个的组合数
inline ll get(const ll x) { return (x*(x-1)) >> 1; }
ll n, m;///总元素数量 分组数量
int main() {
    fast;
    cin >> n >> m;
    const ll k = n/m, t = k + 1, r = n%m, l = m - r,
    mn = r * get(t) + l * get(k), x = n - (m - 1),
    mx = get(x);
    cout << mn << ' ' << mx << '\n';
    return 0;
}