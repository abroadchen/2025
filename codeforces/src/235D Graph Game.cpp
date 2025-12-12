//
// Created by Psy.C on 2025/12/12.
//
/*
*to[]：存储边的目标节点
head[]：每个节点的第一条边的索引
nxt[]：下一条边的索引（构成链表）
cnt：边的计数器
add()函数：向无向图中添加一条边(u,v)
 *
*flag：标记是否已经找到环
vis[]：记录节点是否被访问过
st[]：DFS路径栈
top：栈顶指针
t[]：标记环上的节点
len：环的长度
这个DFS函数用于在图中寻找唯一的环，并标记环上的所有节点
*如果已找到环则返回
标记当前节点为已访问并压入栈
遍历当前节点的所有邻接点
跳过父节点避免回溯
如果邻接点已被访问，说明找到了环
从栈中提取环上的所有节点并标记
如果未找到环，则继续深度优先搜索
回溯时弹出栈顶元素
 *
*ans：最终答案
get()函数根据节点位置计算对答案的贡献
y：距离参数
z：环上位置参数
根据节点是否在环上以及位置不同采用不同的计算公式
 *
*lst[]：记录节点在哪一轮DFS中被访问
num：DFS轮数计数器
从每个节点开始DFS遍历整棵树
y：距离起始节点的距离
z：在环上的累积位置
t[to[j]]：如果邻接点在环上则加1，否则加0
 *
*加速IO操作
读入节点数n
读入n条边，构建无向图（节点编号加1避免0号节点的问题）
第一次DFS找到图中的唯一环
对每个节点进行一次DFS，计算该节点对总答案的贡献
输出结果，保留12位小数
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 6005
using namespace std;

int to[N], head[N], nxt[N], cnt;
void add(const int u, const int v) {
    to[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}

bool flag;
int vis[N], st[N], top, t[N], len;
void dfs(const int i, const int pre) {
    if (flag) return;
    vis[i] = 1; st[++top] = i;
    for (int j = head[i]; j; j = nxt[j]) {
        if (to[j] == pre) continue;
        if (flag) return;
        if (vis[to[j]]) {
            for (; st[top] != to[j]; --top) t[st[top]] = 1, len++;
            t[st[top]] = 1; len++; flag = true;
            return;
        }
        dfs(to[j], i);
    }
    top--;
}

double ans;
void get(const double y, const double z) {
    if (z <= 1) ans += 1 / y;
    else {
        const double x = y - z + len;
        ans -= 1 / x;
        if (z >= 2) ans += 1 / (x - (z - 2));
        if (z <= len) ans += 1 / (x - (len - z));
    }
}


int lst[N], num;
void dfs(const int i, const int y, const int z) {
    lst[i] = num; get(y, z);
    for (int j = head[i]; j; j = nxt[j]) if (lst[to[j]] != num) {
        dfs(to[j], y + 1, z + t[to[j]]);
    }
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, u, v; i <= n; ++i) {
        cin >> u >> v; u++; v++;
        add(u, v); add(v, u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) { num++; dfs(i, 1, t[i]); }
    cout << fixed << setprecision(12) << ans << '\n';
    return 0;
}