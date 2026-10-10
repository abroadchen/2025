//
// Created by Psy.C on 2026/10/10.
//
/**
用一个数组 b 来"存放"被保留的元素，j 指向 b 中下一个可写位置（即当前已累计的保留元素数 +1）
对每个元素 a[i]：
先把 a[i] 写入 b[j]（临时放置）
判断条件：
若 i < k（还没养成 k 个元素），直接 j++（保留）
否则需要比较这第 j 个位置与往前第 k-1 个位置的元素差：b[j] - b[j-k+1] >= m
若差值 ≥ m：保留（j++）
否则：剔除（ans++，即被排除的数量 +1

当前保留队列里，最近保留下来的第 j 个元素与它往前数第 k-1 个元素（即连续 k 个保留元素中的第一个）的差。
判定逻辑：当队伍里连续积累了 k 个保留元素时，要求这 k 个中最大与最小的差 ≥ m，否则就认为这个新加入的元素不该保留（被排除）。这实际上是在维护一种约束：任意连续 k 个保留的元素，其极差必须 ≥ m（因为数组本身升序，所以跨不同 k 窗口其实由相邻约束隐含）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+10;
int n, m, k, a[N], b[N], ans;
int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a+1, a+n+1);
    for (int i = 1, j = 1; i <= n; ++i) {
        b[j] = a[i];
        if (i < k || b[j]-b[j-k+1] >= m) j++;
        else ans++;
    }
    cout << ans << '\n';
    return 0;
}