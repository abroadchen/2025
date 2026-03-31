//
// Created by Psy.C on 2026/4/1.
//
/**
边结构体，包含目标节点和下一个邻接边的索引
ent：边计数器
ex[], ey[]：边的起点和终点
qnt：链式前向星边计数
head[]：链式前向星的头指针
向图中添加从x到y的边
如果inc为true，同时记录边的起终点到ex[], ey[]
使用链式前向星存储图
dfn[]：DFS访问时间戳
low[]：能够回溯到的最小时间戳
tim：时间戳计数器
st[]：栈
tp：栈顶指针
bel[]：节点所属强连通分量编号
bnt：强连通分量数量
in[]：节点是否在栈中

实现Tarjan算法找强连通分量
记录访问时间戳和能回溯到的最早节点
当发现强连通分量时，出栈直到根节点

符号函数，返回绝对值
n：变量数量
p：约束条件数量
fv[][]：第一组约束条件
sv[][]：第二组约束条件
deg[]：入度数组
Q：查询数量
sel[]：选择标记
a[][]：可达性矩阵
q：队列

重置所有全局变量
初始化数据结构
构建2-SAT图
如果变量为负，则映射到对应的反变量（+n）
添加约束条件的反向边
运行Tarjan算法找到所有强连通分量
检查是否有矛盾：如果变量i和其反变量i+n在同一强连通分量，则无解
建立缩点后的DAG（有向无环图）
统计每个强连通分量的入度

初始化可达性数组
拓扑排序，传递可达性关系
处理查询
检查约束条件是否满足
找到满足条件的解并输出
读入数据
尝试解决第一个问题
如果失败则交换两组数据再尝试
如果都失败输出"SIMILAR"

fp: 第一个变量所在的强连通分量编号
sp: 第二个变量所在的强连通分量编号
fo: 第一个变量的正向映射（用于可达性检查）
so: 第二个变量的正向映射
a[fp][0][so]: 从第一个变量的正向（0）能否到达第二个变量的反向（so）
a[fp][1][so]: 从第一个变量的反向（1）能否到达第二个变量的反向（so）
a[sp][0][fo]: 从第二个变量的正向（0）能否到达第一个变量的反向（fo）
a[sp][1][fo]: 从第二个变量的反向（1）能否到达第一个变量的反向（fo）

a[fp][0]|a[sp][0]: 合并第一个变量和第二个变量的正向可达集合
a[fp][1]|a[sp][1]: 合并第一个变量和第二个变量的反向可达集合
&: 求两个集合的交集
.any(): 检查交集中是否有任何元素

第一种情况: if (a[fp][0][j] || a[fp][1][j])

如果变量j可以从第一个变量的任一方向（正或反）到达
设置 sel[j] = true（表示选择变量j的正向）
第二种情况: else if (a[fp][1][j] || a[sp][1][j])

如果变量j可以从第二个变量的反向到达
设置 sel[j+n] = true（表示选择变量j的反向）
第三种情况: else

如果以上都不满足
sel[j+(bel[j]>bel[j+n])*n] = true:
如果变量j与其反变量不在同一强连通分量，选择较小索引的那个
如果 bel[j] > bel[j+n]，选择 j+n（反变量）
否则选择 j（正变量）
输出结果: printf("%d ", sel[j] ? 0 : 1);

如果选择了变量j的正向(sel[j]为true)，输出0
如果没有选择变量j的正向(sel[j]为false)，输出1

 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e3+5, M = 2e6+5;

struct node { int to, nxt; } qu[M];

int ent, ex[M], ey[M], qnt, head[N];
void add(int x, int y, bool inc) {
    if (inc) ent++, ex[ent] = x, ey[ent] = y;
    qu[++qnt] = {y, head[x]}, head[x] = qnt;
}
int dfn[N], low[N], tim, st[N], tp, bel[N], bnt;
bool in[N];
void tarjan(int x) {
    dfn[x] = low[x] = ++tim, st[++tp] = x, in[x] = true;
    for (int i = head[x]; i; i = qu[i].nxt) {
        int v = qu[i].to;
        if (!dfn[v]) tarjan(v), low[x] = min(low[x], low[v]);
        else if (in[v]) low[x] = min(low[x], dfn[v]);
    }
    if (low[x] == dfn[x]) {
        bnt++, st[tp+1] = 0;
        while (st[tp+1] != x)
            bel[st[tp]] = bnt, in[st[tp]] = false, tp--;
    }
}

int sgn(int x) { return x < 0 ? -x : x; }

int n, p, fv[M][2], sv[M][2], deg[N], Q;
bool sel[N];
bitset<N/2> a[N][2];
queue<int> q;
bool ok() {
    tim = bnt = ent = qnt = 0;
    for (int i = 1; i <= 2*n; i++)
        head[i] = low[i] = dfn[i] = bel[i] = 0, sel[i] = false,
            a[i][0].reset(), a[i][1].reset();
    for (int i = 1; i <= p; i++) {
        add(sgn(fv[i][0])+(fv[i][0]<0)*n, sgn(fv[i][1])+(fv[i][1]>0)*n, 1);
        add(sgn(fv[i][1])+(fv[i][1]<0)*n, sgn(fv[i][0])+(fv[i][0]>0)*n, 1);
    }
    for (int i = 1; i <= 2*n; i++) if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++) if (bel[i] == bel[i+n]) return false;
    memset(head, 0, sizeof head);
    memset(deg, 0, sizeof deg); qnt = 0;
    for (int i = 1; i <= ent; i++) {
        ex[i] = bel[ex[i]], ey[i] = bel[ey[i]];
        if (ex[i] != ey[i]) add(ey[i], ex[i], 0), deg[ex[i]]++;
    }
    for (int i = 1; i <= 2*n; i++) a[bel[i]][i>n][i-(i>n)*n] = 1;
    for (int i = 1; i <= bnt; i++) if (!deg[i]) q.push(i);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = head[x]; i; i = qu[i].nxt) {
            int v = qu[i].to;
            a[v][0] |= a[x][0], a[v][1] |= a[x][1], deg[v]--;
            if (deg[v] == 0) q.push(v);
        }
    }
    for (int i = 1; i <= Q; i++) {
        int fp = bel[sgn(sv[i][0])+(sv[i][0]<0)*n], sp = bel[sgn(sv[i][1])+(sv[i][1]<0)*n],
        fo = sgn(sv[i][0])+(sv[i][0]>0)*n, so = sgn(sv[i][1])+(sv[i][1]>0)*n;
        if (a[fp][0][so] || a[fp][1][so] || a[sp][0][fo] || a[sp][1][fo]) continue;
        if (((a[fp][0]|a[sp][0])&(a[fp][1]|a[sp][1])).any()) continue;
        for (int j = 1; j <= n; j++) {
            if (a[fp][0][j] || a[sp][0][j]) sel[j] = true;
            else if (a[fp][1][j] || a[sp][1][j]) sel[j+n] = true;
            else sel[j+(bel[j]>bel[j+n])*n] = true;
            printf("%d ", sel[j] ? 0 : 1);
        }
        return true;
    }
    return false;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    n = rd(), p = rd(), Q = rd();
    for (int i = 1; i <= p; i++) fv[i][0] = rd(), fv[i][1] = rd();
    for (int i = 1; i <= Q; i++) sv[i][0] = rd(), sv[i][1] = rd();
    if (ok()) return 0;
    swap(p, Q), swap(fv, sv);
    if (!ok()) printf("SIMILAR");
    return 0;
}