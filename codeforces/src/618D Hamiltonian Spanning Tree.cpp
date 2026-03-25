//
// Created by Psy.C on 2026/3/25.
//
///O(n)，每个节点最多访问一次
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e6+5;

vector<int> g[N];///邻接表存储树
int cnt;
///树中可以配对的节点对数 优先在子树内部配对，剩余能力向上传递
int dfs(int u, int fa) {
    int ans = 2;//当前节点最多可以参与2次配对 度数限制
    for (auto v : g[u]) {
        if (v == fa) continue;//跳过父节点
        //子节点还有配对能力且当前节点还能配对
        if (dfs(v, u) && ans)
            cnt++, ans--;//增加配对数，减少当前节点配对能力
    }
    return ans;//返回当前节点剩余的配对能力
}
///n为节点数，x和y为两种操作的代价
int n, x, y;
signed main() {
    fast;
    cin >> n >> x >> y;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    if (x <= y) dfs(1, 0);//从根节点开始DFS，计算最大配对数
    else {
        //寻找星型图的中心节点（度数为n-1的节点）
        for (int i = 1; i <= n; ++i)
            if (g[i].size() == n - 1) {
                cnt++;
                break;//找到一个就够了
            }
    }
    //cnt对使用x代价，其余(n-cnt-1)对使用y代价
    cout << x*cnt + y*(n-cnt-1) << '\n';
    return 0;
}