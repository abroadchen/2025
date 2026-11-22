//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
N：数组大小上限。
inf = -0U>>2：无符号 0 取反再右移 2，即 (1<<30)-1 ≈ 10^9 量级，用作"较大但不过大"的哨兵值。
INF = -0U>>1：(1<<31)-1，即 INT_MAX，哨兵最大值
n：元素个数。
m：读入但（在代码里似乎没用到）‍。
k：关键参数（第 k 大差分相关）。
a[i]：原数组。
d[i]：差分数组（相邻元素之差）。
ans：最终答案
读入 n、m、k。
读入 a，并同时计算差分 d[i] = a[i] - a[i-1]（a[0]=0，未初始化，故 d[1] = a[1]-a[0]）。
把 d[1] 强制改成 -inf（置为一个很小的值，让第一项差分不参与后面的正常比较/取第 k 大统计）
对差分数组 d[1]..d[n] 从大到小排序（greater<>() 降序）。因为 d[1] 被设为 -inf，会排到最末尾。
排序后，d[k-1] 就是第 k 大的差分值（数组下标从 1 开始，降序下标 k-1 对应第 k 大）
这里有个细节：d[1] 被改成 -inf 后排在最后，所以"前 k 大的差分"实际是 d[1..k] 原本的值，d[k-1] 索引排序后在"前 k-1 个"加上 d[1] 修改，需要理解成"以 d[k-1] 作为阈值"
l, r：滑动窗口左右端点（当前尝试的区间 [l, r]）。
q：统计变量。
d[0] = INF：把数组 0 号位置设为极大值做哨兵。
统计：在 i = k..n 范围内，有多少个差分的值等于 d[k-1]（即等于第 k 大的差分值）。
q 记录这些"重复出现的第 k 大值"的数量。
bool flg = 1;：默认标记"本轮无法继续扩展右端点"。
if (r < n)：若右端点还没到末尾。
int t = a[r+1]-a[r];：计算下一个差分值（区间 [r, r+1] 的差）。
if (q > 0 && t <= d[k-1])：当仍需消耗 q 且下一个差分 t 不大于阈值第 k 大值时，可以扩展：
else if (q <= 0 && t < d[k-1])：当 q 已消耗完（为 0）且 t < d[k-1]（严格小于阈值）时，也可以继续扩展：
这两种情况都是"能扩展右端点"，相当于窗口继续向右生长，且保证某性质成立
if (flg)：若本不能扩展（flg 仍为 1），则结算当前窗口：
即遇到不能继续扩展的位置，就把这段区间长度累加入答案，然后从头（新的单点）重新开窗口。
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

constexpr int N = 1e5+10, inf = ~0U>>2, INF = ~0U>>1;
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
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n, m, k, a[N], d[N];
ll ans;
int main() {
    read(n); read(m); read(k);
    for (int i = 1; i <= n; i++) read(a[i]), d[i] = a[i] - a[i-1];
    d[1] = -inf;
    sort(d+1, d+n+1, greater<>());
    int l = 1, r = 1, q = 0; d[0] = INF;
    for (int i = k; i <= n; i++) q += d[i] == d[k-1];
    while (l <= r && r <= n) {
        bool flg = 1;
        if (r < n) {
            int t = a[r+1] - a[r];
            if (q > 0 && t <= d[k-1]) q -= t == d[k-1], ++r, flg = 0;
            else if (q <= 0 && t < d[k-1]) ++r, flg = 0;
        }
        if (flg) ans += a[r]-a[l]+1, l = ++r;
    }
    write(ans);
    return 0;
}