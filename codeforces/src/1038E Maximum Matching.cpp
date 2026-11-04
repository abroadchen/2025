//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
每个 i（1..n）描述一条边：从 c[0][i] 到 c[1][i]，权值为 a[i]。
关键：c[0][i] 和 c[1][i] 取值域很小（0-3，因为后面 fa[5]、find(i) 用到 i=0..4）。所以这是一个点数≤4的小图，a[i] 是边权。
c[0][0]=c[1][0]=1, a[0]=0：把 0 号“边”当作连接到节点1的自环占位，用来统一处理枚举逻辑。
用一个四数组：

s[i]：连通分量 i 的权值和。
ss[i]：节点 i 的度数奇偶（每经过一条边就 ^=1，即异或翻转，1 表示奇度）。
so[i]：某连通分量内"奇度节点个数"
外层 j 从 0 到 n：枚举被删除的那条边（j=0 是那条占位边，相当于"不删任何真实边"）。
内部只处理 i != j 的边，即在删掉边 j 后用剩下的边建图
标准并查集合并连通分量，同时维护分量内边权和 s。
ss[u] ^= 1 让节点 u 的奇偶度翻转——统计每个节点的度奇偶性。
注意：注意这里 s[...] += a[i] 的位置——它把边权加进 c[0][i] 所在根的连通块。合并时把两个块的 s 相加
so[i]：连通分量 i 中奇度节点的个数。
对每个连通分量根：若该分量的奇度节点数不等于 4，则更新 ans = max(ans, 分量的权值和 s[i])。
即：在删掉某条边后，选一个连通块（其奇度节点数 ≠ 4），取其权值和作为候选，取最大
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); i++)
using namespace std;

constexpr int N = 101;

int fa[5];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int n, a[N], c[2][N], s[5], ss[5], so[5], ans;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> c[0][i] >> a[i] >> c[1][i];
    c[0][0] = c[1][0] = 1; a[0] = 0;
    for (int j = 0; j <= n; j++) {
        rep(i,4) fa[i] = i, s[i] = 0, ss[i] = 0, so[i] = 0;
        rep(i,n) if (i != j) {
            if (find(c[0][i]) != find(c[1][i])) {
                s[find(c[1][i])] += s[find(c[0][i])];//合并权值和
                fa[find(c[0][i])] = find(c[1][i]);
            }
            s[find(c[0][i])] += a[i];//把边权加进所在连通块
            ss[c[0][i]]^=1; ss[c[1][i]]^=1;//翻转两端点奇偶度
        }
        rep(i,4) so[find(i)] += ss[i];
        rep(i,4) if (find(i) == i) if (so[i] != 4) ans = max(ans, s[i]);
    }
    cout << ans;
    return 0;
}