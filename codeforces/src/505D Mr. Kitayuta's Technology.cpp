//
// Created by Psy.C on 2026/2/25.
//
/**
dfn[N]：节点的DFS访问时间戳
low[N]：节点能够追溯到的最早时间戳
tp：时间戳计数器
vis[N]：节点访问状态（0未访问，1在栈中，2已处理）
cnt：强连通分量计数器
siz[N]：每个SCC的大小
scc[N]：节点所属的SCC编号

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+1;

int dfn[N], low[N], tp=0, vis[N], cnt, siz[N], scc[N];
stack<int> st;//存储当前路径上的节点
vector<int> g[N];//图的边关系
void tarjan(const int now) {//求强连通分量
    dfn[now] = low[now] = ++tp;
    st.push(now);
    vis[now] = 1;
    for (const int i : g[now]) {
        if (dfn[i] == 0) {//未访问过
            tarjan(i);//递归处理并更新low值
            low[now] = min(low[now], low[i]);
        } else if (vis[i] == 1)//在栈中，说明是回边，更新low值
            low[now] = min(low[now], dfn[i]);
    }
    if (dfn[now] == low[now]) {//发现SCC
        cnt++;//创建新的SCC编号
        int top;
        do {
            top = st.top(); st.pop();
            vis[top] = 0;//更新相关数组
            siz[cnt]++;
            scc[top] = cnt;
        } while (top != now);//弹出栈中属于同一SCC的所有节点
    }
}

int fa[N];
int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int n, m, r[N];
int main() {
    fast;
    cin >> n >> m;
    while (m--) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
    }
    for (int i = 1; i <= n; ++i) if (dfn[i] == 0) tarjan(i);//对所有未访问的节点
    int ans = n;//最坏情况每个节点都需要单独处理
    for (int i = 1; i <= cnt; ++i) {
        fa[i] = i;
        r[i] = siz[i]>1;//记录每个SCC是否包含环
    }
    for (int i = 1; i <= n; ++i)
        for (const int j : g[i]) if (scc[i] != scc[j]) {//两个节点属于不同SCC
            if (int a = find(scc[i]), b = find(scc[j]); a != b) {
                fa[a] = b;
                r[b] |= r[a];//任意一个有环，则合并后也有环
            }
        }
    for (int i = 1; i <= cnt; ++i)
        if (fa[i] == i && r[i] == 0) ans--;//可以合并处理，答案减1
    cout << ans << '\n';
    return 0;
}