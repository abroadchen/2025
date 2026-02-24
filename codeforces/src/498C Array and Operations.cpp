//
// Created by Psy.C on 2026/2/23.
//
/**
终点y、容量z、下一节点指针nxt
e数组存储边，大小为N<<3即8*N（因为每条边要建两条反向边）
num记录边的数量，初始化为1（这样0号边不存在）
head数组存储每个节点的首条边编号

添加一条从x到y的有向边，容量为z
同时添加反向边，容量为0，用于网络流中的反向增广

实现Dinic算法的BFS部分，构建层次图
lev数组记录每个节点的层次（距离源点的距离）
t是汇点编号
只有当前边还有剩余容量且目标节点未访问过才加入队列
找到汇点t则返回true，否则返回false

实现Dinic算法的DFS部分，在层次图上找增广路径
cur数组是当前弧优化，避免重复遍历已饱和的边
只沿层次递增的方向走，确保在层次图上搜索
对找到的流量更新正向边和反向边的容量
如果从某个节点无法继续扩展，则将其层次设为0

cnt数组记录每个点包含因子x的个数
对于质因子x，重新构建网络流图
奇数位置向汇点连边，容量为该点包含x的个数
偶数位置从源点连边，容量为该点包含x的个数
根据题目给定的边连接相应节点，容量为无穷大
跑最大流算法累加结果

读入节点数n、边数m，设置汇点t=n+1
读入每个节点的权值
读入边，并根据奇偶性调整方向（确保二分图性质）
对每个节点的数值进行质因数分解
对每个质因子运行网络流算法
输出最终答案
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 105, inf = 0x3f3f3f3f;

struct node { int y, z, nxt; } e[N<<3];
int num = 1, head[N];
inline void add(const int x, const int y, const int z) {
    e[++num].y = y; e[num].z = z; e[num].nxt = head[x]; head[x] = num;
    e[++num].y = x; e[num].z = 0; e[num].nxt = head[y]; head[y] = num;
}

int lev[N], t;
inline bool bfs() {
    queue<int> q;
    q.push(0); memset(lev, 0, sizeof(lev)); lev[0] = 1;
    while (!q.empty()) {
        const int x = q.front(); q.pop();
        for (int i = head[x]; i; i = e[i].nxt) {
            int y = e[i].y, z = e[i].z;
            if (lev[y] || !z) continue;
            lev[y] = lev[x] + 1;
            q.push(y);
            if (y == t) return true;
        }
    }
    return false;
}

int cur[N];
inline int dfs(const int x, int s) {
    if (x == t) return s;
    const int ss = s;
    for (int& i = cur[x]; i; i = e[i].nxt) {
        if (int y = e[i].y, z = e[i].z; lev[x] + 1 == lev[y] && z) {
            const int xx = dfs(y, min(z, s));
            if (!xx) lev[y] = 0;
            s -= xx;
            e[i].z -= xx;
            e[i^1].z += xx;
            if (!s) return ss;
        }
    }
    return ss - s;
}

int cnt[N], n, a[N], m, st[N], ed[N], ans;
inline void get(const int x) {
    memset(head, 0, sizeof(head));
    memset(cnt, 0, sizeof(cnt)); num = 1;
    for (int i = 1; i <= n; ++i) {
        while (a[i] % x == 0) a[i] /= x, ++cnt[i];
        if (!cnt[i]) continue;
        if (i&1) add(i, t, cnt[i]);
        else add(0, i, cnt[i]);
    }
    for (int i = 1; i <= m; ++i)
        if (cnt[st[i]] && cnt[ed[i]])
            add(st[i], ed[i], inf);
    while (bfs())
        memcpy(cur, head, sizeof cur), ans += dfs(0, inf);
}

inline char gc() {
    static char now[1<<16], *S, *T;
    if (T == S) {
        T = (S = now) + fread(now, 1, 1<<16, stdin);
        if (T == S) return EOF;
    }
    return *S++;
}
inline int read() {
    int x = 0; char ch = gc();
    while (ch < '0' || ch > '9') ch = gc();
    while (ch <= '9' && ch >= '0') x = (x<<1)+(x<<3)+(ch&15), ch = gc();
    return x;
}

int main() {
    n = read(), m = read(); t = n + 1;
    for (int i = 1; i <= n; ++i) a[i] = read();
    for (int i = 1; i <= m; ++i) {
        st[i] = read(), ed[i] = read();
        if (st[i]&1) swap(st[i], ed[i]);
    }
    for (int i = 1; i <= n; ++i) {
        const int nn = sqrt(a[i]);
        for (int j = 2; j <= nn; ++j)
            if (a[i] % j == 0) get(j);
        if (a[i] != 1) get(a[i]);
    }
    printf("%d\n", ans);
    return 0;
}