//
// Created by Psy.C on 2025/11/17.
//
/*
 *矩阵维度n, m和目标序列编号k
 *创建(n+1)×(m+1)的二维向量p存储权重值
 *
*t = n + m - 1：对角线总数
创建向量mn存储每条对角线的最小权重值
按照对角线分组：位置(i,j)属于第(i+j-1)条对角线
对每条对角线记录最小权重值
*创建lev向量存储对角线索引(1到t)
按照各对角线的最小权重值对索引进行排序
权重小的对角线优先处理
*创建ans向量存储结果字符，初始化为'?'
mx = t/2 + 1：最大可能的括号嵌套层数
 *
*定义lambda函数dfs用于计算当前配置下的合法序列数
创建dp数组：dp[i][s]表示从第i个位置开始，当前嵌套层数为s的方案数
边界条件：dp[t+1][0] = 1（结束状态）
*状态转移：
如果位置i确定为'('：只能从前一层s+1转移过来
如果位置i确定为')'：只能从前一层s-1转移过来
如果位置i未确定：可以从s+1和s-1两种状态转移过来
*优化：如果方案数超过k，截断为k+1（避免溢出）
返回dp[1][0]：从第1个位置开始，嵌套层数为0的方案数
 *
*按权重顺序处理每条对角线
先假设位置x放'('，计算合法序列数cnt
如果k > cnt，说明第k个序列不在这个选择中
改为放')'
更新k = k - cnt（跳过所有'('开头的序列）
*按照行列顺序输出结果矩阵
位置(i,j)对应ans[i+j-1]
 *
 */
#include <vector>
#include <iostream>
#include <algorithm>
#define rep(i,n) for(int i=1;i<=(n);++i)
using namespace std;

typedef long long ll;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m; ll k; cin>>n>>m>>k;
    vector<vector<int>> p(n + 1, vector<int>(m + 1));
    rep(i,n) rep(j,m) cin>>p[i][j];
    int t = n + m - 1;
    vector<int> mn(t + 1, INT_MAX);
    rep(i,n) rep(j,m) {
        int x = i + j - 1;
        if (p[i][j] < mn[x]) mn[x] = p[i][j];
    }
    vector<int> lev(t);
    for (int i = 0; i < t; ++i) lev[i] = i + 1;
    sort(lev.begin(), lev.end(), [&](int i, int j) {
        return mn[i] < mn[j];
    });
    vector<char> ans(t + 1, '?');
    int mx = t / 2 + 1;

    auto dfs = [&]() -> ll {
        vector<vector<ll>> dp(t + 2, vector<ll>(mx, 0));
        dp[t + 1][0] = 1;
        for (int i = t; i >= 1; --i) {
            for (int s = 0; s < mx; ++s) {
                if (ans[i] == '(') {
                    if (s + 1 < mx) dp[i][s] = dp[i + 1][s + 1];
                    else dp[i][s] = 0;
                } else if (ans[i] == ')') {
                    if (s - 1 >= 0) dp[i][s] = dp[i + 1][s - 1];
                    else dp[i][s] = 0;
                } else {
                    dp[i][s] = 0;
                    if (s + 1 < mx) dp[i][s] += dp[i + 1][s + 1];
                    if (s - 1 >= 0) dp[i][s] += dp[i + 1][s - 1];
                }
                if (dp[i][s] > k) dp[i][s] = k + 1;
            }
        }
        return dp[1][0];
    };

    for (int i = 0; i < t; ++i) {
        int x = lev[i];
        ans[x] = '(';
        ll cnt = dfs();
        if (k > cnt) { ans[x] = ')'; k -= cnt; }
    }
    rep(i,n) {
        rep(j,m) { int x = i + j - 1; cout << ans[x]; }
        cout << '\n';
    }
    return 0;
}