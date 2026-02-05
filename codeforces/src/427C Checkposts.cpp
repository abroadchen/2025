//
// Created by Psy.C on 2026/2/5.
//
/**
*vis[N]：访问标记数组
dfn[N]：DFS序数组
low[N]：能回溯到的最小DFS序
tp：时间戳计数器
tot：强连通分量计数器
scc[N]：节点所属强连通分量编号
*mn[N]：每个强连通分量的最小权值
val[N]：节点权值
cnt[N]：每个强连通分量中最小权值节点的数量
 *
*vis[now] = 1：标记节点now为正在访问
st.push(now)：将节点now压入栈
dfn[now] = low[now] = ++tp：设置DFS序和low值
*遍历节点now的所有邻接点
if (dfn[i] == 0)：如果邻接点未访问，递归访问
low[now] = min(low[now], low[i])：更新low值
else if (vis[i])：如果邻接点在栈中，更新low值
 *
*
if (low[now] == dfn[now])：找到强连通分量
tot++：增加强连通分量计数
mn[tot] = inf：初始化最小值为无穷大
while (st.top() != now)：弹出栈中元素直到now
vis[x] = 0：标记为不在栈中
scc[x] = tot：设置节点所属强连通分量
统计最小权值和最小权值节点数量
 *
*读取节点数n
读取每个节点的权值
读取边数m
读取边并构建邻接表
 *对未访问的节点运行Tarjan算法
*a：所有强连通分量最小权值的和
b：每个强连通分量中最小权值节点数量的乘积
 *
*时间复杂度：O(n+m)，Tarjan算法的线性时间复杂度
空间复杂度：O(n)，用于存储图和辅助数组
 */
#include <iostream>
#include <stack>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 300010
#define mod 1000000007
using namespace std;
constexpr ll inf = 1e18;

int vis[N], dfn[N], low[N], tp, tot, scc[N];
stack<int> st;
vector<int> g[N];
ll mn[N], val[N], cnt[N];
void tarjan(const int now) {
    vis[now] = 1; st.push(now); dfn[now] = low[now] = ++tp;
    for (const int i : g[now]) {
        if (dfn[i] == 0) {
            tarjan(i);
            low[now] = min(low[now], low[i]);
        } else if (vis[i]) {
            low[now] = min(low[now], low[i]);
        }
    }
    if (low[now] == dfn[now]) {
        tot++;
        mn[tot] = inf;
        while (st.top() != now) {
            const int x = st.top(); st.pop();
            vis[x] = 0; scc[x] = tot;
            if (val[x] == mn[tot]) cnt[tot]++;
            else if (val[x] < mn[tot]) {
                cnt[tot] = 1;
                mn[tot] = val[x];
            }
        }
        st.pop(); vis[now] = 0; scc[now] = tot;
        if (val[now] == mn[tot]) cnt[tot]++;
        else if (val[now] < mn[tot]) {
            cnt[tot] = 1;
            mn[tot] = val[now];
        }
    }
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> val[i];
    int m; cin >> m;
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b; g[a].push_back(b);
    }
    for (int i = 1; i <= n; ++i) if (dfn[i] == 0) tarjan(i);
    ll a = 0, b = 1;
    for (int i = 1; i <= tot; ++i) {
        a += mn[i];
        b = cnt[i] * b % mod;
    }
    cout << a << ' ' << b << '\n';
    return 0;
}