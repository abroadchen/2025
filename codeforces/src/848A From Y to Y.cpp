//
// Created by Psy.C on 2026/9/28.
//
/**
N = 2e5+5：x 数组容量上限（虽然 inf=1000 已够用）。
inf = 1e3（即 1000）：x 数组的有效长度上限，也是"段长 c"的最大值。
读入 n。
cur = 97：初始字母的 ASCII 码 = 'a'（97），每用一段就 cur++，得到连续字母 a,b,c,...。
x[N]：存三角数表。
c：当前要用的段长。
特判 n == 0：直接输出 "ab"。这是题目的边界情况——当 n=0 时（可能表示"0 个需要计数的子串"），固定输出 "ab"。这个特判需结合原题确认。
预计算 x[i] = i*(i-1)/2 对 i = 1..1000。
数值：x[1]=0, x[2]=1, x[3]=3, x[4]=6, x[5]=10, ...，也就是三角数序列 0,1,3,6,10,15,...。
这里是 C(i,2)（组合数"从 i 个里选 2 个"），作用是：一段长度为 i 的同字母串能贡献的子串数是 i*(i+1)/2 吗？ —— 注意这里用的是 i*(i-1)/2 而不是 i*(i+1)/2，说明对"子串计数"的定义包含某种"减 i"或"从 0 开始数"的约定，需结合原题。但代码统一用它做"能减掉的最大值"查找
循环直到 n 减为 0：
upper_bound(x+1, x+inf+1, n)：在 x[1..inf] 里找第一个大于 n 的位置，再 -1 得到"最后一个 ≤ n"的下标 c。即在三角数表里找出不超过 n 的最大三角数 x[c]，其索引就是当前段长 c。
输出 c 个当前字母 cur（一段同字母，长度 c）。
n -= x[c]：从 n 里减去这段贡献的子串数。
cur++：换下一个字母（a→b→c→...）。
如此反复，n 逐步减小，每段用一个新字母，直到 n 归零
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5, inf = 1e3;

template <typename T>
static T rd() {
    T f = 0, ch = 0; T x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    fast;
    ll n = rd<ll>(), cur = 97, x[N], c;
    if (!n) return cout << "ab\n", 0;
    for (int i = 1; i <= inf; ++i) x[i] = i*(i-1)/2;
    while (n) {
        c = upper_bound(x+1, x+inf+1, n) - x - 1;
        for (int i = 1; i <= c; ++i) putchar(cur);
        n -= x[c], cur++;
    }
    return 0;
}