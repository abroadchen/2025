//
// Created by Psy.C on 2026/9/9.
//
/**
to 为目标点，nxt 为下一条边的下标
扩展欧几里得：解 a*x + b*y = gcd(a,b)，结果存入全局 ax、ay，同时返回 gcd。系数回溯：tx = ay - (b/a)*ax, ty = ax。后续用于求模线性方程和逆元相关计算
记忆化搜索求最长路径（DAG 最长链）‍：
dp[x]：从点 x 出发能获得的最大总权重；w[x]：点 x 自带的权重；g[x]：记录最优点 x 应走向的后继（用于回溯路径）。
若已算过直接返回；否则 dp[x] = w[x] 起步，遍历每条出边，对每个后继 v 递归计算，若 dp[v]+w[x] 更大则更新 dp[x] 并记录 g[x]=v。
相当于树/图上带权最长路径
读入 n、m，以及 n 个被标记（禁止/已存在）的数 vis[x]=1（vis 记录哪些数不可用）。
对每个 i（1 到 m-1）：
跳过被禁止的数（vis[i]）。
k = gcd(i, m)：按 i 与 m 的最大公约数 k 分组——所有 gcd 相同的 i 属于一组。可见这是环/群论分组：在模 m 的乘法或加法环里，gcd 分组代表同阶/同轨道。
f[k].push_back(i)：把 i 放进组 k 的元素列表。
++w[k]：组 k 的权重 +1（该组多了一个可用元素）。
若组 k 还没建过节点（!s[k]）：标记 s[k]=1 表示该组已作为图节点，然后为 k 所有的倍数 j=2k,3k,... 建边 add(k,j)（倍数关系构成 DAG/偏序），同时 deg[j]++ 记录入度
拓扑序：把所有入度为 0 的组节点（s[i] 存在且 !deg[i]）入队。
BFS/队列逐个处理：对每个起点节点跑 dfs(u) 求最长路；若该路径权重 dp[u] 更大就更新 ans 和起点 id。最终找到权值最大的最长链的起点
从最优起点 id 沿 g[] 后继链一路走到底，把每组的元素列表 f[i] 全部展开存入 a[]（即实际输出的数序列）。若 0 未被禁止，再把 0 加入末尾
先输出元素个数 top，若为 0 直接退出。
逐个输出元素，元素之间用空格隔开，遇到 0 时换行（0 作为分隔/结尾）。
对于非 0 元素 a[i]，计算从上一步 a[i-1] 走到 a[i] 的增量：
exgcd(a[i-1], m) 求 a[i-1] 在模 m 下的逆元相关（返回 gcd k，并给出系数 ax）。
dx = m/k（周期），tp = a[i]/k。
把 ax 规范化到 [0, dx)，再乘以 tp，得到从 a[i-1] 到 a[i] 应该走的步数 ax%m。输出这个增量作为"上一步到这一步的距离"。
这是将每个数序列转换为相邻数之间的位移量（用 exgcd 解同余方程）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5+5;

struct Edge { int to, nxt; } e[N*16];
int gcd(int a, int b) {
    return a == 0 ? b : gcd(b%a, a);
}

int ax, ay;
int exgcd(int a, int b) {
    if (a == 0) { ax = 0, ay = 1; return b; }
    int k = exgcd(b%a, a), tx = ay - (b/a)*ax, ty = ax;
    ax = tx, ay = ty;
    return k;
}

int cnt, head[N];
void add(int x, int y) {
    e[++cnt] = {.to = y, .nxt = head[x]}, head[x] = cnt;
}

queue<int> q;
int dp[N], w[N], g[N];
void dfs(int x) {
    if (dp[x]) return;
    dp[x] = w[x];
    for (int i = head[x]; i; i = e[i].nxt) {
        int v = e[i].to; dfs(v);
        if (dp[x] < dp[v] + w[x])
            dp[x] = dp[v] + w[x], g[x] = v;
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, vis[N], s[N], deg[N], a[N], top;
vector<int> f[N];
signed main() {
    fast;
    n = rd(), m = rd();
    for (int i = 1, x; i <= n; ++i) {
        x = rd(); vis[x] = 1;
    }
    for (int i = 1; i < m; ++i) {
        if (vis[i]) continue;
        int k = gcd(i, m);
        f[k].push_back(i), ++w[k];
        if (s[k]) continue;
        s[k] = 1;
        for (int j = 2*k; j < m; j += k)
            add(k, j), ++deg[j];
    }
    for (int i = 1; i < m; ++i)
        if (s[i] && !deg[i]) q.push(i);
    int id = 0, ans = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        dfs(u);
        if (ans < u) ans = dp[u], id = u;
    }
    for (int i = id; i; i = g[i])
        for (int j : f[i])
            a[++top] = j;
    if (!vis[0]) a[++top] = 0;
    cout << top << '\n';
    if (top == 0) exit(0);
    cout << a[1] << ' ';
    for (int i = 2; i <= top; ++i) {
        if (a[i] == 0) cout << a[i] << '\n';
        else {
            int k = exgcd(a[i-1], m), dx = m/k, tp = a[i]/k;
            while (ax < 0) ax += dx;
            ax %= dx;
            ax = ax*tp;
            cout << ax%m << ' ';
        }
    }
    return 0;
}