//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
c[0..n-1]：某种"要求值/能力值/门槛"数组（长度 n）。
a[0..m-1]：某种"尝试项/任务"数组（长度 m）。
ans：最终要输出的匹配数量，初始 0
i：指向当前要尝试匹配的 a 元素（从 0 到 m-1）。
j：指向当前考虑的门槛 c[j]
只要当前 a[i] 小于 c[j]（即 a[i] 够不到这个门槛），就把 j 往右移，跳过这些门槛。
含义：c 中那些比当前 a[i] 更大的"关卡/门槛"一律放弃不用，直到遇到一个 c[j] <= a[i]（当前 a 够得着的门槛）。
j < n 保证不越界
如果跳过了 n 个门槛后 j 已经越界（说明所有门槛都比当前 a[i] 大），那这个 a[i] 及之后都无法匹配 → break，提前结束
到这里说明 a[i] >= c[j]（跳过后够得着门槛），匹配成功。
更新 ans = i+1：记录当前成功匹配的是 a 的第几个（成功消耗了多少个 a 元素）。
for 的 i++, j++：匹配成功后两者同时前进——a 看下一个，c 的门槛也用掉一个
输出 ans：最多能成功匹配的 a 的前缀长度
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 0; i < n; i++)
using namespace std;

constexpr int N = 1e3+5;

int n, m, c[N], a[N], ans;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> c[i];
    rep(i,m) cin >> a[i];
    for (int i = 0, j = 0; i < m && j < n; i++, j++) {
        while (j < n && a[i] < c[j]) j++;
        if (j >= n) break;
        ans = i + 1;
    }
    cout << ans << '\n';
    return 0;
}