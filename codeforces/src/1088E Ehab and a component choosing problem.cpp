//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
a[u]：结点 u 的权值。
e[u]：u 的邻居。
mx：记录当前找到的 最大连通块权值和（因为有负权，用 -inf 初值）。
cnt：达到 mx 的连通块数量
sum = a[u]：以 u 为根的连通块初始和为 u 的权值。
遍历子结点 v（跳过父结点 pre）：
dfs(v,u,f) 返回 v 子树处理后向上传递的和；
只当它 >0 时才加进 sum（max(0, ...)）——若子树贡献为负，就整块不选（选它只会拖低连通和），这是最大连通和的贪心选择。
两次 DFS 的 f 分工：

f=false（第一次）：仅更新 mx = max(mx, sum)，找出整棵树能达到的最大连通块权值和。这次不修改 sum，原样返回给父结点（父结点据此决定是否加）。

f=true（第二次）：若某子树的 sum == mx，说明这是"达到全局最大值的连通块"之一，cnt++，并把该子树 sum 清零（sum = 0）——让父结点不再把它算进去，从而每个取到 mx 的连通块只被独立计数一次，互不重叠。

注意第二次遍历时前面的 mx = max 分支被跳过（!f 为假），只做计数，因此不会改变 mx。
读入 n 个点权、n-1 条边。
两次 DFS 从根 1 出发。
输出 cnt*mx（总计: 最大连通块权值和 × 达到该值的块数）与 cnt（个数）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 3e5+5, inf = 1e9+7;

int a[N], cnt;
vector<int> e[N];
ll mx = -inf;
ll dfs(int u, int pre, bool f) {
    ll sum = a[u];
    for (int v : e[u])
        if (v != pre) sum += max(0ll, dfs(v,u,f));
    if (!f) mx = max(mx, sum);
    else if (sum == mx) cnt++, sum = 0;
    return sum;
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v; e[u].push_back(v); e[v].push_back(u);
    }
    dfs(1,1,0), dfs(1,1,1);
    cout << cnt*mx << ' ' << cnt << '\n';
    return 0;
}