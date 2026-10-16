//
// Created by Psy.C on 2026/10/16.
//
/**
w[i]：节点 i 的权值。
fa[i][j]：i 向上跳 2^j 步的祖先（倍增表）。
sum[i][j]：从 i 出发，沿祖先链向上，经过第 0-2^j-1 级祖先的权值累加和（终点是 fa[i][j]）
插入规则（这是关键技巧）：

新节点权值 val。
若 val ≤ w[u]，直接把新节点挂在 u 下（父亲 = u）。
否则，从 u 沿倍增表向上，找到最后一个权值 < val 的祖先 u，然后新节点的父亲设为 fa[u][0]（即那个祖先的父节点）。
这样构造出的树满足：沿着从根往下的路径，节点权值非严格递增（每个节点的权值 ≥ 其祖先权值的某个约束）‍。这保证了后续"沿祖先向上累加"时权值满足可累加性
sum[cnt][0] = 父亲节点的权值（若父亲为 0 即不存在，则设 inf 防止误跳）。
对每个 i，倍增拼接：
fa[cnt][i] = 向上跳 2^i 步的祖先。
sum[cnt][i] = sum[cnt][i-1]（先跳 2^{i-1} 步的累加和）+ sum[fa[cnt][i-1]][i-1]（再跳 2^{i-1} 步的累加和）。
于是 sum[u][i] 表示从 u 向上走 2^i 级祖先过程中经过节点的权值总和（不包括 u 自己，包含到达的祖先节点）
若 w[u] > val，预算不足走到 u，返回 0。
否则消耗 w[u]，至少能包括 u（ans=1）。
从高位到低位倍增跳：只要当前预算 ≥ sum[u][i]（走 2^i 级祖先的费用），就走上去，累加步数与费用。
最终返回最多能包括的节点数（含 u 和能到达的若干祖先）。
sum[u][i] 设计为"向上走 2^i 级祖先的花费"，配合从高位枚举贪心，得到预算内能走到的最多祖先层数（节点数）
初始化：节点 0 权值 inf（作为根的虚拟祖先，用于拦停），节点 1 为根（权值 0），cnt=1。
sum[1] 全设无穷大，避免从根继续向上跳。
每组操作先 XOR 解密：a ^= lst、b ^= lst（lst 是上一次查询的答案，实现强制在线，防止离线预处理）。
op==1：插入节点（a 为父亲编号，b 为权值）。
op==2：查询——从节点 a 出发、预算 b，输出最多可走节点数，并用它更新 lst
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
#define ll long long
using namespace std;

constexpr int N = 4e5+5;
constexpr ll inf = 1e18;

ll w[N], sum[N][25];
int cnt, fa[N][25];
void add(int u, int val) {
    w[++cnt] = val;
    if (w[cnt] <= w[u]) fa[cnt][0] = u;
    else {
        per(i,20,0) if (w[fa[u][i]] < w[cnt]) u = fa[u][i];
        fa[cnt][0] = fa[u][0];
    }
    if (fa[cnt][0] == 0) sum[cnt][0] = inf;
    else sum[cnt][0] = w[fa[cnt][0]];
    rep(i,1,20) {
        fa[cnt][i] = fa[fa[cnt][i-1]][i-1];
        if (fa[cnt][i] == 0) sum[cnt][i] = inf;
        else sum[cnt][i] = sum[cnt][i-1] + sum[fa[cnt][i-1]][i-1];
    }
}

ll query(int u, ll val) {
    if (w[u] > val) return 0;
    val -= w[u];
    ll ans = 1;
    per(i,20,0) if (val >= sum[u][i]) {
        val -= sum[u][i];
        ans += 1<<i;
        u = fa[u][i];
    }
    return ans;
}

ll lst, a, b;
int q, op;
int main() {
    fast;
    w[0] = inf; w[1] = 0; lst = 0; cnt = 1;
    memset(sum[1], 0x3f, sizeof(sum[1]));
    cin >> q;
    while (q--) {
        cin >> op >> a >> b;
        a ^= lst; b ^= lst;
        if (op == 1) add(a, b);
        else cout << (lst=query(a,b)) << '\n';
    }
    return 0;
}