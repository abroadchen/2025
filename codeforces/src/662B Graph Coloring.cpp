//
// Created by Psy.C on 2026/4/11.
//
/**
v（终点），nxt（下一条边），c（颜色标志） 0表示红色，1表示蓝色
head[N]存储邻接表的头指针
tot跟踪添加的总边数

执行基于BFS的着色，带约束检查
x是期望的颜色模式（0或1）
op是当前组件的起始颜色（0或1）
检查当前边颜色是否匹配期望模式（e[i].c^col[u]^col[v]）
f[op]标志在此着色尝试中是否发生矛盾
使用异或操作更新颜色：col[v] = e[i].c^col[u]^x

处理每个连通组件，尝试两种着色（0和1）
如果两种着色都失败（f[0] && f[1]），设置flag[x] = 1
否则选择更好的着色（较小的组或成功的那个）
在ans[x]中构建解决方案

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
struct node { int v, nxt, c; } e[N<<1];
int head[N], tot;
void add(int a, int b, int c) {
    e[tot] = {b, head[a], c}, head[a] = tot++;
}
int vis[N], col[N], f[2];
vector<int> tmp[2];
void dfs(int x, int u, int op) {
    vis[u] = 1; col[u] = op;
    queue<int> q; q.push(u);
    vector<int> vv;
    while (!q.empty()) {
        u = q.front(); q.pop(); vv.push_back(u);
        if (col[u]) tmp[op].push_back(u);
        for (int i = head[u]; i != -1; i = e[i].nxt) {
            int v = e[i].v;
            if (vis[v] && e[i].c^col[u]^col[v] != x) {
                f[op] = 1;
                break;
            }
            if (!vis[v]) {
                col[v] = e[i].c^col[u]^x;
                vis[v] = 1;
                q.push(v);
            }
        }
        if (f[op]) break;
    }
    if (op == 0)
        for (int i : vv) vis[i] = 0;
}

int n, flag[2];
vector<int> ans[2];
void out(int x) {
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            tmp[0].clear(); tmp[1].clear();
            f[0] = f[1] = 0;
            dfs(x, i, 0); dfs(x, i, 1);
            if (f[0] && f[1]) {
                flag[x] = 1;
                return;
            }
            int k;
            if (f[0]) k = 1;
            else if (f[1]) k = 0;
            else if (tmp[0].size() < tmp[1].size()) k = 0;
            else k = 1;
            for (int j : tmp[k]) ans[x].push_back(j);
        }
    }
}

void init() {
    memset(head, -1, sizeof(head));
    ans[0].clear(); ans[1].clear();
    flag[0] = flag[1] = 0;
    tot = 0;
}

int m;
int main() {
    fast;
    cin >> n >> m; init();
    for (int i = 0, a, b; i < m; ++i) {
        char c[10];
        cin >> a >> b >> c;
        add(a, b, c[0]=='R' ? 0 : 1);
        add(b, a, c[0]=='R' ? 0 : 1);
    }
    out(0); out(1);
    if (flag[0] && flag[1]) cout << -1 << '\n';
    else {
        int k;
        if (flag[0]) k = 1;
        else if (flag[1]) k = 0;
        else if (ans[0].size() < ans[1].size()) k = 0;
        else k = 1;
        cout << ans[k].size() << '\n';
        for (int i = 0; i < ans[k].size(); ++i) {
            cout << ans[k][i];
            if (i == ans[k].size()-1) cout << '\n';
            else cout << ' ';
        }
    }
    return 0;
}