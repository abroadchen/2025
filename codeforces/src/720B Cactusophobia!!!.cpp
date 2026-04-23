//
// Created by Psy.C on 2026/4/22.
//
/**
邻接表结构：
v: 目标节点
w: 边权值
nxt: 下一条边的索引
cnt = 1: 边编号从1开始，便于位运算

状态标记：
tp[u]: 临时访问标记（用于检测环） 栈上标记
vis[u]: 永久访问标记 标记节点是否被访问过
pos[u]: 到达u的边 到达节点u的边的编号
sum: 环的计数器，记录发现的环数量
pre[u]: u的前驱节点
环检测：
if (tp[v]): 发现后向边，形成环
i>>1: 将边编号转换为边对编号（每条边与其反向边为一对）
pos[u]^1: 获取反向边（奇偶互换）
环收集：
cir[sum]: 存储环中所有边的权值
bel[i>>1]: 标记边属于哪个环

bfs(): 构建层次图
dfs(): 寻找阻塞流
dinic(): 重复上述过程直到无增广路径
权值离散化：
收集所有边权值
排序并去重
用排名替换原始权值

冲突环: 与其他环共享边或已标记为必选
独立环: 不与其他环冲突的简单环
建图策略：
源点到边：容量为该边参与的独立环数量
边到环：每个环最多选择一条边
环到汇点：容量为1
时间复杂度：O(环数量 × 最大流复杂度)，适合稀疏图的情况


n: 节点数
m: 边数
d[M]: 权值数组（用于离散化）
co: 离散化后的权值种类数
col[M]: 临时计数数组
de[M]: 每个权值参与的独立环数
pd[M]: 权值是否必须选择的标记
ve: 独立环的列表

遍历所有边对（i和i+1为一对）
lower_bound: 查找权值在离散化数组中的位置
用排名替换原始权值
对每个未访问的节点执行DFS
找出所有简单环
遍历所有边对
如果边不属于任何环，标记其权值为必须选择
遍历每个环
col[j]++: 统计每个权值在当前环中的出现次数
col[j] != 1: 如果权值在多个环中出现，标记为冲突
pd[j]: 如果权值必须选择，标记为冲突
flag: 如果环有冲突，标记所有涉及的权值为必须选择
否则，累加独立环计数，将环加入独立环列表
清空临时计数数组
为每个参与独立环的权值分配节点编号

now: 独立环节点起始编号
tot: 更新总节点数
s, t: 分配源点和汇点编号
pd[i]: 如果权值必须选择，容量为de[i]
de[i] > 1: 如果权值参与多个环，容量为de[i]-1
d[j], i+now: 从权值节点到环节点，容量为1
i+now, t: 从环节点到汇点，容量为1
co: 总权值种类数
ve.size(): 独立环总数
flow::dinic(): 最大流值（被选择的独立环数）
ve.size()-flow::dinic(): 未被选择的独立环数
最终结果：总权值数减去未选择的独立环数
*/

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 8e5+7, M = 4e5+7, inf = 0x3f3f3f3f;
struct node { int v, w, nxt; } e[N<<1];

int head[M], cnt = 1;
void add(int u, int v, int w) {
    e[++cnt] = {v, w, head[u]}, head[u] = cnt;
}

bool tp[M], vis[N], bel[M];
int pos[N], sum, pre[N];
vector<int> cir[M];
void dfs(int u) {
    tp[u] = 1;//将节点u标记为临时访问状态（正在DFS栈中）
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        //检查边i是否已被分配给某个环 获取到达u的反向边编号
        if (bel[i>>1] || i == (pos[u]^1)) continue;
        int v = e[i].v;//获取当前边的目标节点
        if (tp[v]) {//检查目标节点v是否在当前DFS栈中（发现后向边，形成环）
            ++sum;
            cir[sum].push_back(e[i].w);//将当前边的权值加入新环
            bel[i>>1] = sum;//标记当前边属于第sum个环
            int now = u;//从当前节点u开始回溯
            while (now != v) {//直到回到环的起点v
                cir[sum].push_back(e[pos[now]].w);//将回溯路径上的边权值加入环
                bel[pos[now]>>1] = sum;//标记该边属于当前环
                now = pre[now];// 移动到前驱节点
            }
        }
        //如果目标节点v不在DFS栈中（不是后向边）
        //记录到达v的边 记录v的前驱节点为u 递归访问节点v
        else pos[v] = i, pre[v] = u, dfs(v);
    }
    tp[u] = 0;//从DFS栈中移除u（回溯时清除临时标记）
}

int s, t;
namespace flow {
    //图中节点总数 层次图中节点的距离标号 当前弧优化数组
    int tot, dis[N], cur[N];
    struct edge { int v, f, nxt; } e[N<<1];//目标节点 边的容量 下一条边指针
    void add(int u, int v, int f) {//为最大流网络添加边
        e[++cnt] = {v, f, head[u]}, head[u] = cnt;
    }
    void Add(int u, int v, int f) {
        add(u, v, f); add(v, u, 0);
    }
    int bfs() {
        memset(dis+1, -1, sizeof (int)*(tot));//从dis[1]开始设置
        queue<int> q; dis[s] = 0; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; i; i = e[i].nxt) {
                int v = e[i].v;
                //边是否有剩余容量 节点v是否未被访问
                if (e[i].f > 0 && dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    q.push(v);
                    if (v == t) return 1;//到达汇点，返回成功
                }
            }
        }
        return 0;
    }
    int dfs(int u, int f) {
        //到达汇点，返回流量f 流量用尽，返回0
        if (u == t || f == 0) return f;
        int used = 0;//当前节点实际使用的流量
        for (int& i = cur[u]; i; i = e[i].nxt) {
            //检查是否为层次图中的边
            if (e[i].f > 0 && dis[e[i].v] == dis[u] + 1) {
                int w = dfs(e[i].v, min(f, e[i].f));//递归增广
                if (!w) continue;//如果没有增广成功，继续下一条边
                //累加使用流量 剩余流量减少 正向边容量减少 反向边容量增加
                used += w; f -= w; e[i].f -= w; e[i^1].f += w;
                if (!f) break;//流量用尽，跳出循环
            }
        }
        if (!used) dis[u] = -1;//如果没有使用任何流量，标记节点不可达
        return used;
    }
    int dinic() {
        int f = 0;
        while (bfs()) {
            memcpy(cur, head, sizeof (int)*(tot+1));//恢复当前弧为邻接表头
            f += dfs(s, inf);//累加最大流
        }
        return f;
    }
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
using flow::tot;
using flow::Add;

int n, m, d[M], co, col[M], de[M];
bool pd[M];
vector<int> ve;
int main() {
    fast;
    rd(n), rd(m);
    for (int i = 1, u, v, w; i <= m; ++i) {
        rd(u), rd(v), rd(w);
        add(u, v, w), add(v, u, w);
        d[i] = w;
    }
    sort(d + 1, d + m + 1);
    co = unique(d + 1, d + m + 1) - d - 1;
    for (int i = 2; i <= cnt; i += 2)
        e[i].w = e[i+1].w = lower_bound(d+1, d+co+1, e[i].w) - d;
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
    for (int i = 2; i <= cnt; i += 2)
        if (!bel[i>>1]) pd[e[i].w] = true;
    for (int i = 1; i <= sum; ++i) {
        bool flag = false;
        for (int j : cir[i]) {
            col[j]++;
            if (col[j] != 1 || pd[j]) flag = true;
        }
        if (flag) {
            for (int j : cir[i]) pd[j] = true;
        } else {
            for (int j : cir[i]) de[j]++;
            ve.push_back(i);
        }
        for (int j : cir[i]) col[j]--;
    }
    for (int i = 1; i <= co; ++i) {
        if (!de[i]) continue;
        d[i] = ++tot;
    }
    int now = tot+1; tot += ve.size(); s = ++tot; t = ++tot;
    for (int i = 1; i <= co; ++i) {
        if (!de[i]) continue;
        if (pd[i]) Add(s, d[i], de[i]);//必选边
        else if (de[i] > 1) Add(s, d[i], de[i]-1);//冲突边
    }
    for (int i = 0; i < ve.size(); ++i) {
        int u = ve[i];
        for (int j : cir[u]) Add(d[j], i+now, 1);//边到环的连接
        Add(i+now, t, 1);//环到汇点
    }
    cout << co-(ve.size()-flow::dinic()) << '\n';
    return 0;
}