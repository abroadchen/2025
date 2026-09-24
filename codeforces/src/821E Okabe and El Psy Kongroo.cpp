//
// Created by Psy.C on 2026/9/23.
//
/**
add 是快速取模加法：先 x += y - mod，再若结果为负（x>>31 为负数的符号位）则加回 mod，避免每次用 % 的除法开销。这是常见的 mod 加法优化
矩阵最大 20×20（因为 sz ≤ 19 左右，c+1）。
乘法用 ikj 循环序优化缓存，标准矩阵乘，模下运算。
标准二进制快速幂，初始为单位矩阵
初始 ja.a[1][1] = 1（起点态为 1）。

对每一段 (a, b, c)：

len = min(b, k) - a：这一段持续的步数（截断到 k）。
sz = c + 1：这段的状态数维度（状态 0..c，共 c+1 个）。
构造转移矩阵 t：三对角全 1——t.a[j][j-1] = t.a[j][j] = t.a[j][j+1] = 1，含义是从状态 j 可以转移到 j-1, j, j+1（一步走相邻一格，含原地）。
ja = ja * (t^len)：该段走 len 步的转移矩阵幂，连乘进累计矩阵。
最后输出 ja.a[1][1]（从状态 1 回到状态 1 的路径数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int mod = 1e9+7;
inline void add(int& x, int y) {
    x += y - mod;
    x += (x>>31)&mod;
}

struct mtx {
    int a[20][20]{};
    mtx() { memset(a, 0, sizeof(a)); }
} ja;
int sz;
inline mtx operator*(const mtx& A, const mtx& B) {
    mtx C;
    for (int k = 1; k <= sz; ++k)
        for (int i = 1; i <= sz; ++i)
            for (int j = 1; j <= sz; ++j)
                add(C.a[i][j], 1ll*A.a[i][k] * B.a[k][j]%mod);
    return C;
}
inline mtx operator^(mtx A, int k) {
    mtx b;
    for (int i = 1; i <= sz; ++i) b.a[i][i] = 1;
    while (k) {
        if (k&1) b = b*A;
        A=A*A;
        k >>= 1;
    }
    return b;
}

int n, k, len;
signed main() {
    fast;
    cin >> n >> k; ja.a[1][1] = 1;
    for (int i = 1, a, b, c; i <= n; ++i) {
        cin >> a >> b >> c;
        len = (b > k ? k : b) - a, sz = c + 1;
        mtx t;
        for (int j = 1; j <= sz; ++j)
            t.a[j][j-1] = t.a[j][j] = t.a[j][j+1] = 1;
        ja = ja*(t^len);
    }
    cout << ja.a[1][1];
    return 0;
}