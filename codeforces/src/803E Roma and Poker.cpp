//
// Created by Psy.C on 2026/9/19.
//
/**
有一局 n 步的比赛记录 str，每步是 W（赢，分数 +1）、L（输，分数 -1）、D（平，分数不变）、?（未知，三者皆可）。
dp[i][j] 表示走了 i 步后，当前"分数 + k"等于 j 是否可行。
关键：j = 分数 + k，所以分数范围是 [-k, k]，对应 j ∈ [0, 2k]。初始 dp[0][k]=1（0 步，分数 0，即 j=k）。
2*k 是 j 的最大下标，因为分数最低 -k、最高 +k，偏移 k 后就是 0-2k。数组第二维 M=4e3+5 只是开大点。
get(i, l, d, w)：在第 i 步，l/d/w 表示该步是否允许 L/D/W 三种动作。
对每个可行状态 (i-1,j) 做转移：
d：平 → dp[i][j]=1（分数不变）。
l：输 → 分数 j-1；若还没到最后一步且 j-1==0（分数已到下限 -k）则跳过（不允许超越边界）。
w：赢 → 分数 j+1；同理上限边界 j+1==2*k 时若非最后一步则跳过。
边界规则：中间步不允许分数越界（-k 到 k），但最后一步允许冲过边界（对应"比分可以是 -k 或 k 这种极端终局"
?：L/D/W 都允许（传 1,1,1）。
D：只允许平（0,1,0）。
W：只允许赢（0,0,1）。
L：只允许输（1,0,0）
若最后一步是 D（平）‍，则终局分数必然等于上一步——而题目目标终局必须是 ±k 边界，平局不可能到达边界，故直接 NO
从终态 (n, j0) 回溯到起点 (0, k)，根据前驱 dp 值选择具体动作。
明确字符：直接按 D/W/L 反推前驱。
?：尝试三种前驱，谁可行走谁，构造完整操作串 s
目标终局分数必须是 -k（j=0）‍ 或 +k（j=2k）‍ 两个极端之一。
哪个可达就从哪个回溯；都不可达 → NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e3+5, M = 4e3+5;

int k, dp[N][M], n;
void get(int i, int l, int d, int w) {
    for (int j = 1; j < 2*k; ++j) {
        if (dp[i-1][j]) {
            if (d) dp[i][j] = 1;
            if (l) {
                if (i != n && j-1 == 0) continue;
                dp[i][j-1] = 1;
            }
            if (w) {
                if (i != n && j+1 == 2*k) continue;
                dp[i][j+1] = 1;
            }
        }
    }
}

string s, str;
bool dfs(int i, int j, const string& ans) {
    if (i == 0 && j == k) { s = ans; return true; }
    if (str[i-1] != '?') {
        if (str[i-1] == 'D') return dfs(i-1, j, 'D'+ans);
        if (str[i-1] == 'W') return dfs(i-1, j-1, 'W'+ans);
        if (str[i-1] == 'L') return dfs(i-1, j+1, 'L'+ans);
    } else {
        if (dp[i-1][j] && dfs(i-1, j, 'D'+ans)) return true;
        if (dp[i-1][j-1] && dfs(i-1, j-1, 'W'+ans)) return true;
        if (dp[i-1][j+1] && dfs(i-1, j+1, 'L'+ans)) return true;
    }
}

int main() {
    fast;
    while (cin >> n >> k) {
        memset(dp, 0, sizeof dp); dp[0][k] = 1;
        cin >> str;
        if (str[n-1] == 'D') { cout << "NO\n"; continue; }
        for (int i = 1; i <= n; ++i) {
            if (str[i-1] == '?') get(i, 1, 1, 1);
            else if (str[i-1] == 'D') get(i, 0, 1, 0);
            else if (str[i-1] == 'W') get(i, 0, 0, 1);
            else get(i, 1, 0, 0);
        }
        string ans;
        if (dp[n][0]) { dfs(n, 0, ans); cout << s << '\n'; }
        else if (dp[n][2*k]) { dfs(n, 2*k, ans); cout << s << '\n'; }
        else cout << "NO\n";
    }
    return 0;
}