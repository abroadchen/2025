//
// Created by Psy.C on 2026/4/4.
//
/**
N, M: 节点数和边数的最大值
edge: 链式前向星图的边结构体
head[]: 邻接表头节点数组
add(): 添加边的函数
node: 存储边信息的结构体
dfn[]: DFS访问时间戳
low[]: 能回到的最小时间戳
id: 时间戳计数器
st[]: Tarjan算法栈
top: 栈顶指针
bcc: 双连通分量编号
bel[]: 节点所属双连通分量
in[]: 节点是否在栈中

执行Tarjan算法寻找双连通分量
初始化当前节点的时间戳和栈状态
遍历邻接节点，递归处理未访问节点或更新回边
当发现割点时弹出栈中元素形成一个双连通分量
从起点搜索到终点，判断是否存在满足条件的路径
flag[]: 标记包含权值为1的边的双连通分量
sum: 路径上边权之和
如果到达终点且sum不为0，返回true

时间复杂度：O(n+m)，空间复杂度：O(n+m)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+5, M = 6e5+5;
struct edge { int nxt, to, len; } G[M];
int head[N], num;
void add(int fr, int to, int len) {
    G[++num] = {head[fr], to, len}, head[fr] = num;
}
struct node { int u, v, len; };

int dfn[N], low[N], id, st[N], top, bcc, bel[N];
bool in[N];
void tarjan(int u, int fa) {
    int i;
    dfn[u] = low[u] = ++id; in[u] = true; st[++top] = u;
    for (i = head[u]; i != -1; i = G[i].nxt) {
        int v = G[i].to;
        if (v == fa) continue;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if (in[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++bcc;
        do {
            i = st[top--];
            bel[i] = bcc;
            in[i] = false;
        } while (i != u);
    }
}

int ed;
bool flag[N];
bool dfs(int to, int fa, int sum) {
    if (to == ed) {
        if (sum != 0) return true;
        return false;
    }
    for (int i = head[to]; i != -1; i = G[i].nxt) {
        int v = G[i].to;
        if (v != fa) {
            if (dfs(v, to, sum+G[i].len+flag[v]))
                return true;
        }
    }
    return false;
}

vector<node> vf;
int n, m, stt;
int main() {
    fast;
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 1, x, y, z; i <= m; ++i) {
        cin >> x >> y >> z;
        vf.push_back({x, y, z});
        add(x, y, z); add(y, x, z);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i, 0);//对每个未访问节点运行Tarjan算法
    num = 0; memset(head, -1, sizeof(head));//重建邻接表，只保留不同双连通分量间的边
    for (int i = 0; i < m; ++i) {
        int u = vf[i].u, v = vf[i].v, w = vf[i].len;
        if (bel[u] != bel[v])
            add(bel[u], bel[v], w), add(bel[v], bel[u], w);
        else if (w == 1)
            flag[bel[u]] = true;
    }
    cin >> stt >> ed; stt = bel[stt], ed = bel[ed];//将起点和终点转换为对应的双连通分量编号
    if (flag[stt] || flag[ed]) {
        cout << "YES";
        return 0;
    }
    if (dfs(stt, -1, 0)) cout << "YES";
    else cout << "NO";
    return 0;
}