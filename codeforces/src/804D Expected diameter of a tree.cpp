//
// Created by Psy.C on 2026/9/19.
//
/**
cc[x]：点 x 所属连通块。
dis[x][i]：点 x 沿第 i 条边方向（到子树 y）的最远距离。
返回以 x 为根的子树最大深度。
作用：给每个点标记连通块，并记录向各子节点方向的最远距离（为直径和"偏心距"准备
dis[x][i] = d + 1：补上通过父节点方向到达子树外的最远距离（换根 DP 的"自顶向下"）。
mx[x]：点 x 到连通块内最远点的距离（偏心距）。
diam[c]：连通块 c 的直径。
某点处直径候选 = mx[x]（最远分支） 或 两最大分支和 ds[0]+ds[1]。
核心换根：对子节点 y，传给它的"来自上方的最远距离" = 排除父分支后剩下的最大值（若父方向是最大分支则用次大 ds[1]），从而算出每个点真实偏心距 mx[x]。
关键结论：某连通块直径为 D 时，任意点到块内某最远点距离 ≤ D，且块直径端点的偏心距就是 D（mx ≤ D，等号成立时说明该点是直径端点）
Dis[i]：连通块 i 内所有点的偏心距 mx 集合（排序）。
sum[i][j]：后缀和（Dis[i][j] + Dis[i][j+1] + ...），便于区间求和。

在连通块 x 中取点 p、连通块 y 中取点 q，需要"跨越两个连通块"连接。设连一个"桥"（连接 p 与 q），则从 p 到 q 经过桥的长度至少 = 从 p 到 x 内某端点 + 桥 + 从 q 到 y 内某端点。

设两个块的直径分别为 Dx, Dy，令 md = max(Dx, Dy)。关键事实：对 x 内任意点 p（偏心距 a=Dis[x][i]），从 p 出发到 y 内任意点 q 的距离 = a + 1 + (q 到 y 内某端点的距离)——而 q 到 y 内端点的距离正好是 q 的偏心距
b
b，但存在一个"封顶"：若
a
+
1
+
b
a+1+b 会超过
m
d
=
a
+
1
md=a+1 与直径的关系……

聪明的化简：对固定的 p（偏心距
a
a）和 y 内的点 q（偏心距
b
b），实际"最长 / 期望代表距离"取
dist
=
max
⁡
(
m
d
,
    
a
+
1
+
b
)
dist=max(md,a+1+b) 的某种形式。代码用的是：

若
b
≥
m
d
−
a
b≥md−a，则贡献
m
d
md（被直径封顶，因为 a+1+b 超出后会受限于桥接两端点但不会超过 md？不——需验证）。
实际上这是换根 DP + 直径的结合：图上两点间距离 = max(在各自块内到某些关键点距离的总和)。当跨越块时，最优路径 = 从 p 到 x 的某端点 + 桥 + 从 y 端点附近到 q。而"x 端点到 y 端点"这段通过桥的最短距离恰为 1（桥直接连通）。于是距离 =
a
+
1
+
b
a+1+b，其中
a
,
b
a,b 是各自到直径端点的距离。但由于直径性质，
a
,
b
≤
a,b≤ 各自直径，且
a
+
1
+
b
a+1+b 的上界由
m
d
md 决定——当选择的端点恰到好处时，总距离等于
max
⁡
(
m
d
,
a
+
1
+
b
)
max(md,a+1+b)。

代码采用二分：

对每个
a
=
D
i
s
[
x
]
[
i
]
a=Dis[x][i]，在 y 的偏心距集合中找第一个
≥
m
d
−
a
≥md−a 的位置 len。
前面的 len 个（
b
<
m
d
−
a
b<md−a）：贡献
a
+
1
+
b
a+1+b？——不，代码让它们贡献 md。
等等，顺序反了：lower_bound(Dis[y], md - a) 找到首个
≥
m
d
−
a
≥md−a 的下标 len。
对 j < len（
b
<
m
d
−
a
b<md−a，即
a
+
1
+
b
≤
m
d
a+1+b≤md）：取
a
+
1
+
b
a+1+b？但代码贡献 md。
对 j ≥ len（
b
≥
m
d
−
a
b≥md−a，即
a
+
1
+
b
>
m
d
a+1+b>md）：代码贡献
(
a
+
1
)
+
b
(a+1)+b（Dis[x][i]+1 项 + sum[y][len] 的后缀和）。
len * md：前 len 个（
b
b 较小的那些，
a
+
1
+
b
≤
m
d
a+1+b≤md）距离封顶为 md。
(size-len)*(Dis[x][i]+1) + sum[y][len]：后 size-len 个（
b
b 较大，
a
+
1
+
b
>
m
d
a+1+b>md）距离 =
a
+
1
+
b
a+1+b，拆成每个都加
(
a
+
1
)
(a+1) 再加各自
b
b 的后缀和。
所以每个点对的距离公式为：
dist
(
p
,
q
)
=
max
⁡
(
m
d
,
    
mx
[
p
]
+
1
+
mx
[
q
]
)
dist(p,q)=max(md,mx[p]+1+mx[q])

这正是"跨连通块两点间距离 = 各自到直径端点的偏心距之和 + 桥 1，但与两块直径最大值取 max"。用三分支——大
b
b 取真实值、小
b
b 被 md 封顶——这样一次二分加后缀和就
O
(
∣
X
∣
log
⁡
∣
Y
∣
)
O(∣X∣log∣Y∣) 算完整个和。

关键原理：跨连通块的最长/代表距离由两块中较大直径 md 和"两偏心距之和+1"共同决定；这是该类"带桥连接的树距离期望"题的标准公式
get(x,y) 返回点对距离之和；除以 |X|*|Y| 得到期望值。
map 记忆化（可打乱 pair 顺序避免重复计算，用 {x,y} 对称性缓存）。
多组数据，while(-scanf) 循环处理
 */
#include <bits/stdc++.h>
#define ll long long
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+5;

int cc[N], cn;
vector<int> v[N]{}, dis[N]{};
int dfs(int x, int fa) {
    cc[x] = cn;
    int d = 0;
    for (int i = 0; i < v[x].size(); ++i) {
        int y = v[x][i];
        if (y == fa) continue;
        dis[x][i] = dfs(y, x) + 1;
        d = max(d, dis[x][i]);
    }
    return d;
}

int mx[N], diam[N];
void dfs2(int x, int fa, int d) {
    for (int i = 0; i < v[x].size(); ++i) {
        int y = v[x][i];
        if (y != fa) continue;
        dis[x][i] = d + 1;
    }
    if (dis[x].empty()) {
        mx[x] = 0;
        diam[cc[x]] = 0; return;
    }
    vector<ii> ds(dis[x].size());
    for (int i = 0; i < ds.size(); ++i) ds[i] = {dis[x][i], i};
    sort(ds.rbegin(), ds.rend());
    mx[x] = ds[0].first;
    diam[cc[x]] = max(mx[x], diam[cc[x]]);
    if (ds.size() > 1)
        diam[cc[x]] = max(diam[cc[x]], ds[0].first+ds[1].first);
    for (int i = 0; i < v[x].size(); ++i) {
        int y = v[x][i];
        if (y == fa) continue;
        if (ds[0].second != i) dfs2(y, x, ds[0].first);
        else if (ds.size() > 1) dfs2(y, x, ds[1].first);
        else dfs2(y, x, 0);
    }
}

vector<int> Dis[N]{}, sum[N]{};
ll get(int x, int y) {
    if (Dis[x].size() > Dis[y].size()) swap(x, y);
    ll ans = 0;
    int md = max(diam[x], diam[y]);
    for (int i = 0; i < Dis[x].size(); ++i) {
        ll len = ranges::lower_bound(Dis[y], md-Dis[x][i]) - Dis[y].begin();
        ans += len*md + (Dis[y].size() - len)*(Dis[x][i] + 1) + sum[y][len];
    }
    return ans;
}

int n, m, q;
int main() {
    while (~scanf("%d%d%d", &n, &m, &q)) {
        memset(cc, 0, sizeof(cc));
        for (int i = 0, x, y; i < m; ++i) {
            scanf("%d%d", &x, &y);
            v[x].push_back(y); v[y].push_back(x);
            dis[x].push_back(-1); dis[y].push_back(-1);
        }
        cn = 0;
        for (int i = 1; i <= n; ++i)
            if (!cc[i]) { ++cn; dfs(i, -1); dfs2(i, -1, 0); }
        for (int i = 1; i <= n; ++i) Dis[cc[i]].push_back(mx[i]);
        for (int i = 1; i <= cn; ++i) {
            ranges::sort(Dis[i]);
            sum[i].resize(Dis[i].size()+1);
            sum[i][Dis[i].size()] = 0;
            for (int j = Dis[i].size()-1; j >= 0; --j)
                sum[i][j] = sum[i][j+1] + Dis[i][j];
        }
        map<ii, double> dp;
        while (q--) {
            int x, y; scanf("%d%d", &x, &y); x = cc[x], y = cc[y];
            if (x == y) { puts("-1"); continue; }
            if (dp.count({x, y}) == 1)
                printf("%0.9lf\n", dp[{x, y}]);
            else {
                ll t = get(x, y), u = 1ll*Dis[x].size()*Dis[y].size();
                double ans = (double)t/u;
                printf("%0.9lf\n", ans);
                dp[{x, y}] = ans;
            }
        }
    }
    return 0;
}