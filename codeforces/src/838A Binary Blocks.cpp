//
// Created by Psy.C on 2026/9/26.
//
/**
num[i][j] 记录第 i 行第 1..j 列的 1 的个数（行内前缀和）。
注意：这里只做行方向的前缀和（num[i][j] = num[i][j-1] + …），列方向没有累加。后续用它来 O(1) 求某一行内一段区间 [j1, j2] 的 1 的个数：num[i][j2] − num[i][j1−1]
cnt 记录全局最少翻转次数的最终答案，初始为一个"足够大"的值（棋盘最多 N×N 格）
对每个块大小 k（从 2 到 max(n,m)）：
按 k×k 网格切块：外层循环步长 k 遍历所有块的左上角 (i,j)。
数出块内 1 的个数 sum
对块内每一行 l 用行前缀和求 [j, j+k-1] 区间里 1 的个数，逐行累加得到整个块内 1 的总数 sum。
边缘块用 min(n, i+k-1)、min(m, j+k-1) 截断到棋盘边界，即不完整块按实际大小处理
该块的最少翻转次数
块内总格数 ≈ k*k（边缘块实际可能少，但代码统一按 k*k 算——实际这是个小近似，对满格块正确；对边缘块会有冗余计数，但因为不同 k 之间取 min，最终答案仍来自所有 k 的最小值，通常该近似不影响最优解，属常见简化写法）。
sum = 要"全翻成 0"需要翻转的 1 的个数；
k*k - sum = 要"全翻成 1"需要翻转的 0 的个数（即把 0 变 1）。
取两者较小者 = 该块做到"整块同色"的最少翻转数。
对当前 k 求和得到 ans（所有块的最少翻转之和），更新全局最优 cnt = min(ans, cnt)
遍历完全部 k 后，输出全局最小翻转次数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2510;
int n, m, num[N][N];
char mp[N][N];
ll cnt, ans;
int main() {
    fast;
    while (cin >> n >> m) {
        memset(num, 0, sizeof(num));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                cin >> mp[i][j];
                num[i][j] = num[i][j-1] + mp[i][j] - '0';
            }
        cnt = N*N;
        int len = max(n, m);
        for (int k = 2; k <= len; ++k) {
            ans = 0;
            for (int i = 1; i <= n; i += k)
                for (int j = 1; j <= m; j += k) {
                    ll sum = 0;
                    for (int l = i; l <= min(n, i+k-1); ++l)
                        sum += num[l][min(m, j+k-1)] - num[l][j-1];
                    ans += min(k*k - sum, sum);
                }
            cnt = min(ans, cnt);
        }
        cout << cnt << '\n';
    }
    return 0;
}