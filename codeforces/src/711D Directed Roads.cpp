//
// Created by Psy.C on 2026/4/20.
//
/**
step: 当前深度
u: 当前节点
fa: 当前连通分量的标识
标记访问状态：
vis[u] = fa: 标记节点u属于连通分量fa
cnt[u] = step: 记录到达节点u的步数
继续DFS：
如果to[u]未访问，继续递归dfs(step+1, to[u], fa)
发现环：
如果to[u]已被访问且属于同一连通分量(vis[to[u]] == fa)
计算环的长度：y = cnt[u] - cnt[to[u]] + 1
更新总环长度：sum += y
更新答案：ans = ans*(ksm(2ll, y) - 2) % mod

ksm(2ll, y): 2^y，表示环上y个节点的所有可能状态
ksm(2ll, y) - 2: 减去全0和全1两种非法状态
对于每个环，有(2^y - 2)种合法的二进制赋值方式

初始化和输入
读入n和to数组（表示每个节点指向的下一个节点）
遍历所有连通分量
对每个未访问的节点运行DFS
DFS会处理整个连通分量（包括树的部分和环的部分）
处理剩余节点
ans = ans*ksm(2ll, n-sum) % mod
对于不在环中的节点（树的部分），每个节点有2种选择
总共有(n-sum)个这样的节点

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+7, mod = 1e9+7;

ll ksm(ll a, ll b) {
    ll res = 1; a %= mod;
    while (b) {
        if (b&1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll vis[N], cnt[N], to[N], sum, ans;
void dfs(ll step, ll u, ll fa) {
    vis[u] = fa; cnt[u] = step;
    if (!vis[to[u]]) dfs(step+1, to[u], fa);
    else if (vis[to[u]] == fa) {
        ll y = cnt[u] - cnt[to[u]] + 1;
        sum += y;
        ans = ans*(ksm(2ll, y) - 2) % mod;
    }
}

ll n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> to[i];
    ans = 1, sum = 0;
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) dfs(0, i, i);
    ans = ans*ksm(2ll, n-sum) % mod;
    cout << ans << '\n';
    return 0;
}