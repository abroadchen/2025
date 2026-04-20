//
// Created by Psy.C on 2026/4/20.
//
/**
siz[N]: 以节点为根的子树大小
mx[N]: 节点的重儿子
mx1[N], mx2[N]: 节点子树中最大和第二大子树的根
初始化：siz[x] = 1（包含自身）
遍历子节点：if (siz[to[i]]) continue 避免重复访问
更新子树大小：siz[x] += siz[to[i]]
更新重儿子：mx[x] 记录最大子树
更新最大子树：
如果子树大小 ≤ n/2：直接更新mx1, mx2
否则：使用子树的mx1更新当前节点的mx1, mx2
情况1：siz[mx[x]] <= n/2
重儿子子树大小 ≤ n/2
检查删除后其他部分是否都 ≤ n/2
情况2：siz[mx[x]] > n/2
重儿子子树大小 > n/2
检查重儿子内部是否平衡

mxx: 传递给子节点的最大连通分量大小
m2: 传递第二大子树信息
t: 删除当前节点后，父节点所在连通分量的大小
O(n): 每个节点访问常数次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 4e5+7;

int cnt, to[N<<1], nxt[N<<1], head[N];
void add(int u, int v) {
    to[++cnt] = v, nxt[cnt] = head[u], head[u] = cnt;
}

int siz[N], mx[N], n, mx1[N], mx2[N];
void dfs(int x) {
    siz[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        if (siz[to[i]]) continue;
        dfs(to[i]);
        siz[x] += siz[to[i]];
        if (siz[mx[x]] < siz[to[i]]) mx[x] = to[i];
        if (siz[to[i]] <= n/2) {
            if (siz[to[i]] > siz[mx1[x]]) {
                mx2[x] = mx1[x];
                mx1[x] = to[i];
            } else {
                if (siz[to[i]] > siz[mx2[x]])
                    mx2[x] = to[i];
            }
        } else {
            if (siz[mx1[to[i]]] > siz[mx1[x]]) {
                mx2[x] = mx1[x];
                mx1[x] = mx1[to[i]];
            } else {
                if (siz[mx1[to[i]]] > siz[mx2[x]])
                    mx2[x] = mx1[to[i]];
            }
        }
    }
}

bool vis[N];
int ans[N];
void dfs(int x, int mxx, int m2) {
    vis[x] = true;
    if (siz[mx[x]] <= n/2) {
        if (n - siz[x] > n/2) {
            if (n - siz[x] - mxx > n/2 && n - siz[x] - siz[m2] > n/2)
                ans[x] = 0;
            else ans[x] = 1;
        } else ans[x] = 1;
    } else if (siz[mx[x]] - siz[mx1[mx[x]]] <= n/2) ans[x] = 1;
    else ans[x] = 0;
    for (int i = head[x]; i; i = nxt[i]) {
        if (vis[to[i]]) continue;
        int t = (n - siz[x])*(int(bool(n-siz[x] <= n/2)));
        if (to[i] == mx1[x]) {
            if (m2 == to[i]) m2 = 0;
            if (siz[mx2[x]] >= siz[m2])
                dfs(to[i], max(mxx, t), mx2[x]);
            else dfs(to[i], max(mxx, t), m2);
        } else {
            if (m2 == to[i]) m2 = 0;
            if (siz[mx1[x]] >= siz[m2])
                dfs(to[i], max(mxx, t), mx1[x]);
            else dfs(to[i], max(mxx, t), m2);
        }
    }
}

int main() {
    fast;
    cin >> n;
    for (int i = 1, u, v; i <= n; ++i) {
        cin >> u >> v; add(u, v); add(v, u);
    }
    dfs(1); dfs(1, 0, 0);
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}