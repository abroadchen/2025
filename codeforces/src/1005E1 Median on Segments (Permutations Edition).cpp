//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
N：数组元素上限；M：计数数组大小（4e5+5，用于偏移）。
a[N]：转换后的 ±1 数组。
id：m 在数组中的下标。
pre[N]：前缀和。
cnt[M]：频次计数数组，用于统计前缀和值出现的次数（做了偏移）。
ans：最终答案
读入 a[i]。

若 a[i] == m，记录 m 出现的位置为 id。

转换：a[i] = (a[i] <= m) ? -1 : 1，即：

a[i] < m → -1；
a[i] > m → +1；
a[i] == m → -1（这里等于 m 也算 -1，注意！也不是全部，后面解释）。
等一下，仔细看：a[i] <= m ? -1 : 1，所以等于 m 时也被赋成 -1。这是这个特定解法的一个约定（与一般"=保留"的常见做法不同），对应"上中位数/含 m"的计数口径，稍后第 5 节说明。

pre[i] = pre[i-1] + a[i]：前缀和（转换后的 ±1 序列）。

关键：if (id) cnt[pre[i]+N-5]++。意思是只有在已经遇到（或越过）id 之后（当 id 非零时），才把当前 pre[i]（加偏移 N-5 防止负数下标）计入计数数组 cnt。

也就是说：只统计 m 位置 id 及其之后的所有前缀和值（下标 i ≥ id 的 pre[i]）的出现次数
遍历 i 从 0 到 id-1（即所有位于 m 之前的边界位置，包括空前缀 i=0），对每个 pre[i]：

加上 cnt[pre[i]+N-5]：统计后面（id 及之后）前缀和等于 pre[i] 的数量；
加上 cnt[pre[i]-1+N-5]：统计后面前缀和等于 pre[i]-1 的数量。
这两项分别对应两种"中位数等于 m"的定义口径（下中位数/上中位数），合在一起统计所有满足条件的子数组

记转换后数组 b[i] ∈ {-1, +1}（m 处也按第2节为 -1），前缀和 pre[i]。

对一个子数组 [l+1, r]，其和 = pre[r] - pre[l]。

关键事实：若子数组 [l+1, r] 的中位数为 m，则在这个子数组内部：

m 两侧的元素数量需满足某种平衡条件。具体地，若用 cnt_gt（大于 m 的数量，即 +1 个数）、cnt_lt（小于等于 m 的数量，即 -1 个数），则中位数为 m 的充要条件可写成：
对下中位数（(len+1)/2 位置）：cnt_gt - cnt_lt 的差 ∈ {0, 1}，即子数组和 ∈ {0, 1}；
对上中位数：子数组和 ∈ {0, -1}。
这正好对应两轮统计：

第一项 cnt[pre[i]+N-5]：子数组和 = pre[r]-pre[i] = 0，即 pre[r] = pre[i]。
第二项 cnt[pre[i]-1+N-5]：子数组和 = pre[r]-pre[i] = -1，即 pre[r] = pre[i]-1。
所以这个解法把"median=m"转化成了子数组和为 0 或 -1 两种情形，分别用 cnt 统计后半段出现的目标前缀和次数，累加即得答案。

i 从 0 到 id-1、而 cnt 只存 id 及之后的边界条件，保证了每个被统计的子数组一定包含 id（即 m）‍——左端在 id 之前（含 i=0 空前缀），右端在 id 及之后。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 2e5+5, M = 4e5+5;;

int n, m, a[N], id, pre[N], cnt[M], ans;
signed main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == m) id = i;
        a[i] = a[i] <= m ? -1 : 1;
        pre[i] = pre[i-1] + a[i];
        if (id) cnt[pre[i]+N-5]++;
    }
    for (int i = 0; i < id; i++) ans += cnt[pre[i]+N-5] + cnt[pre[i]-1+N-5];
    cout << ans;
    return 0;
}