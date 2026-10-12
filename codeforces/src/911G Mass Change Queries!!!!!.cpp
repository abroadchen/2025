//
// Created by Psy.C on 2026/10/12.
//
/**
rep(i,j)：从 i=0 循环到 j-1（j 存进 i_end_ 避免重复计算）。
ull = unsigned long long（64 位无符号整数，作为块内 64 个位置的 bitset）。
N = 2e5：数组最大长度。
B = 6：因为是 i>>6（除以 64）和 i&63，这里 B 其实对应"每块 64 个位置"，1<<B = 64。实际分块大小是 64。
L = 63：&L 即 &63，取低 6 位作为块内偏移（0..63）
n 数组个数，q 询问个数。
a[N]：存原始（及最终）值。
b[100][...]：100 种值 × 块数（N>>6 + 1 块）的 bitset 二维数组。b[val][block] 第 bit 位为 1 表示"该块中位置 bit 的值是 val"。
rd(a[i])：读第 i 个值。
--a[i]：值减 1，把值域从 1..100 变成 0..99（便于用 b[100] 索引）。
b[a[i]][i>>B] |= 1ull << (i&L)：i>>6 是所在块号，1ull << (i&63) 是该块内的位。把"位置 i 属于值 a[i]"这一位标记为 1
读 l, r, x, y，全部减 1（0 基）。l、r 转成下标，x、y 转成值编号（0..99）。
若 x == y（替换前后相同）则直接跳过本次询问（无意义）
循环条件：l <= r 且 l&63 != 0（即 l 不在块首）。逐个处理 l 位置，直到 l 对齐到块首。
b[x][l>>B]>>(l&L)&1：检查位置 l 的值是否为 x（该位是否为 1）。
若是：
b[y][l>>B] |= 1ull<<(l&L)：把 y 在该位的位设为 1。
b[x][l>>B] ^= 1ull<<(l&L)：把 x 在该位的位取反（清 0）。
效果：单点把 x 改 y。++l 前进
循环条件：l <= r 且 -r & 63 != 0（即 r 对应的位不是块内第 63 位，即 r 不在块尾）。
同上，对位置 r 做单点 x→y 替换。--r 前进
走到这里时 [l, r] 已经两端对齐到块边界，l < r 意味着中间还有整块。
对每个完整块 i（从 l>>6 到 r>>6）：
b[y][i] |= b[x][i]：把该块中所有值为 x 的位合并到 y 中。
b[x][i] = 0：把该块中 x 的位全部清空。
这就是 整块 O(1) 批量替换 的核心——不用逐位遍历，直接整块位运算。
这样，区间两端不完整的块逐位处理（最多 128 次位操作），中间完整块整块处理，总复杂度约为 O(完整块数)，远小于 O(区间长度)
双重循环枚举每种值 i 和每个位置 j：
b[i][j>>6]>>(j&63)&1：判断位置 j 的值是否为 i。
若是，把 a[j] = i（还原成 0-based 值）。
输出时 a[i] + 1：把 0..99 映射回 1..100 的原始值域，空格分隔
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define ull unsigned long long
using namespace std;

constexpr int N = 2e5, B = 6, L = 63;

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, q, a[N];
ull b[100][(N>>B)+1];
int main() {
    fast;
    rd(n);
    for (int i = 0; i < n; rd(a[i]), --a[i], b[a[i]][i>>B]|=1ull<<(i&L), ++i) {}
    rd(q);
    for (int l, r, x, y; q--;) {
        rd(l), rd(r), rd(x), rd(y); --l, --r, --x, --y;
        if (x == y) continue;
        for (; l <= r && (l&L); ++l)
            if (b[x][l>>B]>>(l&L)&1) b[y][l>>B]|=1ull<<(l&L), b[x][l>>B]^=1ull<<(l&L);
        for (; l <= r && (~r&L); --r)
            if (b[x][r>>B]>>(r&L)&1) b[y][r>>B]|=1ull<<(r&L), b[x][r>>B]^=1ull<<(r&L);
        if (l < r) {
            for (int i = l>>B; i <= r>>B; ++i)
                b[y][i]|=b[x][i], b[x][i] = 0;
        }
    }
    rep(i,100) rep(j,n) if (b[i][j>>B]>>(j&L)&1) a[j] = i;
    for (int i = 0; i < n; cout << a[i++]+1 << ' ') {}
    return 0;
}