//
// Created by Psy.C on 2026/10/5.
//
/**
选定标记点 1 作为根，把 d[1][x] 当作“深度”
利用树上距离公式：LCA 深度 = (depth(a)+depth(b)−dist(a,b))/2
若标记点
i
i 与
j
j 的 LCA 深度 =
dep
(
p
[
i
]
)
dep(p[i])，说明
i
i 是
j
j 的祖先
取深度最深的那个祖先作为
j
j 的“父亲标记点”fa[j]
对每个标记点
j
j，路径条件 d[j][i]+d[fa[j]][i]==d[j][p[fa[j]]] 表示节点
i
i 在
j
j 与 fa[j] 的路径上
且深度落在两者之间，则把该节点按深度记入 con[j]
把 con[j] 按深度排序后，依次让深度小的作为深度大的父节点，最后接到 p[fa[j]]
这样标记点
j
j 到其祖先之间的整条链就重建好了
对每个还没确定位置的节点，先尝试挂在某个标记点下；若不行，就在已重建路径上定位其父节点
把挂在同一点下的普通节点按深度串成链
最后输出每条边（节点 → 其父节点）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,a,b) for (int i=(a);i<=(b);++i)
#define ii pair<int,int>
using namespace std;
constexpr int N = 3e4+5, M = 205;

int d[M][N], p[M];
int dep(int x) { return d[1][x]; }
int lcadep(int x, int y) { return (dep(p[x]) + dep(p[y]) - d[x][p[y]]) / 2; }//求两个标记点的 LCA 深度
int lca(int x, int y) { return (dep(p[x]) + dep(y) - d[x][y]) / 2; }//求标记点x与普通点y的LCA深度

bool mk[N];
int fa[M], f[N];
vector<ii> con[M], h[N];
int main() {
    fast;
    int n, k; cin >> n >> k;
    rep(i,1,k) {
        bool flg = false;
        rep(j,1,n) {
            cin >> d[i][j];
            if (d[i][j] == 0) { p[i] = j; mk[p[i]] = true; flg = true; }//找到每个标记点自身位置
        }
        if (!flg) { cout << -1 << '\n'; return 0; }
    }
    rep(i,1,k) {
        rep(j,1,k) {
            if (i == j) continue;
            if (lcadep(i, j) == dep(p[i])) {//j 的 LCA 恰好等于 i 的位置 ⇒ i 是 j 的祖先
                if (dep(p[i]) > dep(p[fa[j]]) || !fa[j]) fa[j] = i;
            }
        }
    }
    rep(i,1,n) {
        rep(j,2,k) {
            if (p[j] != i && p[fa[j]] != i) {
                if (d[j][i] + d[fa[j]][i] == d[j][p[fa[j]]] &&
                    dep(i) > dep(p[fa[j]]) && dep(i) < dep(p[j])) {
                    con[j].emplace_back(dep(i), i);
                    mk[i] = true;
                }
            }
        }
    }
    rep(i,2,k) {
        ranges::sort(con[i]);
        int lst = p[fa[i]];
        for (auto u: con[i] | views::values) {
            f[u] = lst; lst = u;
        }
        f[p[i]] = lst;
    }
    rep(i,1,n) {
        if (mk[i]) continue;
        int mx = -1, pt = 0;
        rep(j,1,k) {
            if (lca(j, i) > mx) {
                mx = lca(j, i);
                pt = j;
            } else if (lca(j, i) == mx) {
                if (dep(p[pt]) > dep(p[j])) pt = j;
            }
        }
        if (lca(pt, i) == dep(p[pt])) {
            h[p[pt]].emplace_back(dep(i), i);
            continue;
        }
        mx = 0;
        rep(j,2,k) {
            if (lca(j, i) > dep(p[fa[j]]) && lca(j, i) < dep(p[j])) {
                int cur = con[j][lca(j, i) - dep(p[fa[j]]) - 1].second;
                if (dep(cur) > dep(mx)) mx = cur;
            }
        }
        h[mx].emplace_back(dep(i), i);
    }
    rep(i,1,n) {
        if (mk[i]) {
            ranges::sort(h[i]);//按深度排序
            int cur = i, lst = i;
            for (auto u: h[i] | views::values) {
                if (dep(u) != dep(lst)) cur = lst;//深度变化则换父
                f[u] = cur;
                mk[u] = true;
                lst = u;
            }
        }
    }
    rep(i,1,n) if (f[i]) cout << i << ' ' << f[i] << '\n';
    return 0;
}