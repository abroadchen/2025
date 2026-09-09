//
// Created by Psy.C on 2026/9/8.
//
/**
add 把边插入 fr 的邻接链表头（.to, .nxt 是指定初始化器）
点分治第一步：找当前子树(连通块)的重心。
sz[now]：以 now 为根的子树的节点数。递归收集。
mx[now]：删除 now 后，剩余各部分（子树 + 上方部分 stot - sz[now]）中最大的那块大小。
遍历后，选 mx 最小（且编号最小，rt=min(rt,now) 处理并列）的节点作为重心 rt，其最大块大小 rz
calc 深度优先遍历某棵"未删除"子树，计算每个点到根(当前重心)的距离 dep。
cb[dep%m]++：按 距离 mod m 统计该子树内节点数（cb 是"当前子树"的计数桶）。
distot += dep[now]：累加该子树内所有点到当前重心的深度总和
div(now)：对以 now 为重心的连通块进行点分治。
bc[m]："已处理子树累积"的 mod m 计数桶，初始 bc[0]=1（把重心自身这一个点算进去，距离 0）。
ts：已处理子树的深度总和累积值。vis[now]=true：标记重心已删除（分治后会拆开各子树）
遍历重心的每个邻居（每条子树），对每个子树：
重新清空 cb、distot，置 dep[to]=1，调用 calc 统计该子树内各点到重心的距离分布及深度和
跨子树路径配对：一条"经过 now 重心"的路径，一侧在当前子树里（距离 mod m = k），另一侧在"之前已处理的子树或重心本身"里（距离 mod m = j），这条路径总长 (j+k) mod m。
ans[(j+k)%m] += bc[j]*cb[k]：把这种距离 mod m 的路径条数累加到 ans
更新 bc：把当前子树的 cb 并入 bc（之后可作为"已处理侧"）。
tcnt=处理完并入前 bc 的总点数，cnt=当前子树点数。
sum += ts*cnt + distot*tcnt：统计经过重心、一侧在本子树、另一侧在已处理集合/重心的全部路径的深度和（距离和）：
ts*cnt：已处理侧每个点(深度用 ts 表示的和)与当前子树每个点配对产生的距离贡献；
distot*tcnt：反过来，当前子树的深度和 × 已处理侧点数。
ts += distot：把当前子树深度和并入 ts。
（这两组更新是等价的路径统计，ans[] 管"mod m 类别的条数"，sum 管"实际距离之和"。）
递归分治：删除重心 now 后，对其每个未访问的子树 to，用 calc_g 重新找出该子树重心 rt，再对 rt 递归 div，直到所有点都被处理。stot = sz[to] 用作该子树当前总大小

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+5, M = 4e5+5;
struct Edge { int to, nxt; } e[M];

int tot, head[N];
void add(int fr, int to) {
    e[++tot] = {.to = to, .nxt = head[fr]}; head[fr] = tot;
}

int sz[N], mx[N], stot, rt, rz;
bool vis[N];
void calc_g(int now, int fa) {
    sz[now] = mx[now] = 1;
    for (int to, i = head[now]; i; i = e[i].nxt) {
        to = e[i].to;
        if (vis[to] || to == fa) continue;
        calc_g(to, now);
        sz[now] += sz[to], mx[now] = max(mx[now], sz[to]);
    }
    mx[now] = max(mx[now], stot - sz[now]);
    if (!rt || rz > mx[now]) rt = now, rz = mx[now];
    else if (rz == mx[now]) rt = min(rt, now);
}

ll distot, cb[10];
int dep[N], m;
void calc(int now, int fa) {
    cb[dep[now]%m]++; distot += dep[now];
    for (int to, i = head[now]; i; i = e[i].nxt) {
        to = e[i].to;
        if (vis[to] || to == fa) continue;
        dep[to] = dep[now] + 1;
        calc(to, now);
    }
}

ll bc[10], ts, sum, ans[10];
void div(int now) {
    memset(bc, 0, sizeof bc); bc[0] = 1; ts = 0, vis[now] = true;
    for (int to, tcnt, cnt, i = head[now]; i; i = e[i].nxt) {
        to = e[i].to;
        if (vis[to]) continue;
        memset(cb, 0, sizeof cb); distot = 0, dep[to] = 1; calc(to, now);
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < m; ++k)
                ans[(j+k)%m] += 1ll*bc[j]*cb[k];
        cnt = tcnt = 0;
        for (int j = 0; j < m; ++j)
            tcnt += bc[j], bc[j] += cb[j], cnt += cb[j];
        sum += 1ll*ts*cnt + 1ll*distot*tcnt;
        ts += distot;
    }
    for (int to, i = head[now]; i; i = e[i].nxt) {
        to = e[i].to;
        if (vis[to]) continue;
        stot = sz[to], rt = rz = 0;
        calc_g(to, 0); calc_g(rt, 0); div(rt);
    }
}

int n;
int main() {
    fast;
    cin >> n >> m;
    for (int u, v, i = 1; i < n; ++i)
        cin >> u >> v, add(u, v), add(v, u);
    stot = n;
    calc_g(1, 0); calc_g(rt, 0); div(rt);
    for (int i = 1; i < m; ++i)
        sum += 1ll*ans[i]*(m-i);
    cout << sum/m;
    return 0;
}