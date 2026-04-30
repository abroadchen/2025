//
// Created by Psy.C on 2026/4/29.
//
/**
dp[N]: 动态规划数组
sw[N]: 某集合中w值的总和
sb[N]: 某集合中b值的总和
v[N]: 每个连通分量包含的物品列表
n: 节点数量
m: 边的数量
q: 背包容量
w[N]: 权重数组
b[N]: 价值数组

对于每个节点i，找到其所在连通分量的根节点x
将(w[i], b[i])添加到对应连通分量的物品列表
累加权重和价值到对应分量的总和
对于每个非空的连通分量，添加一个"全部选择"的选项
这样可以选择整个连通分量或者其中的部分物品
遍历每个连通分量
对于非空的连通分量进行背包DP
外层循环是背包容量从大到小
内层循环遍历当前连通分量中的所有物品选项
对于每个物品，如果容量够就更新dp值
输出容量为q时的最大价值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pll pair<ll, ll>
using namespace std;
constexpr int N = 1e3+7;
int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void join(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) fa[x] = y;
}

ll dp[N], sw[N], sb[N];
vector<pll> v[N];

void init() {
    for (int i = 0; i < N; ++i) {
        v[i].clear();
        dp[i] = 0; fa[i] = i;
        sw[i] = 0; sb[i] = 0;
    }
}

int n, m, q;
ll w[N], b[N];
int main() {
    fast;
    cin >> n >> m >> q; init();
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y; join(x, y);//将对应的节点合并到同一个连通分量
    }
    for (int i = 1; i <= n; ++i) {
        int x = find(i);
        v[x].emplace_back(w[i], b[i]);
        sw[x] += w[i]; sb[x] += b[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (v[i].empty()) continue;
        v[i].emplace_back(sw[i], sb[i]);
    }
    for (int i = 1; i <= n; ++i) {
        if (v[i].empty()) continue;
        for (int j = q; j > 0; --j) {
            for (auto &[fst, snd] : v[i]) {
                if (ll W = fst, B = snd; j - W >= 0)
                    dp[j] = max(dp[j], dp[j-W] + B);
            }
        }
    }
    cout << dp[q] << '\n';
    return 0;
}