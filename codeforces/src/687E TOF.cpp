//
// Created by Psy.C on 2026/4/15.
//
/**
head：邻接表头指针数组
tot：边的编号计数器（从1开始）
to, nxt：边的目标节点和下一个边的索引
add函数：添加有向边a→b
dfn：节点的DFS序（发现时间）
low：节点能到达的最小DFS序
tim：时间戳计数器
st, top：栈和栈顶指针
scc：强连通分量数量
bel：节点所属的强连通分量编号
in：节点是否在栈中
ve：每个强连通分量包含的节点列表

初始化：设置当前节点的dfn和low值
入栈：将当前节点压入栈中
遍历邻居：
如果邻居未访问，递归tarjan，更新low值
如果邻居在栈中，更新low值
强连通分量识别：当dfn[now] == low[now]时，弹出栈中元素组成SCC
BFS初始化：将同SCC内的节点距离设为无穷，起点距离为0
BFS搜索：在当前SCC内进行广度优先搜索
回路查找：寻找回到起点x的最短路径


输入：读取节点数n和边数m
建图：添加所有有向边
运行Tarjan：对所有未访问的节点运行Tarjan算法
初始化答案：ans=n（基础分数）
遍历每个SCC：
计算跨SCC的边数
如果有跨SCC边，跳过（不是纯SCC）
如果SCC只有一个节点，跳过
在SCC内找最短回路
更新答案

Tarjan算法：找出所有的强连通分量
内部最短路：在每个纯SCC内寻找最短回路
评分规则：每个包含环的SCC贡献 最短环长度*998+1 的分数
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5005, inf = 1e9;

int head[N], tot=1, to[N], nxt[N];
void add(int a, int b) {
    tot++;
    to[tot] = b; nxt[tot] = head[a]; head[a] = tot;
}

int dfn[N], low[N], tim, st[N], top, scc, bel[N];
bool in[N];
vector<int> ve[N];
void tarjan(int now) {
    dfn[now] = low[now] = ++tim;
    in[now] = 1; st[++top] = now;
    for (int i = head[now]; i; i = nxt[i]) {
        if (!dfn[to[i]])
            tarjan(to[i]), low[now] = min(low[now], low[to[i]]);
        else
            if (in[to[i]])
                low[now] = min(low[now], dfn[to[i]]);
    }
    if (dfn[now] == low[now]) {
        scc++;
        while (true) {
            int y = st[top]; top--; in[y] = 0;
            ve[scc].push_back(y);
            bel[y] = scc;
            if (y == now) break;
        }
    }
}

int dis[N];
int get(int x) {
    for (int i : ve[bel[x]]) dis[i] = inf; dis[x] = 0;
    queue<int> q; q.push(x);
    while (!q.empty()) {
        int now = q.front(); q.pop();
        for (int i = head[now]; i; i = nxt[i])
            if (bel[to[i]] == bel[x] && dis[to[i]] > dis[now] + 1)
                dis[to[i]] = dis[now] + 1, q.push(to[i]);
    }
    int ans = inf;
    for (int now : ve[bel[x]])
        for (int i = head[now]; i; i = nxt[i])
            if (to[i] == x)
                ans = min(ans, dis[now] + 1);
    return ans;
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

template<typename T,typename... Args>
void rd(T& t,Args&... args) {
    rd(t); rd(args...);
}

int n, m;
int main() {
    rd(n, m);
    for (int i = 1, x, y; i <= m; ++i) {
        rd(x, y); add(x, y);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i);
    int ans = n;
    for (int i = 1; i <= scc; ++i) {
        int num = 0;
        for (int now : ve[i])
            for (int j = head[now]; j; j = nxt[j])
                if (bel[to[j]] != i) num++;
        if (num) continue;
        if (ve[i].size() == 1) continue;
        int sum = inf;
        for (int j : ve[i]) sum = min(sum, get(j));
        ans += sum*998 + 1;
    }
    printf("%d\n", ans);
    return 0;
}