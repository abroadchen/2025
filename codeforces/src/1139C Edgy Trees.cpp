//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
输入 n-1 条边（树的最小连通边数）。
若边权 c == 0，则这条边保留并加入邻接表；权值非 0 的边被跳过。
因此 v[] 中只含"有效连通"的边，图变成若干个独立连通块
对每个未访问结点启动 DFS，cnt 累加该连通块内结点数。
由于只用 c==0 的边，数的是"哪些点仍然彼此连通"
返回 x^c mod mod。
但当 c 很大（如 k ≤ 1e9）时会超时。真正的快速幂应该用 while(c){ if(c&1)...; x=x*x; c>>=1; }。
res = n^k：全体方案数。
对每个连通块，累加 块大小^k 到 num。
最终答案 = n^k − Σ(块大小^k)，取模
在一棵树上，每条带权边（c=1）表示"不能同时选择"的关系，求"选择 k 个点，且不含任何非零权边连接的方案数"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+10, mod = 1e9+7;

ll ksm(int x, int c) {
    ll ans = 1;
    for (int i = 0; i < c; i++)
        ans = ans*x%mod;
    return ans;
}

bool vis[N];
int cnt;
vector<int> v[N];
void dfs(int x) {
    vis[x] = 1; ++cnt;
    for (auto i : v[x])
        if (!vis[i]) dfs(i);
}

int n, k;
ll res, num;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1, a, b, c; i < n; i++) {
        cin >> a >> b >> c;
        if (c == 0) v[a].push_back(b), v[b].push_back(a);
    }
    res = ksm(n%mod,k)%mod;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            cnt = 0; dfs(i);
            num = (num+ksm(cnt,k))%mod;
        }
    cout << (res-num+mod)%mod;
    return 0;
}