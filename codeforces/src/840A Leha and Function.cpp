//
// Created by Psy.C on 2026/9/26.
//
/**
node：存两个值——now（原始值）和 id（原本的下标/编号）。
cmp：按 now 从小到大排序的比较函数
读入 n。
读入数组 d[1..n]。
读入数组 c[1..n]，并把每个元素的下标 i 存到 c[i].id
d 按值从小到大排序。
c 按值从小到大排序
对 c 中第 i 小的元素（c[i]），给它分配 d 中第 (n-i+1) 大（从大到小第 i 个）的值，即 d[n-i+1]。
也就是：把 c 中第 i 小的，配给 d 中第 i 大的——即"从小到大"与"从大到小"反序配对。
把配对结果按原下标存入 a[c[i].id]
按原下标顺序输出配对后的数组 a
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

struct node { int now, id; } c[N];
inline bool cmp(node a, node b) { return a.now < b.now; }

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int d[N], a[N];
int main() {
    fast;
    int n = rd();
    for (int i = 1; i <= n; ++i) d[i] = rd();
    for (int i = 1; i <= n; c[i].id = i, ++i)
        c[i].now = rd();
    sort(d+1, d+1+n);
    sort(c+1, c+1+n, cmp);
    for (int i = 1; i <= n; ++i) a[c[i].id] = d[n-i+1];
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    return 0;
}