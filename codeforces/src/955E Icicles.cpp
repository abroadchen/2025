//
// Created by Psy.C on 2026/10/19.
//
/**
N = 1e5+5：数组上限（含哨兵位）。
inf = 1e9：无穷大（用于"不存在"）。
x[i]：log2(i) 的整数下取整（预计算，供 RMQ 查表用）。
mn[N][25]：稀疏表，存区间原生最小值（值 = a[x]）。20 层足够覆盖 1e5 内任意区间长度（2^20 ≈ 1e6）
区间最小值查询（对 mn 表）：区间 [l,r] 的长度 len = r-l+1，取其二进制最高位 k（k = floor(log2 len)），用两个长度为 2^k 的重叠块覆盖整个区间，取两者最小值。O(1)。l>r 返回 inf（空区间）
另一张表 pre 的区间最小值查询，与上面结构完全相同，只是底层值是 a[x]-x
第三张表 suf 的区间最小值查询，底层值是 a[x]+x。

这三张表分别代表：a[i]、a[i]-i、a[i]+i 的区间最小值。后两者常用于把"左右方向的不等式"合并（例如覆盖范围 [i-a[i]+1, i+a[i]-1] 类问题）

读 n 和数组 a。
初始化每张表的第 0 层（长度为 1 的区间）：
mn[i][0] = a[i]
pre[i][0] = a[i] - i
suf[i][0] = a[i] + i
预处理 x[i] = floor(log2 i)（递推：x[i] = x[i/2]+1），供 RMQ 用
三层稀疏表构建：对 j=1..20，区间 [i, i+2^j-1] 的最小值 = 左半 [i, i+2^(j-1)-1] 和右半 [i+2^(j-1), i+2^j-1] 的最小值
now：一个"双指针"左端点边界（单调不减），初始为 1。
ans：全局最优代价，初始 inf
now 单调前进：当 now <= i 且 2*now - a[now] <= i 时，now++。条件 2*now - a[now] <= i 可写成 now - (a[now]-now) <= i，即 a[now] - now >= now - i 反向看……让我解释常用语义：

这在**「灯塔/覆盖跳到末尾」类问题中通常表达：位置 now 若以其"右端能力"（与 a[now]+now 相关）能覆盖到更右边，就往前收。这里用 now*2 - a[now] <= i 作为"位置 now 可以作为某个覆盖左端点的下界**"的判断——把 pre[now] = a[now]-now 反代：now*2 - a[now] = now - (a[now]-now) = now - pre[now]。所以条件是 now - pre[now] <= i，也就是"用 now 处的 a[now]-now 值，映射出的一个位置不超过 i"。

具体它对应哪种贪心取决于原题，但结构性作用很清晰：now 是满足某单调条件的最左可行边界，随 i 单调右移（双指针）。
确定"分割点" pos：

若 now <= i，直接 pos = now（现成的边界）；
否则在 [i, n] 上二分：找一个最小的 mid 使得区间 [i, mid] 的原生最小值 < i（即区间内存在某个 a[x] < i，x 在 [i,mid]）。找到的 mid 作为 pos；找不到（pos==-1）就跳过本次 i。
语义：pos 是 "在 [i, pos] 中存在一个 a[x] < i 的最左位置"——暗示从 i 出发能"借助某个更左的强点"到达的位置分界
按 pos 与 i 的关系分两种情况，计算代价对 (xx, y)，取 max，再对全局取 min：

情况 A（pos ≤ i）‍：

xx = qryp(1, pos-1) + i：在 [1, pos-1] 里取 a[x]-x 的最小值，再加 i。→ 表示"左侧部分的最小 'a[x]-x' 贡献，调整为以 i 为基准的代价"。
y = min(qryp(pos,i)+i, qrys(i+1,n)-i)：取 [pos,i] 的 a[x]-x 最小值 +i，与 [i+1,n] 的 a[x]+x 最小值 −i，两者较小的那一个。
组合代价 = max(xx, y)（取两个方向的较大值，类似"最坏单边开销"）。
情况 B（pos > i）‍：

xx = qrys(pos,n) - i：在 [pos,n] 取 a[x]+x 最小值再 −i。
y = min(qryp(1,i)+i, qrys(i+1,pos-1)-i)：同样取左/中前段的 a[x]-x 与 [i+1,pos-1] 的 a[x]+x 的较小者。
组合代价同取 max(xx,y)
若 ans 仍接近 inf（无解），输出 -1；否则输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5, inf = 1e9;

int x[N], mn[N][25];
inline int query(int l, int r) {
    if (l > r) return inf;
    int k = x[r-l+1];
    return min(mn[l][k], mn[r-(1<<k)+1][k]);
}

int pre[N][25];
inline int qryp(int l, int r) {
    if (l > r) return inf;
    int k = x[r-l+1];
    return min(pre[l][k], pre[r-(1<<k)+1][k]);
}

int suf[N][25];
inline int qrys(int l, int r) {
    if (l > r) return inf;
    int k = x[r-l+1];
    return min(suf[l][k], suf[r-(1<<k)+1][k]);
}

int n, a[N];
int main() {
    fast;
    cin>>n;
    for (int i = 1; i <= n; i++) {
        cin>>a[i];
        mn[i][0] = a[i]; pre[i][0] = a[i] - i; suf[i][0] = a[i] + i;
    }
    for (int i = 2; i <= n; i++) x[i] = x[i>>1] + 1;
    for (int j = 1; j <= 20; j++) {
        for (int i = 1; i <= n-(1<<j)+1; i++) {
            mn[i][j] = min(mn[i][j-1], mn[i+(1<<(j-1))][j-1]);
            pre[i][j] = min(pre[i][j-1], pre[i+(1<<(j-1))][j-1]);
            suf[i][j] = min(suf[i][j-1], suf[i+(1<<(j-1))][j-1]);
        }
    }
    int now = 1, ans = inf;
    for (int i = 1; i <= n; i++) {
        while (now <= i && now*2-a[now] <= i) now++;
        int xx, y, pos = -1;
        if (now <= i) pos = now;
        else {
            int l = i, r = n;
            while (l <= r) {
                int mid = (l+r)>>1;
                if (query(i,mid) < i) { pos = mid; r = mid-1; }
                else l = mid+1;
            }
            if (!~pos) continue;
        }
        if (pos <= i) {
            xx = qryp(1,pos-1) + i;
            y = min(qryp(pos,i)+i, qrys(i+1,n)-i);
        } else {
            xx = qrys(pos,n) - i;
            y = min(qryp(1,i)+i, qrys(i+1,pos-1)-i);
        }
        ans = min(ans, max(xx, y));
    }
    cout << (ans >= inf/2 ? -1 : ans) << '\n';
    return 0;
}