//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
维护一个有序去重数组 v 和对应计数 cnt：
每次二分找到 x 应插入位置 y。
若 v[y]==x，则 cnt[y]++（该卡片出现次数 +1）。
否则在位置 y 插入新卡片，计数 1。
结果：v 是去重后的所有不同卡片类型，cnt[i] 是第 i 种卡片在池里的总出现次数
读入 n 个数 val[1..n]，这是某种需要的卡片清单？实际这表示"要组成的某需求"。
对每个 val[i]，在卡片池 v 中二分，若存在则 tot[y]++。
结果：tot[y] 表示第 y 种卡片在需求清单里需要几张
h[1..k] 是价值函数：h[l] 表示当你"收集到 l 张同一种卡"时获得的价值
dp[i][j] 表示：前 i 种卡（假设每种最多 k 张）总共收集 j 张时能获得的最大总价值。
状态转移：对第 i 种卡，可选 l = 1..min(j,k) 张，获得 h[l] 价值，剩余 j−l 张由前 i−1 种承担 → dp[i-1][j-l] + h[l]。
取 max，且与不选该种（dp[i][j] 保持）比较。
边界：dp[0][0]=0，i 从 1 开始
遍历每种实际存在的卡片 i：
tot[i] 是需求中该卡需要的张数，cnt[i] 是池中可用张数。
dp[tot[i]][cnt[i]] 表示"在最多收集 cnt[i] 张、且由 tot[i] 种单位分担"下，收集这 cnt[i] 张能获得的最大价值（这正代表该种卡能贡献的最大价值）。
ans 累加所有种类卡的价值
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;
constexpr int N = 510, M = 20;

int n, k, x, val[N], tot[N*M], h[N], dp[N][N*M];
vector<int> v, cnt;
int main() {
    fast;
    cin >> n >> k;
    rep(i,n*k) {
        cin >> x;
        if (v.empty()) { v.push_back(x); cnt.push_back(1); continue; }
        int y = lower_bound(v.begin(), v.end(), x) - v.begin();
        if (v[y] == x) cnt[y]++;
        else {
            v.insert(v.begin()+y, x);
            cnt.insert(cnt.begin()+y, 1);
        }
    }
    rep(i,n) {
        cin >> val[i];
        int y = lower_bound(v.begin(), v.end(), val[i]) - v.begin();
        if (v[y] == val[i]) tot[y]++;
    }
    rep(i,k) cin >> h[i];
    rep(i,n) rep(j,n*k) for (int l = 1; l <= j && l <= k; l++)
        dp[i][j] = max(dp[i-1][j-l]+h[l], dp[i][j]);
    int ans = 0;
    for (int i = 0; i < v.size(); i++) ans += dp[tot[i]][cnt[i]];

    cout << ans;
    return 0;
}