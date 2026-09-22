//
// Created by Psy.C on 2026/9/22.
//
/**
dif[N]：差分数组。坐标范围约 1..2e5（故开 2e5+5）。
pre[N]：前缀和数组，pre[i] 表示坐标 1..i 里"被 ≥k 个区间覆盖"的点的个数
n 个区间、阈值 k、q 次询问
对每个区间 [l, r]，在起点 l 处 +1、在 r+1 处 -1。
这是差分更新：经过后续一次前缀累加就能得到"每个坐标被多少个区间覆盖"。r+1 减一保证区间闭端点 r 本身被计入覆盖（整点计数）
dif[i] += dif[i-1]：把差分变成当前坐标 i 被覆盖的次数（前缀和还原）。
若 dif[i] >= k（该点被 ≥k 个区间覆盖），则 pre[i] 比 pre[i-1] 多 1（把这个点算入"合格点"）；
否则 pre[i] = pre[i-1]（该点不算）。
这样 pre[i] 就是"坐标 1..i 上合格点的累计个数"，是一个可做区间差的前缀数组
对每次询问 [l, r]：区间内合格点数 = 累计到 r 的个数 pre[r] 减去 l 之前的部分 pre[l-1]。
利用前缀和相减，每次询问 O(1) 得出答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+5;
int dif[N], pre[N];
int main() {
    fast;
    int n, k, q; cin>>n>>k>>q;
    for (int i = 0, l, r; i < n; ++i) {
        cin>>l>>r;
        dif[l]++; dif[r+1]--;
    }
    for (int i = 1; i <= N-5; ++i) {
        dif[i] += dif[i-1];
        if (dif[i] >= k) pre[i] = pre[i-1] + 1;
        else pre[i] = pre[i-1];
    }
    while (q--) {
        int l, r; cin>>l>>r;
        cout << pre[r] - pre[l-1] << '\n';
    }
    return 0;
}