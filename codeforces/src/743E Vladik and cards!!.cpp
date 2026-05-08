//
// Created by Psy.C on 2026/5/8.
//
/**
t[M+7]：临时存储每种颜色的位置
pos[M+7]：存储每种颜色在原数组中的位置
dp[N][(1<<M)+7]：动态规划数组，其中(1<<M)表示2^M，即所有可能的状态组合
a[N]：原数组
n：数组长度

复制pos数组到t数组
初始化dp数组为极小值
设置初始状态dp[0][0]=0
外层循环遍历位置
内层循环遍历所有可能的状态j
对于每个未使用的颜色k+1（!(j&(1<<k))判断），尝试将其加入
如果颜色k+1的数量大于num，则可以使用完整的num个
如果颜色k+1的数量大于等于num，则可以使用num-1个
j|(1<<k)：将颜色k+1标记为已使用
最后删除当前位置的颜色
寻找所有状态都完成时的最大值
返回num*8 + res（num*8是基础分数，res是额外分数）

读入数组，并记录每种颜色的所有位置
检查是否有空的颜色，如果有则输出非空颜色的数量
二分查找最优的num值
~check(mid)：检查函数返回值是否非负
输出最优解
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+7, M = 8;

vector<int> t[M+7], pos[M+7];
int dp[N][(1<<M)+7], a[N], n;
int check(int num) {
    for (int i = 1; i <= M; ++i) t[i] = pos[i];
    memset(dp, -0x3f, sizeof dp);
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        int lim = (1<<M)-1;
        for (int j = 0; j <= lim; ++j) {
            if (dp[i][j] >= 0)
                for (int k = 0; k < M; ++k) {
                    if (!(j&(1<<k))) {
                        if (t[k+1].size() > num)
                            dp[t[k+1][num]][j|(1<<k)] = max(dp[t[k+1][num]][j|(1<<k)], dp[i][j]+1);
                        if (t[k+1].size() >= num)
                            dp[t[k+1][num-1]][j|(1<<k)] = max(dp[t[k+1][num-1]][j|(1<<k)], dp[i][j]);
                    }
                }
        }
        if (a[i]) t[a[i]].erase(t[a[i]].begin());
    }
    int res = -1;
    for (int i = 1; i <= n; ++i)
        res = max(res, dp[i][(1<<M)-1]);
    if (res == -1) return -1;
    return num*8 + res;
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    for (int i = 1; i <= M; ++i) {
        if (pos[i].empty()) {
            int ans = 0;
            for (int j = 1; j <= M; ++j)
                if (!pos[j].empty()) ans++;
            return cout << ans, 0;
        }
    }
    int l = 1, r = n/8+1;
    while (l + 1 < r) {
        int mid = (l+r)>>1;
        if (~check(mid)) l = mid; else r = mid;
    }
    cout << check(l);
    return 0;
}