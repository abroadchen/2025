//
// Created by Psy.C on 2026/9/30.
//
/**
一个点用分数 (x/y) 表示角度/斜率，z 表示特殊状态：
z=1 的 vec 是"空/无效/负无穷"（排序时排在最前，a.z 为真则 a<b）。
operator<：若 a 为空的（z=1）则小于一切；否则按叉积比较斜率 a.x*b.y < a.y*b.x（即按角度升序）。
operator==：斜率相等判定（叉积相等），用于去重/区间合并。
用 (x:y) 表示极角：这说明题目中的"区间端点"是角度坐标，圆在此映射下变成一段角度区间
l[i]/r[i]：第 i 个圆在角度域上的 [左,右] 区间（operator< 定义角度序）。
c[i]：所有左端点的离散化坐标。
T：堆式线段树地址的数组（利用二进制下标，长度为 2M
堆式线段树：下标从 M 开始是叶子，change 从叶子向上更新；query 用左右指针 l,r 从叶子两侧向上爬，标准 0-based 缩区间求区间最大值。
query(l,r) 返回 [l,r] 上所有"右端点 r" 的最大值（把最大右端点用来判断区间是否被完全覆盖）。
res 初始 z=1（空），取 max 时空值自然不构成影响
每个圆按其左端点 l[x] 离散化到槽 k。槽 k 用大顶堆存所有"左端点位于该槽"的圆的右端点。
若插入 x 后，该槽的最大右端点正好是 x，则更新线段树叶子 T[k] = r[x]（即为"该槽当前覆盖到的最大右端点"）。
u[x]：激活标记。
把 x 标记为失效（u[x]=1，惰性删除），然后不断弹出堆顶已被删除的元素，直到堆顶是有效元素。
若弹掉过元素，则把线段树叶子更新为该堆新的最大值（回退）
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e5, M = 524288;

struct vec {
    int x, y, z;
    friend bool operator<(const vec& a, const vec& b) {
        return a.z || (!b.z && 1ll*a.x*b.y < 1ll*a.y*b.x);
    }
    friend bool operator==(const vec& a, const vec& b) {
        return 1ll*a.x*b.y == 1ll*a.y*b.x;
    }
} l[N+5], r[N+5], c[N+5], T[(M<<1)+5];//(2^19)，树大小 2*M

void change(int k, const vec& x) {
    for (T[k+=M] = x; k >>= 1;)
        T[k] = max(T[k<<1], T[k<<1|1]);
}

vec query(int l, int r) {
    vec res = {.x = 0, .y = 0, .z = 1};//初始为空(z=1)
    for (l+=M-1, r+=M+1; l^r^1; l >>= 1, r >>= 1) {
        if (~l&1) res = max(res, T[l+1]);//左指针偶时取右兄弟
        if (r&1) res = max(res, T[r-1]);//右指针奇时取左兄弟
    }
    return res;
}
//lp[i]: 第 i 个处理器/圆 的离散化下标缓存
int lp[N+5], cnt, u[N+5];
priority_queue<pair<vec, int>> p[N+5];//落在第 k 个离散槽的"r 右端点"大顶堆
void ins(int x) {
    int k = lp[x] ? lp[x] : lp[x] = lower_bound(c+1, c+cnt+1, l[x]) - c;//由左端点定位离散槽
    u[x] = 0; //标记"未删除/激活"
    p[k].emplace(r[x], x);//把 (右端点, id) 压入该槽的大顶堆
    //若 x 成为该槽最大右端点
    if (p[k].top() == make_pair(r[x], x)) change(k, r[x]);//新线段树叶子的值
}

void del(int x) {
    int k = lp[x] ? lp[x] : lp[x] = lower_bound(c+1, c+cnt+1, l[x]) - c, s = 0;
    for (u[x] = 1; u[p[k].top().second]; ++s) p[k].pop();//弹出顶部所有已删除/失效的
    if (s) change(k, p[k].top().first);//更新为该槽现存最大右端点
}

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int t[N+5], x[N+5], y[N+5];
int main() {
    //R: 半平面半径；n: 操作数
    int R = read(), n = read(), i, k;
    for (i = 1; i <= n; ++i) {
        t[i] = read(); x[i] = read();
        if (t[i] != 2) y[i] = read();
        if (t[i] == 1) {//插入一个圆
            ++cnt; c[cnt] = l[cnt] = {.x = x[i]+R, .y = y[i], .z = 0};//左端点(斜率形式)
            r[cnt] = {.x = y[i], .y = R-x[i], .z = 0};//右端点
            x[i] = cnt;//记录这个插入的圆编号
        }
    }
    sort(c+1, c+cnt+1);//左端点排序
    cnt = unique(c+1, c+cnt+1) - c - 1;//离散化去重
    for (i = 1; i < 2*M; ++i) T[i] = {.x = 0, .y = 0, .z = 1};
    for (i = 1; i <= cnt; ++i) p[i].emplace(T[1], 0);//每个槽堆预置"空"哨兵
    for (i = 1; i <= n; ++i) {
        if (t[i] == 1) ins(x[i]);
        if (t[i] == 2) del(x[i]);
        if (t[i] == 3) {//询问 x[i],y[i] 是否连通
            if (l[y[i]] < l[x[i]]) swap(x[i], y[i]);//按左端点排序
            if (r[x[i]] < l[y[i]]) { puts("NO"); continue; }//不相交直接 NO
            //定位 y 的槽
            k = lp[y[i]] ? lp[y[i]] : lp[y[i]] = lower_bound(c+1, c+cnt+1, l[y[i]]) - c;
            del(x[i]); del(y[i]);//先删掉这两圆（避免重复计算自己）
            //查询槽 1..k 的最大右端点是否覆盖到 y 的左端
            puts(query(1, k) < (r[x[i]] < r[y[i]] ? r[x[i]] : r[y[i]]) ? "YES" : "NO");
            ins(x[i]); ins(y[i]);//恢复
        }
    }
    return 0;
}