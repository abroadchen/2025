//
// Created by Psy.C on 2026/5/27.
//
/**
- N = 200005 ：数组大小上限。
- inf = 1000000007 ：大值常量（通常用作模或无穷大）。
- M = 100000 ：时间 t 的最大值上限，用于线段树值域
- sum[x] ：节点 x 维护的某种加权和。
- siz[x] ：节点 x 维护的元素数量

线段树单点更新函数：
- x ：当前节点编号。
- l , r ：当前节点维护的区间 [l, r] 。
- pos ：要更新的位置（时间 t 值）。
- v ：增量（+1或-1，表示添加或移除一个元素）
边界条件：区间非法或位置为0（无效）时直接返回
- l - (int)ceil(1.*l/2) ：计算位置 l 的权重。例如 l=1 时权重为 1-1=0 ； l=2 时权重为 2-1=1 ； l=3 时权重为 3-2=1 ； l=4 时权重为 4-2=2 。权重大致是 ⌊l/2⌋ 。
- sum[x] += 权重 * v ：累加加权值。
- siz[x] += v ：累加元素个数。
- void() ：强制返回void类型（因为用了逗号表达式）

初始化滑动窗口：
- j=1 ，窗口右端从第1个物品开始。
- 线段树添加 t[1] 。
- Sum 记录当前窗口的时间总和
尝试扩展窗口右端 ：当窗口右端还能扩展，且扩展后满足约束条件时。
- query(1, 1, M, w) ：查询当前窗口中权值最小的 w 个元素的加权和。
- Sum - query(...) ：从总时间中减去最小的 w 个的加权和，判断剩余是否 ≤ k 。
- 含义：在选 w 个物品的约束下，判断是否能扩展窗口
扩展窗口：右端 j 右移，将 t[j] 加入线段树，累加时间
撤销上一步的扩展 （因为条件不满足或循环结束）：
- 将刚才添加的 t[j] 从线段树移除。
- 将当前左端 t[i] 也移除（因为窗口要右移， i 要离开窗口）。
- 从 Sum 中减去两者。
- j-- 恢复右端位置
更新答案：窗口 [i, j] 内物品的价值总和 = pre[j] - pre[i-1] ，取最大值

 */
#include "bits/stdc++.h"
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5, inf = 1e9+7, M = 1e5;

int sum[N<<2], siz[N<<2];
void update(int x, int l, int r, int pos, int v) {
    if (l > r || !pos) return;
    if (l == r) return sum[x] += (l - (int)ceil(1.*l/2))*v, siz[x] += v, void();
    int mid = (l+r)>>1;
    //若 pos 在左半区间，递归左儿子 x<<1 否则递归右儿子 x<<1|1
    if (pos <= mid) update(x<<1, l, mid, pos, v);
    else update(x<<1|1, mid+1, r, pos, v);
    //回溯时合并左右子树的结果
    sum[x] = sum[x<<1] + sum[x<<1|1];
    siz[x] = siz[x<<1] + siz[x<<1|1];
}

//查询线段树中 权值最小的前 k 个元素 的加权和
int query(int x, int l, int r, int k) {
    if (k <= 0) return 0;//不需要取元素，返回0
    //需要的元素数大于等于当前区间的元素总数，直接返回整个区间的加权和
    if (k >= siz[x]) return sum[x];
    //叶节点：平均每个元素的权重 × 取的元素数（向下取整）
    if (l == r) return sum[x]/siz[x]*min(k, siz[x]);
    int mid = (l+r)>>1, ls = siz[x<<1], rs = siz[x<<1|1];
    //如果需要的 k 个元素全在右子树（因为右子树对应更大的时间值，权值更小），直接递归右子树
    if (k <= rs) return query(x<<1|1, mid+1, r, k);
    //否则：右子树全取（ sum[x<<1|1] ），剩余 k-rs 个从左子树取
    return query(x<<1, l, mid, k-rs) + sum[x<<1|1];
}

//支持任意整数类型。逐字符读取，遇到负号标记，将数字字符转换为整数
template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;//计算数字位数 len
    for (; y <= x/10; y *= 10) ++len;
    //逐位输出： x/y+48 将数字转为字符， x%=y 去掉已输出的位
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

/**
- n ：物品数量。
- w ：最多允许的时间总和上限。
- k ：时间限制参数。
- a[i] ：第 i 个物品的价值。
- pre[i] ： a 数组的前缀和。
- t[i] ：第 i 个物品的时间。
- Sum ：当前滑动窗口内的时间总和。
- Ans ：最终答案（最大价值和）
 */
int n, w, k, a[N], pre[N], t[N], Sum, Ans;
int main() {
    fast;
    read(n), read(w), read(k);
    for (int i = 1; i <= n; ++i) read(a[i]), pre[i] = pre[i-1] + a[i];
    for (int i = 1; i <= n; ++i) read(t[i]);
    int j = 1;
    update(1, 1, M, t[1], 1); Sum = t[1];
    //枚举窗口左端点 i
    for (int i = 1; i <= n; ++i) {
        while (j <= n && Sum - query(1, 1, M, w) <= k) {
            j++;
            update(1, 1, M, t[j], 1);
            Sum += t[j];
        }
        update(1, 1, M, t[j], -1), update(1, 1, M, t[i], -1);
        Sum -= t[i] + t[j];
        j--;
        Ans = max(Ans, pre[j] - pre[i-1]);
    }
    write(Ans);
    return 0;
}