//
// Created by Psy.C on 2026/5/8.
//
/**
to[]：边指向的节点
head[]：以某节点为起点的第一条边
nxt[]：同一起点的下一条边
cnt：边的编号计数器
添加无向边a-b，同时添加双向边（因为是树）
计算以每个节点为根的子树的权值和
sum[x]表示以x为根的子树中所有节点权值的总和
避免回到父节点
ret[x]：以x为根的子树中的最大子树和
v[x]：存储x的所有子节点对应的最大子树和
递归更新当前节点的最大值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+7;
constexpr ll inf = 1e18;

int to[N<<2], head[N<<2], nxt[N<<2], cnt;
void add(int a, int b) {
    to[++cnt] = b, nxt[cnt] = head[a], head[a] = cnt;
    to[++cnt] = a, nxt[cnt] = head[b], head[b] = cnt;
}

ll sum[N], a[N];
void dfs(int x, int fa) {
    sum[x] = a[x];
    for (int i = head[x]; i; i = nxt[i]) {
        int now = to[i];
        if (now != fa) {
            dfs(now, x);
            sum[x] += sum[now];
        }
    }
}

ll ret[N];
vector<ll> v[N];
void dfs2(int x, int fa) {
    ret[x] = sum[x];
    for (int i = head[x]; i; i = nxt[i]) {
        int now = to[i];
        if (now == fa) continue;
        dfs2(now, x);
        v[x].push_back(ret[now]);
        ret[x] = max(ret[x], ret[now]);
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, x, y; i <= n-1; ++i) {
        cin >> x >> y; add(x, y);
    }
    dfs(1, 0); dfs2(1, 0);
    ll ans = -inf;
    for (int i = 1; i <= n; ++i)
        if (v[i].size() > 1) ranges::sort(v[i], [](ll a, ll b) {
            return a > b;//降序排列
        });
    for (int i = 1; i <= n; ++i)
        if (v[i].size() > 1) ans = max(ans, v[i][0]+v[i][1]);//每个节点的前两个最大子树和
    if (ans != -inf) cout << ans << '\n';
    else cout << "Impossible\n";
    return 0;
}