//
// Created by Psy.C on 2026/2/5.
//

// g[i]: 节点i的目标状态
// s[i]: 节点i的当前状态
// d[i]: 标记节点i是否被翻转过
// a[i]: 记录节点i的父亲节点
// res: 翻转次数统计
// ans[]: 存储需要翻转的节点序列
// cnt: 记录ans数组的大小
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;

//邻接表边结构：nxt指向下一个边，to指向目标节点
struct node { int nxt, to; } r[N<<1];

//idx是边的索引，head[i]是节点i的第一条边的索引
int idx, head[N];
void add(const int a, const int b) {
    r[idx].to = b, r[idx].nxt = head[a], head[a] = idx++;
}

int g[N], s[N], d[N], a[N], res, ans[N], cnt;
void dfs(const int u, const int fa) {
    if (g[u] != s[u]) {//当前状态不等于目标状态
        //父节点没有被翻转过
        //翻转次数+1 记录当前节点需要翻转
        if (!d[a[u]]) res++, ans[++cnt] = u;
        d[u] = 1;//标记当前节点被翻转
        s[u] ^= 1;//翻转当前节点状态
    }
    //当前状态等于目标状态，但父节点被翻转了
    //需要翻转抵消影响 记录需要翻转的节点
    else if (d[a[u]]) res++, ans[++cnt] = u;
    for (int i = head[u]; ~i; i = r[i].nxt) {
        const int v = r[i].to;
        if (v == fa) continue;
        a[v] = fa;//设置v的父亲为u
        dfs(v, u);//递归处理子节点
    }
    d[u] = 0;//回溯时取消当前节点的翻转标记
}

int main() {
    fast;
    int n; cin >> n;
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    for (int i = 1; i <= n; ++i) cin >> s[i];//初始状态
    for (int i = 1; i <= n; ++i) cin >> g[i];
    dfs(1, 0);
    cout << res << '\n';
    for (int i = 1; i <= cnt; ++i) cout << ans[i] << '\n';
    return 0;
}