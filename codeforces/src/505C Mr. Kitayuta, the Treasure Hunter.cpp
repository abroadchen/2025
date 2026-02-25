//
// Created by Psy.C on 2026/2/25.
//
/**
N = 30001：位置数组大小上限
M = 1001：步长数组大小上限
d：起始位置
k：索引偏移量
mx：最大位置坐标
dp[N][M]：记忆化搜索的DP数组
a[N]：在每个位置的得分（计数）
i：当前位置
j：当前步长

如果超出最大位置，返回0
如果该状态已计算过，直接返回结果
状态转移1：步长减1的情况（向左跳）：
新位置：i+j-1
新步长：j-1
得分：当前位置得分a[i] + 后续最优解
状态转移2：步长不变的情况（直跳）：
新位置：i+j
新步长：j
得分：当前位置得分a[i] + 后续最优解
状态转移3：步长加1的情况（向右跳）：
新位置：i+j+1
新步长：j+1
得分：当前位置得分a[i] + 后续最优解
返回当前位置和步长下的最优解

n：点的数量
d：起始步长
x：点的位置
a[x]++：统计位置x上有多少个点
mx = max(mx, x)：更新最大位置
确保dp数组索引不会越界
基于步长变化的范围来确定偏移量
从起始位置d、起始步长d开始搜索，输出最大得分
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define get(x) ((x)-d+k)
using namespace std;
constexpr int N = 30001, M = 1001;
int d, k;
int mx = 0, dp[N][M], a[N];
int dfs(const int i, const int j) {
    if (i > mx) return 0;
    if (dp[i][get(j)] != -1) return dp[i][get(j)];
    if (j-1 > 0)
        dp[i][get(j)] = max(dp[i][get(j)], dfs(i+j-1,j-1)+a[i]);
    dp[i][get(j)] = max(dp[i][get(j)], dfs(i+j, j)+a[i]);
    dp[i][get(j)] = max(dp[i][get(j)], dfs(i+j+1, j+1)+a[i]);
    return dp[i][get(j)];
}

int n;
int main() {
    fast;
    cin >> n >> d;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; a[x]++;
        mx = max(mx, x);
    }
    k = (sqrt(n*8+1)-1.)/2.+5;
    memset(dp, -1, sizeof dp);
    cout << dfs(d, d) << '\n';
    return 0;
}