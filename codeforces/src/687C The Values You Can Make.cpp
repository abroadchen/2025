//
// Created by Psy.C on 2026/4/15.
//
/**
n, k：物品数量和目标和
ans：存储所有可能的结果
dp[i][j]：布尔数组，表示能否用物品凑出总和为i，其中选择的物品和为j
dp[0][0]=1表示总和为0、选择和为0的状态可达
外层循环：遍历n个物品，每次读取一个物品的值x
状态转移：
dp[i+x][j] = 1：不选择当前物品x，总和变为i+x，选择和仍为j
dp[i+x][j+x] = 1：选择当前物品x，总和变为i+x，选择和变为j+x
逆序遍历：避免重复使用同一个物品（0-1背包特性）
遍历dp[k][j]，找出所有可能的"选择和"
先输出可能结果的数量，再输出所有可能的结果

时间复杂度：O(n×k²)
空间复杂度：O(k²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;
int n, k, ans[N];
bool dp[N][N];
int main() {
    fast;
    cin >> n >> k;
    int cnt = 0; dp[0][0] = 1;
    for (int y = 1, x; y <= n; ++y) {
        cin >> x;
        for (int i = k-x; i >= 0; --i)
            for (int j = 0; j <= i; ++j)
                if (dp[i][j])
                    dp[i+x][j] = dp[i+x][j+x] = 1;
    }
    for (int j = 0; j <= k; ++j)
        if (dp[k][j]) ans[++cnt] = j;
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; ++i) cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}