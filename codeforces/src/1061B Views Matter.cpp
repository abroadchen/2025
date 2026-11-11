//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
n 个柱子高度 a[i]，m 是某种限制（但主流程里 m 没被使用）。
统计：cnt = Σ a[i]（总砖块数/总面积）
a 升序排列。
遍历中，每遇到一个 a[i] > h 就 h++。由于升序，最后 h 等于"a 中互不相同的值从 1 起步能数到多少"——更准确地说，h 是满足 h < a[?] 连续递增的长度。对排序数组这等价于：h = min(n, max h 使得存在严格递增且 h≤a[h])…… 实际上就是对排序后的 a，数"第一个前缀里能把 1,2,3,... 逐个放进去"最多能到几，即能把柱子砌成高度 1..h 的斜坡的最终高度
ans = 最高高度 + n - h：含义是"把整幅图用砖填成一个高度为某值的完整方块所需的总砖数"——即目标方块的总面积（最高柱子高度 a[n-1] 那一档，每根柱子都要堆到那个高度，共 n 根，但有 h 根已"自然"占据对应斜坡位置所以减掉）。
cnt - ans = 总的砖数 - 目标方块所需砖数，即"能抠出来（多余）的砖块数"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

int n, m, a[N], h, ans;
ll cnt;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) { cin >> a[i]; cnt += a[i]; }
    sort(a, a+n);
    rep(i,n) if (a[i] > h) h++;
    ans = a[n-1] + n - h;
    cout << cnt - ans;
    return 0;
}