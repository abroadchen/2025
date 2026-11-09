//
// Created by Psy.C on 2026/11/9.
//

/**
真正学会的起点..
out：递归输出数字（一位一位拆），只输出不换行。
ot：带正负号、后面跟一个空格地输出（用于输出坐标点）
head 是邻接表头，cnt 从 1 开始计数（原因见下）。
add 同时插入正向边 w 和反向边 0。
关键技巧：反向边的编号是 cnt ^ 1（因为第奇数条/偶数条成对），所以：
e[i^1].w 用异或就能拿到反向边的容量——这是 Dinic 中"撤销流量"的关键
沿"层级递增 1"的边找增广路，min(res, cap) 限制流量。
e[i].w -= k; e[i^1].w += k：正边减流量、反边加流量（即反向边表示可退还的流量）。
返回 flow - res = 本次实际推送的流量
注意这个 BFS 是从汇点反向做分层的：d[t]=t+1 一个较大初值，每往源方向走一步 d-1，于是从 s 到 t 层级递增。这和 dfs 里 d[y]==d[x]+1 是一致的（只是方向定义特殊）。这是一种常见的反向分层写法
反复分层→增广，直到无法分层（即最大流求完）。这就是 Dinic 算法
pt：平面点，op() 负责输出"x y "。
ln：一条线段——pos 是固定坐标（水平线段的 x / 竖直的 y），l..r 是沿另一个方向的区间。
水平线段 X：pos = x 坐标，l..r = y 区间。
竖直线段 Y：pos = y 坐标，l..r = x 区间
判断一条水平线段与一条竖直线段是否相交（用于构图：相交的水平、竖直线段不能同时选，构成二分图的"冲突边"）
在已求完最大流的残量网络上，从源点 s 沿还有"剩余容量"的边走，标记所有可达顶点 vis。

这是求二分图最小点覆盖的经典步骤：算出最大匹配后，用残量网络划定左右部的选择边界，决定哪些线段被选中构成覆盖

收集所有唯一 x（tl）和唯一 y（th），排序去重，lc/hc 是去重后数量
li[i]：第 i 条垂直（同一 x）上所有点的 y 坐标，已排序。
h[i]：第 i 条水平（同一 y）上所有点的 x 坐标，已排序
同一 x 上，相邻两个点之间若存在空隙（now-1 >= lst+1 即中间至少空一个单位），就生成一条垂直线段 X[cx]：pos=该 x，区间取中间空隙 [lst+1, now-1]
同理，同一 y 上相邻点间空隙生成水平线段 Y[cy]
左部 = 垂直线段（编号 1..cx），右部 = 水平线段（编号 cx+1..cx+cy）。
相交的一对 (X, Y) 用大容量边 inf 相连。
源到左部、右部到汇都是容量 1 → 最大流 = 二分图最大匹配。
因为需要"线段不交叉"，实际上要求的是最小点覆盖/最大独立集，所以求完最大流后要借助 in() 的结果来划分
依据 vis[s] != vis[now]：每个 X 线段若"一边可达一边不可达"（即落在最小割边界 = 被选入最小点覆盖），则这段成为覆盖区间。
把每列被选中的各段首尾相接，拆成互不重叠的竖直线段存入 ax[]
每条线段输出 4 个数：起点 (ax,y)、终点 (bx,y)。
注意输出顺序是先竖直线段组 ry、再垂直组 rx，且水平线段在前、垂直线段在后——题目要求的输出格式
*/
#include <bits/stdc++.h>
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;

constexpr int N = 1005, inf = 0x3f3f3f3f;

template<class T>
void out(T x) { if (x/10) out(x/10); putchar(x%10+'0'); }

template<class T>
void ot(T x) { if (x < 0) putchar('-'), x = -x; out(x); putchar(' '); }

struct node { int nxt, to, w; } e[N*N+N+N];

int head[N<<1], cnt(1);
void add(int x, int y, int w) {
    e[++cnt].to = y; e[cnt].w = w; e[cnt].nxt = head[x]; head[x] = cnt;
    e[++cnt].to = x; e[cnt].w = 0; e[cnt].nxt = head[y]; head[y] = cnt;
}

int s, t, d[N<<1];
int dfs(int x, int flow) {
    if (x == t) return flow;
    int res = flow;
    for (int i = head[x]; i && res; i = e[i].nxt) {
        int y = e[i].to;
        if (d[y] == d[x] + 1) {
            int k = dfs(y, min(res, e[i].w));
            if (!k) d[y] = 0;
            res -= k; e[i].w -= k; e[i^1].w += k;
        }
    }
    return flow - res;
}

int l, r, q[N<<1];
bool bfs() {
    l = 1, r = 0; memset(d, 0, sizeof(d));
    q[++r] = t; d[t] = t + 1;
    while (l <= r) {
        int x = q[l++];
        for (int i = head[x]; i; i = e[i].nxt) {
            int y = e[i].to;
            if (e[i^1].w && !d[y]) {
                d[y] = d[x] - 1;
                q[++r] = y;
                if (y == s) return 1;
            }
        }
    }
    return 0;
}
struct pt {
    int x, y;
    void op() const { ot(x); ot(y); }
} p[N];
struct ln { int pos, l, r; } X[N], Y[N];

bool cross(ln a, ln b) {
    if (b.l <= a.pos && a.pos <= b.r && a.l <= b.pos && b.pos <= a.r) return 1;
    return 0;
}

bool vis[N<<1];
void in() {
    l = 1, r = 0; q[++r] = s; vis[s] = 1;
    while (l <= r) {
        int x = q[l++];
        for (int i = head[x]; i; i = e[i].nxt) {
            int y = e[i].to;
            if (!vis[y] && e[i].w) { vis[y] = 1; q[++r] = y; }
        }
    }
}
struct sol { pt a, b; } ax[N], ay[N];

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, tl[N], lc, th[N], hc, cx, cy, rx, ry;
vector<int> h[N], li[N], ex[N], ey[N];
int main() {
    int i, j;
    read(n);
    rep(i,n) {
        read(p[i].x), read(p[i].y);
        tl[++lc] = p[i].x; th[++hc] = p[i].y;
    }
    sort(tl+1, tl+lc+1); lc = unique(tl+1, tl+lc+1) - tl - 1;
    sort(th+1, th+hc+1); hc = unique(th+1, th+hc+1) - th - 1;
    rep(i,n) {
        int tx = lower_bound(tl+1, tl+lc+1, p[i].x) - tl;//x 离散化后下标
        int ty = lower_bound(th+1, th+hc+1, p[i].y) - th;//y 离散化后下标
        h[ty].push_back(p[i].x); li[tx].push_back(p[i].y);//同一 y 的行，收集 x 同一 x 的列，收集 y
    }
    rep(i,lc) ranges::sort(li[i]);//每组坐标排序
    rep(i,hc) ranges::sort(h[i]);
    rep(i,lc) {
        if (li[i].empty()) continue;
        int lst = li[i][0];
        rep(j,li[i].size()-1) {
            int now = li[i][j];
            if (now - 1 >= lst + 1) {
                ++cx; X[cx].pos = tl[i]; X[cx].r = now-1; X[cx].l = lst+1; ex[i].push_back(cx);
            }
            lst = now;
        }
    }
    rep(i,hc) {
        if (h[i].empty()) continue;
        int lst = h[i][0];
        rep(j,h[i].size()-1) {
            int now = h[i][j];
            if (now - 1 >= lst + 1) {
                ++cy; Y[cy].pos = th[i]; Y[cy].r = now-1; Y[cy].l = lst+1; ey[i].push_back(cy);
            }
            lst = now;
        }
    }
    s = 0; t = cx + cy + 1;
    rep(i,cx) {
        add(s, i, 1);//源→每条垂直线段，容量1
        rep(j,cy) if (cross(X[i], Y[j])) add(i, j+cx, inf);//相交则连边
    }
    rep(i,cy) add(i+cx, t, 1);//每条水平线段→汇，容量1
    while (bfs()) while (dfs(s, inf)) {}//Dinic 求最大流
    in();//残量网络访问标记
    rep(i,lc) {
        if (li[i].empty()) continue;
        int le = li[i][0], ri;
        for (auto now : ex[i]) if (vis[s] != vis[now]) {//该线段在最小割的"边界"上 → 被选中
            ri = X[now].l - 1; ++rx;
            ax[rx].a = {X[now].pos, le}; ax[rx].b = {X[now].pos, ri};
            le = X[now].r + 1;
        }
        ri = li[i][li[i].size()-1]; ++rx;
        ax[rx].a = {tl[i], le}; ax[rx].b = {tl[i], ri};//最后一段
    }
    rep(i,hc) {
        if (h[i].empty()) continue;
        int le = h[i][0], ri;
        for (auto now : ey[i]) if (vis[t] != vis[now+cx]) {
            ri = Y[now].l - 1; ++ry;
            ay[ry].a = {le, Y[now].pos}; ay[ry].b = {ri, Y[now].pos};
            le = Y[now].r + 1;
        }
        ri = h[i][h[i].size()-1]; ++ry;
        ay[ry].a = {le, th[i]}; ay[ry].b = {ri, th[i]};
    }
    cout << ry << '\n';
    rep(i,ry) { ay[i].a.op(); ay[i].b.op(); cout << '\n'; }
    cout << rx << '\n';
    rep(i,rx) { ax[i].a.op(); ax[i].b.op(); cout << '\n'; }
    return 0;
}