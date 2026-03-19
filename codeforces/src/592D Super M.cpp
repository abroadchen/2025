//
// Created by Psy.C on 2026/3/19.
//
/**
cnt：边的计数器
v[N]：存储边的目标节点
head[N]：存储每个节点的第一条边的索引
nxt[N]：存储同一起点的下一条边
v[++cnt] = y：记录边的目标节点
nxt[cnt] = head[x]：链接到之前的边
head[x] = cnt：更新x节点的第一条边
b[N] 标记数组，表示节点是否为关键节点
x：当前节点，p：父节点
for (int i = head[x]; i; i = nxt[i])：遍历x的所有邻居
if (v[i]^p)：如果邻居不是父节点（防止回溯）
dfs(v[i], x)：递归访问子节点
b[x] |= b[v[i]];：如果子节点包含关键节点，则当前节点也标记为包含关键节点
a[N] 距离数组，记录从起点到各节点的距离
x：当前节点，y：当前距离，p：父节点
a[x] = y;：记录当前节点的距离
if (b[v[i]] && v[i]^p)：只有当邻居节点包含关键节点且不是父节点时才继续
dfs(v[i], y + 1, x);：递归访问，距离加1

n：节点数
m：关键节点数
b[y=rd()] = 1：读取第一个关键节点，标记为关键节点，赋值给y
for (i = 1; i < m; ++i) b[rd()] = 1;：读取剩余的关键节点并标记
dfs(y, 0)：从第一个关键节点开始DFS，标记包含关键节点的路径
a[0] = cnt = -1：初始化特殊值
cnt += b[i];：统计关键节点总数
dfs(y, x=0, 0)：从关键节点y开始，计算距离
找到距离最大的关键节点x
dfs(x, y=0, 0)：从节点x开始重新计算距离
找到距离x最远的关键节点y
x<y?x:y：输出较小的节点编号（可能是直径的一个端点）
cnt+cnt-a[y]：输出结果（可能是树的某种度量，如直径相关）
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2.5e5;
int cnt, v[N], head[N], nxt[N];
void add(int x, int y) {
    v[++cnt] = y, nxt[cnt] = head[x], head[x] = cnt;
}

bool b[N];
void dfs(int x, int p) {
    for (int i = head[x]; i; i = nxt[i])
        if (v[i]^p)
            dfs(v[i], x), b[x] |= b[v[i]];
}
int a[N];
void dfs(int x, int y, int p) {
    a[x] = y;
    for (int i = head[x]; i; i = nxt[i])
        if (b[v[i]] && v[i]^p)
            dfs(v[i], y + 1, x);
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, x, y, i;
int main() {
    n = rd(), m = rd();
    for (i = 1; i < n; ++i) {
        x = rd(), y = rd(); add(x, y); add(y, x);
    }
    for (i = b[y=rd()] = 1; i < m; ++i) b[rd()] = 1;
    for (dfs(y, 0), a[0] = cnt = -1, i = 1; i <= n; ++i) cnt += b[i];
    for (dfs(y, x=0, 0), i = 1; i <= n; ++i)
        if (b[i] && a[x] < a[i]) x = i;
    for (dfs(x, y=0, 0), i = 1; i <= n; ++i)
        if (b[i] && a[y] < a[i]) y = i;
    printf("%d\n%d\n", x<y?x:y, cnt+cnt-a[y]);
    return 0;
}