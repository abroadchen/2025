//
// Created by Psy.C on 2026/10/10.
//
/**
bl = sqrt(n)：每块的大小
cnt：块的数量
b[i]：每个位置所属的块编号 b[i] = (i-1)/bl+1
L[i]、R[i]：第 i 块的左右边界
操作流程（update/query）：

如果 [l,r] 在同一个块内 → 直接暴力处理该块（rebuild）
否则：两边残余块暴力重建，中间整块使用"懒"标记优化

val[i]：位置 i 的真实（当前）值（通过 find(i) 找到代表后取 val[代表]）
fa[i]：并查集父亲
id[x][v]：第 x 块内、值为 v 的代表节点下标
s[i]：以 i 为代表的那组元素个数
mn[x]：第 x 块的最小值（相对基准）‍——这是个重要技巧
mx[x]：第 x 块的最大值（相对基准）‍

遍历块内每个元素，若该值第一次出现则作为代表（id[x][val]=i, s=1），否则并查集合并到代表并 s++
mx[x] 记为块内最大值 t

懒标记技巧：mn[x]（最小值偏移）
代码并不真正逐个减元素，而是通过 mn[x] 整体偏移：
块内元素的"逻辑值" = val[find(i)] - mn[x]
mn[x] 可以理解为"已经从这个块整体减掉的累积量"
于是在处理整块减 k 时，代码把 mn[x] 增大（整体偏移），而不实际修改每个元素，从而
O
(
1
)
O(1) 完成"块内所有元素减 k"的逻辑等价操作。真正发生元素合并时，再用 id[x][v±k] 做值映射

两边的残余块：直接 rebuild 暴力重建（因为只涉及 O(块大小) 个元素）。
中间整块根据情况选择策略：
情况1：mx[x] - mn[x] > 2k（值域跨度大）
由于 k 相对整块值域很小，"减 k" 会把值为 mn+1 ... mn+k 的元素整体变成 mn+1-k ... mn（即整体左移）。此时直接把 mn[x] += k，并对低值部分做并查集合并即可——因为大跨度下不会发生"k 与 2k 之间交叉"，整体偏移安全。
情况2：值域跨度小
逐个处理高于 mn+k 的值 i：把值为 i 的代表映射/合并到值为 i-k 的代表（id[x][i-k]），并更新 s 计数和 fa 并查集。最后收窄 mx[x]

残余块：暴力枚举每个元素，通过 val[find(i)] - mn[块] 计算逻辑值判断是否等于 k
整块：利用结构 id[i][v] 和懒标记，直接 s[id[i][mn[i]+k]] 拿到"值为 k 的元素组"的个数——O(1) 得到整块答案

对于被修改的残余块，需要把懒标记 mn[x] 先"摊还"回真实值（val[find(i)]-mn[x]），清空 id，对指定区间真正执行减 k，然后重新 build

每块大小
O
(
n
)
O(
n
​
 )，共
O
(
n
)
O(
n
​
 ) 块
update：
O
(
n
)
O(
n
​
 ) 用于残余块重建；中间块因并查集合并，整体均摊接近
O
(
n
)
O(
n
​
 )（每个值最多被合并常数次）
query：
O
(
n
)
O(
n
​
 )（残余块暴力 + 整块 O(1)）
总复杂度大致
O
(
m
n
)
O(m
n
​
 ) 级别（加上并查集和懒标记的常数额外优化）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, M = 355;

int fa[N];
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

inline void chkmax(int&a ,int b) { a < b ? a = b : 0; }

int mn[M], L[M], R[M], a[N], val[N], id[M][N], s[N], mx[M];
inline void build(int x) {
    mn[x] = 0;
    int t = 0;
    for (int i = L[x]; i <= R[x]; ++i) fa[i] = i;
    for (int i = L[x]; i <= R[x]; ++i) {
        chkmax(t, a[i]); val[i] = a[i];
        if (!id[x][val[i]]) id[x][val[i]] = i, s[i] = 1;
        else fa[i] = id[x][val[i]], s[find(i)]++;
    }
    mx[x] = t;
}
inline void rebuild(int x, int l, int r, int k) {
    for (int i = L[x]; i <= R[x]; ++i)
        id[x][val[i]] = 0, a[i] = val[find(i)]-mn[x];//先把懒标记实体化：还原每个位置的真实逻辑值
    for (int i = l; i <= r; ++i)
        if (a[i] > k) a[i] -= k;//对 [l,r] 中大于 k 的减 k
    build(x);//重新构建
}

int b[N];
inline void update(int l, int r, int k) {
    if (b[l] == b[r]) { rebuild(b[l], l, r, k); return; }
    rebuild(b[l], l, R[b[l]], k);
    rebuild(b[r], L[b[r]], r, k);
    for (int x = b[l]+1; x < b[r]; ++x) {
        if (mx[x] - mn[x] > 2*k) {//范围大，整体结果"值域宽"，做整体左移
            for (int i = mn[x]+1; i <= mn[x]+k; ++i) {
                if (!id[x][i]) continue;
                if (!id[x][i+k]) id[x][i+k] = id[x][i], val[id[x][i]] = i+k, id[x][i] = 0;
                else s[id[x][i+k]] += s[id[x][i]], fa[id[x][i]] = id[x][i+k], id[x][i] = 0;
            }
            mn[x] += k;
        } else {
            for (int i = mn[x]+k+1; i <= mx[x]; ++i) {//范围小，逐个把大值减 k 合并
                if (!id[x][i]) continue;
                if (!id[x][i-k]) id[x][i-k] = id[x][i], val[id[x][i]] = i-k, id[x][i] = 0;
                else s[id[x][i-k]] += s[id[x][i]], fa[id[x][i]] = id[x][i-k], id[x][i] = 0;
            }
            while (!id[x][mx[x]]) mx[x]--;
        }
    }
}

inline int query(int l, int r, int k) {
    int res = 0;
    if (b[l] == b[r]) {//同一块：暴力
        for (int i = l; i <= r; ++i)
            if (val[find(i)]-mn[b[l]] == k) res++;
        return res;
    }
    for (int i = l; i <= R[b[l]]; ++i)//左残余块
        if (val[find(i)]-mn[b[l]] == k) res++;
    for (int i = L[b[r]]; i <= r; ++i)//右残余块
        if (val[find(i)]-mn[b[r]] == k) res++;
    for (int i = b[l]+1; i < b[r]; ++i)//中间整块：利用 id/mn/mx 直接 O(1) 取计数
        if (mn[i]+k <= mx[i]) res += s[id[i][mn[i]+k]];
    return res;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    fast;
    int n = rd(), m = rd(), bl = sqrt(n), cnt = (n-1)/bl+1;
    for (int i = 1; i <= n; ++i) a[i] = rd();
    for (int i = 1; i <= n; ++i) b[i] = (i-1)/bl+1;
    for (int i = 1; i <= cnt; ++i)
        L[i] = (i-1)*bl+1, R[i] = min(i*bl, n);
    for (int i = 1; i <= cnt; ++i) build(i);
    while (m--) {
        int op = rd(), l = rd(), r = rd(), k = rd();
        if (op == 1) update(l, r, k);
        else cout << query(l, r, k) << '\n';
    }
    return 0;
}