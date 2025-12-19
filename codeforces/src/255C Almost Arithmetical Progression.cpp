//
// Created by Psy.C on 2025/12/18.
//
/*
 *
*外层循环遍历每个位置i（从1到n）：
int pre = 0; 初始化pre为0，用于记录之前遇到的与当前位置相同值的位置
内层循环遍历所有小于i的位置j（从0到i-1）：
dp[i][j] = max(dp[i][j], dp[j][pre] + 1); 状态转移方程：
考虑以位置i结尾、前一个特殊位置为j的序列
这个序列的长度至少是"以位置j结尾、前一个特殊位置为pre的序列"长度加1
if (v[i] == v[j]) pre = j; 如果位置i和j的值相同，则更新pre为j
ans = max(ans, dp[i][j]); 更新全局最大值
 *
 *时间复杂度是O(n²)，空间复杂度也是O(n²)
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin>>n;
    vector<int> v(n + 1);
    for (auto& i : v) i = 0;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    for (auto& i : dp) for (auto& j : i) j = 0;
    for (int i = 1; i <= n; ++i) cin >> v[i];
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int pre = 0;
        for (int j = 0; j < i; ++j) {
            dp[i][j] = max(dp[i][j], dp[j][pre] + 1);
            if (v[i] == v[j]) pre = j;
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans << '\n';
    return 0;
}