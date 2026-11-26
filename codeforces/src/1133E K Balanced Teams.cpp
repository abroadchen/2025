//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
dp[i][j]: 前i个元素选j组的最大覆盖数
单调队列(存下标), 维护可转移的左端点候选
排序后，满足 差 ≤ 5 的组必为连续区间。
把所有状态初始化为极小值（不可达），dp[i][0] 保留为 0

dp[i][j] = max( dp[i-1][j],  max_{k 满足条件} ( dp[k][j-1] + (i-k) ) )
其中 dp[k][j-1] + (i-k) = (dp[k][j-1] - k) + i。
把与 k 相关的部分合并成 dp[k][j-1] - k，这样给定 i 时 i 是常数，只需最大化 dp[k][j-1] - k。用单调队列维护 dp[·][j-1] - · 的最大值，即可 O(1) 取最优 k

队尾放入 j-1（因为 i 至少要从 j 开始，k 从 j-1 起）。
对每个 i：
合法性裁剪：队头若 s[i]-s[q.front()+1] > 5 则弹出（该左端点无法与当前 i 成组）。
取队头为最优 k，更新 dp[i][j] = max(dp[i-1][j], dp[k][j-1] + i-k)。
维护单调性：把当前 i 作为后续左端点候选入队，若队尾的 dp[·][j-1]-· 不比新元素优就弹出，保持队列内 dp-下标 单调递减。
本 j 层结束清空队列，进入下一层。
组数可以不必须用满 k 组，所以取 dp[n][0..k] 的最大值作为答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; ++i)
using namespace std;

constexpr int N = 5005;
int n, k, s[N], dp[N][N];
deque<int> q;
int main() {
    fast;
    cin >> n >> k;
    rep(i,1,n) cin >> s[i];
    sort(s+1, s+n+1);
    rep(i,0,n) rep(j,1,k) dp[i][j] = INT_MIN;
    rep(j,1,k) {
        q.push_back(j-1);
        rep(i,j,n) {
            while (!q.empty()) {
                if (s[i]-s[q.front()+1] > 5) q.pop_front();
                else break;
            }
            int k = q.front();
            dp[i][j] = max(dp[i-1][j],dp[k][j-1]+i-k);
            while (!q.empty()) {
                if (dp[q.back()][j-1]-q.back() <= dp[i][j-1]-i) q.pop_back();
                else break;
            }
            q.push_back(i);
        }
        q.clear();
    }
    int mx = INT_MIN;
    rep(i,0,k) mx = max(mx, dp[n][i]);
    cout << mx;
    return 0;
}