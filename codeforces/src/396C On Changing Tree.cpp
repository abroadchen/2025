//
// Created by Psy.C on 2026/1/30.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 300010
#define mod 1000000007
using namespace std;

int n;
struct node {
    int v[N];
    void add(int x, const int y) {//将位置 x 加 y
        for (; x <= n; x += x & -x) v[x] = (v[x] + y) % mod;
    }
    [[nodiscard]] int query(int x) const {//前缀和查询
        int res = 0;
        for (; x; x -= x & -x) res = (res + v[x]) % mod;
        return res;
    }
    void update(const int l, const int r, const int val) {//区间更新 [l,r] 加 val
        add(l, val), add(r + 1, -val);
    }
} t1, t2;

int dfn[N], cnt, sz[N], dep[N];
vector<int> e[N];
void dfs(const int x) {
    dfn[x] = ++cnt, sz[x] = 1;//设置节点 x 的 DFS 序 初始化子树大小
    for (const int y : e[x])
        dep[y] = dep[x] + 1, dfs(y), sz[x] += sz[y];
}


int main() {
    fast;
    cin >> n;
    for (int i = 2, x; i <= n; ++i) {
        cin >> x; e[x].emplace_back(i);
    }
    dfs(1);
    int m; cin >> m;
    for (int i = 1, op, v, x, k; i <= m; ++i) {
        cin >> op >> v;
        if (op == 1) {
            cin >> x >> k;
            const int l = dfn[v], r = dfn[v] + sz[v] - 1;//v 子树的 DFS 序范围
            t1.update(l, r, k), t2.update(l, r,
                static_cast<int>((dep[v]*1ll*k+x)%mod));
        } else {//加 2*mod 防止负数
            cout << (t2.query(dfn[v]) - t1.query(dfn[v])*1ll*dep[v]%mod + 2*mod) % mod << '\n';
        }
    }
    return 0;
}