//
// Created by Psy.C on 2026/3/25.
//
/**
n表示节点数，m表示边数，dp数组存储每个节点的最长路径长度
e[i]存储与节点i相连的所有节点
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
int n, m, dp[N];
vector<int> e[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        e[u].push_back(v); e[v].push_back(u);
    }
    //计算每个节点的最长下降路径长度（从大到小）
    for (int i = 1; i <= n; ++i) {
        dp[i] = 1;//初始化当前节点的路径长度为1（节点本身）
        //遍历节点i的所有邻居
        for (int j = 0; j < e[i].size(); ++j) {
            //邻居节点编号大于当前节点，则跳过（确保只考虑比当前节点编号小的邻居）
            if (e[i][j] > i) continue;
            //当前值与邻居路径长度+1中的较大者
            dp[i] = max(dp[i], dp[e[i][j]] + 1);
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = max(ans, (ll)dp[i]*(ll)e[i].size());//路径长度乘以度数
    cout << ans << '\n';
    return 0;
}