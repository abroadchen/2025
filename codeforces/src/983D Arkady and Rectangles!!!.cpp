//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
cr：一个有序 set，存当前完整覆盖该区间的所有"颜色 id"（即矩形 id）。rbegin() 是其中最大（最新加入）的颜色。
mx：该区间"最顶层可见颜色"（即最终画在最上面的），未确定时为 -1。
mn：该区间"最底层可见颜色"
mid/ls/rs：线段树的常规左右子访问。
vis[N]：每种颜色累计贡献的新区域数
叶节点（flag=1）‍：
mx：若 cr 为空，或顶层颜色已被 vis 标记（已经统计过、不再算新区域），则 -1；否则为顶层颜色 rbegin()。
mn：若 cr 为空则 -1，否则同样取顶层颜色（这里叶节点只有一层，mn 也用顶层）。
内部节点（flag=0）‍：
先取左右子 mx 的最大值、mn 的最小值作为初始值。
若本区间自身有覆盖颜色 cr，取最大颜色 cmx。
若 cmx > 当前 mx：说明本区间的覆盖颜色比子区间推上来的颜色更高层（更大）。
若当前 mx == -1（子树没有顶层），则按 cmx 与 mn 的相对关系决定 mx 是否取 cmx（且要考虑 vis）。
否则若 cmx 更大，则 mx 更新为 cmx（除非该颜色已访问）。
最后 mn 取 max(mn, cmx)：覆盖颜色至少保证是最底层可见的。
作用：trans 负责在增删覆盖颜色、以及子树变化后，重新计算一个节点负责的 x 区间内"顶层可见颜色 mx"和"底层可见颜色 mn"
建树，区间范围为 [1, m-1]（m 为去重后的 x 坐标数量，所以是 m-1 个 x 区间）
区间覆盖（添加颜色）‍：把颜色 cl 加进区间 [b,e] 上所有完整覆盖的节点，并重新 trans 更新
区间删除颜色：与 cov 对称，把颜色 cl 从 cr 中移除并更新
区间刷新：不增删颜色，只是递归到子节点后重新 trans，用于某颜色被 vis 标记（已统计）后，重新计算顶层可见性，使树顶 mx 反映"下一个未统计的顶层颜色"
line：一条水平扫描线事件。lx, rx 是 x 区间（离散化后的），y 是 y 坐标，cr 是矩形颜色 id，d 是 1（下边界，入）或 -1（上边界，出）。
b[]：用于离散化的 x 坐标数组。
l[i], r[i]：第 i 个矩形的离散 x 区间
读入 n 个矩形（读入顺序为 x1, y1, x2, y2）。
每个矩形产生两条水平线事件：下边界 y1（d=1 进入）、上边界 y2（d=-1 离开）。
记录 x 坐标用于离散化
对 x 坐标排序、去重，得到 m 个不同的 x 坐标
把每条线的 lx, rx 离散化为 1..m 的索引。
保存每个矩形的 l[i], r[i]（x 区间索引）
按 y 坐标从小到大排序所有扫描线事件（经典的扫描线 y 排序）
build()：建立空线段树。
遍历所有扫描线事件（已按 y 排序）：
若 d == 1（下边/进入），用 cov 将该颜色加入其 x 区间；否则 rem 移除。
当遇到"当前 y 层结束"（y 与下一条不同，或是最后一条）时：取出树顶全局 mx（当前最顶层可见且未统计的颜色）t。
只要 t != -1：把 vis[t] 加 1（记录颜色 t 在这一层新产生了区域），然后 update 该颜色对应的 x 区间，重新计算顶层可见性，再取新的 tr[1].mx，循环直到没有未统计的顶层颜色。
核心思想：在每条水平扫描线处，处理完该层的矩形进入/离开后，检查最新"冒出来"的顶层颜色，每冒出一种颜色就给它记一次（vis++），这累计了各颜色分割出的区域数
初始 ans = 1（整个平面最初算 1 个区域）。
对每个矩形颜色 i，把 vis[i]（该矩形贡献的分割区域数）累加。
输出 ans，即平面上被这些矩形分割出的总区域数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+5;

struct node {
    set<int> cr;
    int mx, mn;
} tr[N<<3];
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (p<<1|1)


int vis[N];
void trans(int p, int flag) {
    if (flag) {
        tr[p].mx = tr[p].cr.empty() || vis[*tr[p].cr.rbegin()] ? -1 : *tr[p].cr.rbegin();
        tr[p].mn = tr[p].cr.empty() ? -1 : *tr[p].cr.rbegin();
        return;
    }
    tr[p].mx = max(tr[ls].mx, tr[rs].mx);
    tr[p].mn = min(tr[ls].mn, tr[rs].mn);
    if (tr[p].cr.empty()) return;
    int cmx = *tr[p].cr.rbegin();
    if (cmx > tr[p].mx) {
        if (tr[p].mx == -1) tr[p].mx = cmx>tr[p].mn ? (vis[cmx]?-1:cmx) : -1;
        else tr[p].mx =  vis[cmx] ? -1 : cmx;
    }
    tr[p].mn = max(tr[p].mn, cmx);
}

int m;
void build(int p=1, int l=1, int r=m-1) {
    if (l == r) { trans(p, 1); return; }
    build(ls, l, mid); build(rs, mid+1, r);
    trans(p, 0);
}
void cov(int b, int e, int cl, int p=1, int l=1, int r=m-1) {
    if (b <= l && e >= r) {
        tr[p].cr.insert(cl);
        trans(p, l==r);
        return;
    }
    if (b <= mid) cov(b, e, cl, ls, l, mid);
    if (e > mid) cov(b, e, cl, rs, mid+1, r);
    trans(p, l==r);
}
void rem(int b, int e, int cl, int p=1, int l=1, int r=m-1) {
    if (b <= l && e >= r) {
        tr[p].cr.erase(tr[p].cr.find(cl));
        trans(p, l==r);
        return;
    }
    if (b <= mid) rem(b, e, cl, ls, l, mid);
    if (e > mid) rem(b, e, cl, rs, mid+1, r);
    trans(p, l==r);
}

void update(int b, int e, int p=1, int l=1, int r=m-1) {
    if (b <= l && e >= r) {
        trans(p, l==r);
        return;
    }
    if (b <= mid) update(b, e, ls, l, mid);
    if (e > mid) update(b, e, rs, mid+1, r);
    trans(p, l==r);
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}

struct line { int lx, rx, y, cr, d; } ln[N<<1];
int b[N<<1];

int n, l[N], r[N];
int main() {
    fast;
    read(n);
    rep(i,n) {
        int x1, x2, y1, y2; read(x1, y1, x2, y2);
        int p = i<<1;
        ln[p] = {x1, x2, y1, i, 1};
        ln[p-1] = {x1, x2, y2, i, -1};
        b[p] = x1; b[p-1] = x2;
    }
    sort(b+1, b+n*2+1);
    m = unique(b+1, b+n*2+1)-b-1;
    rep(i,n) {
        int p = i<<1;
        ln[p].lx = lower_bound(b+1, b+m+1, ln[p].lx) - b;
        ln[p].rx = lower_bound(b+1, b+m+1, ln[p].rx) - b;
        ln[p-1].lx = lower_bound(b+1, b+m+1, ln[p-1].lx) - b;
        ln[p-1].rx = lower_bound(b+1, b+m+1, ln[p-1].rx) - b;
        l[i] = ln[p].lx, r[i] = ln[p].rx;
    }
    sort(ln+1, ln+n*2+1, [](const line& L, const line& R) {
        return L.y < R.y;
    });
    build();
    rep(i,n*2) {
        if (ln[i].d == 1) cov(ln[i].lx, ln[i].rx-1, ln[i].cr);
        else rem(ln[i].lx, ln[i].rx-1, ln[i].cr);
        if (ln[i].y != ln[i+1].y || i == n*2) {
            int t = tr[1].mx;
            while (t != -1) {
                ++vis[t];
                update(l[t], r[t]-1);
                t = tr[1].mx;
            }
        }
    }
    int ans = 1;
    rep(i,n) ans += vis[i];
    cout << ans;
    return 0;
}