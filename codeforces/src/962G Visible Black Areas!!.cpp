//
// Created by Psy.C on 2026/10/21.
//
/**
p 数组存"生成点"（突破矩形边框的交点），最多 2N 个。
f 为并查集父数组，find 为路径压缩查找
x[N]/y[N]：输入多边形各顶点坐标。
lx, ly, rx, ry：矩形的左、下、右、上边界（注意读入顺序，见主函数）。
pn：当前生成的点（交点）个数
处理多边形边 (x[l],y[l]) -> (x[r],y[r]) 与矩形的交点。分两种情况
边的两个端点 x 相同（竖直边）
若这条竖直边的 x 坐标不在矩形左右边界之间（即 x[l]<=lx 或 x[l]>=rx），说明不与矩形相交，直接 return。
注意是严格之间（不等号方向），即边框本身旁的边被排除
若 y[l]<y[r]（边自下而上）：可能穿下边界 ly 或上边界 ry；凡穿过的边界就把 (x[l], 边界y) 加入 p。穿过底部和顶部两个点之间用并查集合并（f[find(pn-1)]=find(pn)，把这两个相邻交点连起来）。
若 y[l]>y[r]（边自上而下）：对称处理——可能穿顶部 ry 或底部 ly，同样记录交点并（对落在底部、顶部相邻的两个）用并查集合并。
可确证：对竖直边（x 相同），若 x 不在 (lx,rx) 内则跳过；否则按 y 方向判断是否穿越 ly/ry 边界并记录交点，相邻两交点并查集合并
若 y 不在 (ly, ry) 内则跳过。
若 x[l]<x[r]（自左向右）：可能穿越左边界 lx 或右边界 rx，记录交点并（对穿过左、右两侧的相邻两点）并查集合并。
若 x[l]>x[r]（自右向左）：对称处理右 rx、左 lx。
可确证：对水平边（y 相同），若 y 不在 (ly,ry) 内则跳过；否则按 x 方向判断是否穿越 lx/rx 并记录交点，相邻交点并查集合并
把矩形边界展开成一维坐标（从点 (lx,ly) 逆时针绕一圈）：
底边（y==ly）：编号 = x-lx。
右边（x==rx）：编号 = (rx-lx) + (y-ly)。
顶边（y==ry）：编号 = (rx-lx)+(ry-ly)+(rx-x)。
左边（其他，即 x==lx）：编号 = 2*(rx-lx)+(ry-ly)+(ry-y)。
<<1 即乘 2。
可确证：get 把矩形边界上一点映射成从(lx,ly)绕一圈的一维周长位置，四条边分别用三/四种公式

读入顺序：lx, ry, rx, ly, n。
所以实际：lx=左、ry=上、rx=右、ly=下。即矩形为 [lx, rx] × [ly, ry]
读 n 个顶点。
pos 记录最后一个严格在矩形内部之外的点（即 x<=lx || x>=rx || y<=ly || y>=ry 的点）。最后记录的那一个作为环形起点 pos。
若没有一个点在矩形外（!pos），输出 1 并结束（矩形完全在多边形内/不切割的情况）。
可确证：读入顶点并记录最后一个"不在矩形严格内部"的点的下标 pos；若 pos 为空则输出 1
初始化并查集 f 和数组 d（用于排序的交点下标）为自身。最大到 2n
从 pos 处断开，按环形顺序依次对每条边调用 func 求交点：先 (pos+1..n) 段，再 func(n,1)，再 (2..pos) 段。
这样保证从 pos 点出发沿多边形走一圈，所有与矩形边界的交点都被生成。
可确证：从 pos 处断开后依环形顺序对每条边调用 func，生成所有交点
若没有任何交点（矩形完全不被多边形穿过），此时可能只有底边 ly 被多边形某条水平边恰好覆盖的情况。
对每条相邻边，若 y 相同且等于/低于下边界 ly，且横跨 [lx, rx] 完整区间，则 ans ^= 1（翻转奇偶）。
首尾边（1 与 n）单独判断一次。
输出 ans（0 或 1）。
可确证：无交点时，检测是否有水平边恰好横跨矩形底边 [lx,rx] 且 y<=ly，据此用异或累计 ans 再输出
按各交点在矩形边界周长上的位置（get 值）从小到大排序 d[1..pn]，即把交点沿矩形边界环形排列。
可确证：按 get 值（周长绕行位置）对交点下标排序
d[1]&1：判断首个交点下标奇偶（d[1] 是边编号），决定从 i=2 还是 i=3 开始，步长 2。
把排序后每隔一个的交点两两用并查集合并（连接相邻成对的交点，步长2）。
可确证：从 d 中按奇偶错开、步长 2 把相邻交点两两并查集合并
若 d[1] 是奇数，再把首尾两交点合并（把环形闭合起来）。
可确证：d[1] 为奇数时合并首尾交点
统计并查集中独立的根个数（连通块数）计入 ans，输出。
可确证：统计独立根数作为 ans 输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 15005;

struct node { int x, y; } p[N<<1];

int f[N<<1];
int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

int x[N], y[N], lx, ly, rx, ry, pn;
inline void func(int l, int r) {
    if (x[l] == x[r]) {
        if (x[l] <= lx || x[l] >= rx) return;
        if (y[l] < y[r]) {
            if (y[l] <= ly && y[r] > ly) p[++pn] = {x[l], ly};
            if (y[l] < ry && y[r] >= ry) p[++pn] = {x[l], ry}, f[find(pn-1)] = find(pn);
        } else {
            if (y[l] >= ry && y[r] < ry) p[++pn] = {x[l], ry};
            if (y[l] > ly && y[r] <= ly) p[++pn] = {x[l], ly}, f[find(pn-1)] = find(pn);
        }
    } else {
        if (y[l] <= ly || y[l] >= ry) return;
        if (x[l] < x[r]) {
            if (x[l] <= lx && x[r] > lx) p[++pn] = {lx, y[l]};
            if (x[l] < rx && x[r] >= rx) p[++pn] = {rx, y[l]}, f[find(pn-1)] = find(pn);
        } else {
            if (x[l] >= rx && x[r] < rx) p[++pn] = {rx, y[l]};
            if (x[l] > lx && x[r] <= lx) p[++pn] = {lx, y[l]}, f[find(pn-1)] = find(pn);
        }
    }
}
inline int get(int l) {
    if (p[l].y == ly) return p[l].x - lx;
    if (p[l].x == rx) return rx - lx + p[l].y - ly;
    if (p[l].y == ry) return rx - lx + ry - ly + rx - p[l].x;
    return ((rx-lx)<<1) + ry - ly + ry - p[l].y;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, pos, d[N<<1], ans;
int main() {
    fast;
    lx = rd(), ry = rd(), rx = rd(), ly = rd(), n = rd();
    for (int i = 1; i <= n; i++) {
        x[i] = rd(), y[i] = rd();
        if (x[i] <= lx || x[i] >= rx || y[i] <= ly || y[i] >= ry) pos = i;
    }
    if (!pos) { cout << "1\n"; return 0; }
    for (int i = 1; i <= n<<1; i++) f[i] = d[i] = i;
    for (int i = pos+1; i <= n; i++) func(i-1, i);
    func(n, 1);
    for (int i = 2; i <= pos; i++) func(i-1, i);
    if (!pn) {
        for (int i = 2; i <= n; i++)
            if (y[i] == y[i-1] && y[i] <= ly && min(x[i], x[i-1]) <= lx && max(x[i], x[i-1]) >= rx)
                ans ^= 1;
        if (y[1] == y[n] && y[1] <= ly && min(x[1], x[n]) <= lx && max(x[1], x[n]) >= rx)
            ans ^= 1;
        cout << ans << '\n';
        return 0;
    }
    sort(d+1, d+1+pn, [](int x, int y) {
        return get(x) < get(y);
    });
    for (int i = d[1]&1?3:2; i <= pn; i += 2) f[find(d[i-1])] = find(d[i]);
    if (d[1]&1) f[find(d[1])] = find(d[pn]);
    for (int i = 1; i <= pn; i++) if (i == find(i)) ans++;
    cout << ans << '\n';
    return 0;
}