//
// Created by Psy.C on 2026/9/25.
//
/**
邻接表存无向边，to 是邻居，data 是边权（z）。
输入是 n 条边、n 个点 → 每个连通块是恰好一个环的基环树（这里只有一个连通块，即一个普通环）
vis：DFS 访问标记（用于找环）。
h：标记该节点在环上（true 表示在环上）
从 1 开始 DFS。fa 是父节点。
遍历每条出边：跳过回到父亲的边。
若邻居已被访问（vis 为 1）且不在环上 → 说明我们发现了环（后向边）。此时把当前点 x 标记为环上 h[x]=1，并记录 num = 邻居（标记环的"入口"）。
否则递归 dfs(邻居, x)，返回值 lim 若非 0，则把它传给上层 num（即在回溯过程中沿环把路径上的所有点都标记为 h=1）。
本节点若 num 非 0 → 自己也 h[x]=1（在环上）。
若 num == x（走完整个环回到起点）→ 返回 0 结束这一圈；否则向上返回 num。
效果：h[x]=true 当且仅当 x 在环上。
f[x][0]：x 向非环子树方向能走出的最长链。
f[x][1]：x 向非环子树方向的次长链。
get 把新值 y 放进取 f[x][1]，若不小于 f[x][0] 就交换，保持 f[x][0] 是最长。这样 f[x][0]+f[x][1] 是"经过 x 的、完全在子树内的最长路径"。
对环上点 x，遍历其非环（!h）的子节点，递归求子树 DP。
get(x, 子[x].f[0] + 边权)：用子节点的最长链加上当前边权，更新 x 的最长/次长链。
结果：f[x][0] 是 x 离开环、向内部子树走的最长距离
从环上任一点 x 出发，沿环上的 h=1 节点走，把环上每个点按顺序存入 id[1..cnt]，dis[cnt] 记录从起点走到该点的环上前缀距离 sum。
当走到下一个节点是 num（等于起点）时，说明绕完一圈：
把环复制成两倍：id[j]=id[j-cnt], dis[j] = 总环长 + dis[j-cnt]（总环长 = dis[cnt] + 当前边权 a[x][i].data）。
这样 id[1..2*cnt] 就是断成一条两倍长的链，方便后面做区间查询覆盖任意"环上不重边的一段路径"。
返回即可（环上每个点只有一个继续方向，所以每次只递归一次就 return）

预处理两个方向的最值数组，用于环上任意区间求最优值：
st1[i][0] = f[id[i]][0] - dis[i]：环点 id[i] 的子树最长链减去环上前缀距离。
st2[i][0] = f[id[i]][0] + dis[i]：环点 id[i] 的子树最长链加上环上前缀距离。
还有位置表 n1, n2 记录每个区间最值对应的下标（用于后续 solve 中确定最优点的位置）：
构建 ST（倍增合并 max，同时保存最大值的下标位置）

f1(l,r)：区间内 st1 的最大值。
f2(l,r)：区间内 st2 的最大值。
if (l>r) return 0：空区间返回 0（不贡献）
目标：在环上区间 [l,r] 内找两个环点 u、v，使得 f[u][0] + f[v][0] + 环上u到v的距离 最大（这是"经过环上 u、v 两点之间路径的最长路径"）。
环上 u 到 v 的距离 = dis[v] - dis[u]（若 v 在 u 后面），所以表达式转成 (f[id[u]][0] - dis[u]) + (f[id[v]][0] + dis[v])，分别对应 st1（减）和 st2（加）。
这就是"找区间内一个 st1 最大值和一个在它右侧的 st2 最大值之和最大"：
第一部分：取 st1 最大的位置 p（用 n1 记录），用 f2(p右侧) 找最大的 st2。
第二部分：反过来 max(st2) + 在它左侧的 max(st1)，同样做一次取 max。
两种方向都算，取最大值即区间最优。

先取所有节点"子树内最长+次长"的最大值 → 这是完全不经过环上两条不同边路径、只在各自子树内的最长路径候选。
建 lg 表（log2 下取整，用于 ST 查询）。
枚举环上长度恰好为 cnt/2（即环长）‍的所有区间 [i-cnt/2+1, i]（滑动窗口），每段代表"环上一整圈的不同起点拆分"，用 solve 求该段的最优值，取所有窗口的最小值给 res。
之所以取 min：每段区间代表去掉环上一条边后变成的路径，我们要保证"环上取的两点之间不跨过同一条边两次"，因此必须限制在去掉一条边后的线状区间内，对所有可能的去边方式取最优（min 保证 max 的是严格合法的）
最终答案是"子树内部直径"与"经过环的最长路径"两者的最大值

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 4e5+5;
struct node { int to, data; };
vector<node> a[N];

bool vis[N], h[N];
int dfs(int x, int fa) {
    vis[x] = 1;
    int len = a[x].size(), num = 0;
    for (int i = 0; i < len; ++i) {
        if (a[x][i].to == fa) continue;
        if (vis[a[x][i].to]) {
            if (!h[a[x][i].to]) h[x] = 1, num = a[x][i].to;
            continue;
        }
        int lim = dfs(a[x][i].to, x);
        if (lim) num = lim;
    }
    if (num) h[x] = 1;
    if (num == x) return 0;
    return num;
}

ll f[N][2];
inline void get(int x, ll y) {
    f[x][1] = max(y, f[x][1]);
    if (f[x][1] > f[x][0]) swap(f[x][1], f[x][0]);
}

void dfs2(int x, int fa) {
    f[x][0] = f[x][1] = 0;
    int len = a[x].size();
    for (int i = 0; i < len; ++i) {
        if (a[x][i].to == fa || h[a[x][i].to]) continue;
        dfs2(a[x][i].to, x);
        get(x, f[a[x][i].to][0] + a[x][i].data);
    }
}

int id[N], cnt;
ll dis[N];
void dfs3(int x, int fa, int num, ll sum) {
    id[++cnt] = x; dis[cnt] = sum;
    int len = a[x].size();
    for (int i = 0; i < len; ++i) {
        if (a[x][i].to == fa || !h[a[x][i].to]) continue;
        if (a[x][i].to == num) {
            for (int j = cnt+1; j <= 2*cnt; ++j)
                id[j] = id[j-cnt], dis[j] = dis[cnt] + a[x][i].data + dis[j-cnt];
            return;
        }
        dfs3(a[x][i].to, x, num, sum + a[x][i].data);
        return;
    }
}

int lg[N];
ll st1[N][21];
inline ll f1(int l, int r) {
    if (l > r) return 0;
    int num = lg[r-l+1];
    return max(st1[l][num], st1[r-(1<<num)+1][num]);
}

ll st2[N][21];
inline ll f2(int l, int r) {
    if (l > r) return 0;
    int num = lg[r-l+1];
    return max(st2[l][num], st2[r-(1<<num)+1][num]);
}

int n1[N][21], n2[N][21];
inline ll solve(int l, int r) {
    int num = lg[r-l+1];
    ll ans = 0;
    if (st1[l][num] > st1[r-(1<<num)+1][num])
        ans = f1(l, r) + f2(n1[l][num]+1, r);
    else ans = f1(l, r) + f2(n1[r-(1<<num)+1][num]+1, r);
    if (st2[l][num] > st2[r-(1<<num)+1][num])
        ans = max(ans, f2(l, r)+f1(l, n2[l][num]-1));
    else ans = max(ans, f2(l, r)+f1(l, n2[r-(1<<num)+1][num]-1));
    return ans;
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y, z; i <= n; ++i) {
        cin >> x >> y >> z;
        a[x].push_back({y, z}); a[y].push_back({x, z});
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)
        if (h[i]) dfs2(i, 0);//对所有环上点做子树 DP
    for (int i = 1; i <= n; ++i)
        if (h[i]) { dfs3(i, 0, i, 0); break; }
    cnt *= 2;//从第一个环点开始展开，最后 cnt 变成两倍环长
    for (int i = 1; i <= cnt; ++i) {
        st1[i][0] = f[id[i]][0] - dis[i], st2[i][0] = f[id[i]][0] + dis[i];
        n1[i][0] = n2[i][0] = i;
    }
    for (int i = 1; i <= 20; ++i) {
        for (int j = 1; j+(1<<i)-1 <= cnt; ++j) {
            if (st1[j][i-1] > st1[j+(1<<(i-1))][i-1])
                st1[j][i] = st1[j][i-1], n1[j][i] = n1[j][i-1];
            else st1[j][i] = st1[j+(1<<(i-1))][i-1], n1[j][i] = n1[j+(1<<(i-1))][i-1];
            if (st2[j][i-1] > st2[j+(1<<(i-1))][i-1])
                st2[j][i] = st2[j][i-1], n2[j][i] = n2[j][i-1];
            else st2[j][i] = st2[j+(1<<(i-1))][i-1], n2[j][i] = n2[j+(1<<(i-1))][i-1];
        }
    }
    ll ans = 0, res = 1e18;
    for (int i = 1; i <= n; ++i) ans = max(ans, f[i][0] + f[i][1]);
    for (int i = 2; i <= cnt; ++i) lg[i] = lg[i>>1] + 1;
    for (int i = cnt/2; i <= cnt; ++i) res = min(res, solve(i-cnt/2+1, i));
    cout << max(ans, res);
    return 0;
}