//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
a[i] 第 i 位 0/1；s[i][j] 倍增稀疏表；c 原字符串
读长度和字符串（1 基），转数组
对每个倍率 j（块大小 2^j）：

s[i][j] 表示：从位置 i 出发、每隔 2^j 取一处，对这些采样位置上的相邻异或 (a[t]^a[t+1]) 求和。
递推式：s[i][j] = s[i+2^(j+1)][j] + (a[i]^a[i+1])，即把"i 这一层"加上"隔两块之后的层"；边界处（超出 n）取 0。
遍历 i 从 n−1 向下，倒序递推
输入可能是 0 基区间，统一转 1 基（+1）。
len = r-l+1 区间长度。
ans 累计某种"错位对"数量
i 从 len>>1 开始，每次减半；j 同步递增。i 相当于"当前拆分出的区间剩余半长"。
k = l + (1<<j) - 1：从查询左端点 l 出发，定位到该倍率下的采样起点。
x = s[k][j] - (k+len<n ? s[k+len][j] : 0)：取 s[k][j] 减去偏移 len 之后那一层的值，得到区间内、按步长 2^j 采样得到的异或计数。本质是从稀疏表中"切出"区间 [l, r] 对应的那一段。
ans += min(x, i-x)：因为最终目标是让区间内若干位变成某个标准模式，异或计数为 x 就是"不匹配的对数"，min(x, i-x) 取最少需要翻转的位数。
因为一次"修改"可能同时影响两个相邻采样位置（成对效应），所以把 ans 向上取一半：(ans+1)/2

j 决定"隔几层"（步长），i 决定"从哪个位置开始采"。
因为每一层还要继续递归往下延伸，代码一次往前跳 2 个采样间隔（2 × 2^j = 2^(j+1)）
*/
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5+10;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, a[N], s[N][18], q;
char c[N];
int main() {
    n = rd(); scanf("%s", c+1);
    for (int i = 1; i <= n; ++i) a[i] = c[i] - '0';
    int lz = log2(n);
    for (int j = 0; j < lz; ++j) for (int i = n-1; i; --i)
        s[i][j] = (i+(1<<(j+1)) <= n ? s[i+(1<<(j+1))][j] : 0) + (a[i]^a[i+1]);
    q = rd();
    while (q--) {
        int l = rd()+1, r = rd()+1, len = r-l+1, ans = 0;
        for (int i = len>>1, j = 0; i; i >>= 1, ++j) {
            int k = l+(1<<j)-1, x = s[k][j]-(k+len < n ? s[k+len][j] : 0);
            ans += min(x, i-x);
        }
        printf("%d\n", (ans+1)/2);
    }
    return 0;
}