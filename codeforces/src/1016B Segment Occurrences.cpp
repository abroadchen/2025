//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
n：主串 a 长度；m：模式串 b 长度；q：询问次数。
num[i]：标记，若 b 恰好出现在 a 的以位置 i 为起点的位置（即 a[i..i+m-1] == b），则 num[i]=1，否则 0。
flg[i]：num 的前缀和（方便区间求和）。
a：主串；b：模式串（均从下标 0 存）
读入 n、m、q、主串 a、模式串 b。
① 暴力找 b 在 a 中的每个出现起点
对每个位置 i（作为可能起点）：

先看 a[i] 是否等于 b[0]，否则直接跳过（快速剪枝）。
若相等，从 j=0 起逐个比较 a[i+j] 与 b[j]，只要发现不匹配就 break。
若 j 走满到 m（即 j==m，全程匹配），说明 a[i..i+m-1] == b，令 num[i]=1。
这是一个 O(n·m) 的朴素字符串匹配（因为没有用 KMP，只用了简单比较）。

⚠️ 注意：这里没有做 i+m <= n 的边界检查。若 i 靠近末尾导致 i+j 越界读 a 数组——但因 N 数组大小足够、且越界处读到的是 \0 或垃圾值，与 b[j] 大概率不等会触发 break，通常不会误判。严格说这是一个潜在越界小隐患，但在该数据范围（N=1001）下通常不会出错
② 构造 num 的前缀和
flg[i] = num[0]+num[1]+...+num[i]，即"b 在 a 中、以 ≤ i 为起点出现的总次数"。

这样任意区间 [L, R]（起点范围）内 b 出现次数 = flg[R] - flg[L-1]
每次读入区间 [x,y]（1-based 位置，即 a 的第 x 个字符到第 y 个字符）：

先做两个快速判断：
n < m：主串比模式串短，根本不可能包含，直接输出 0。
y-x+1 < m：区间长度小于模式串长度，显然无法容纳 b，输出 0。
否则：统计以位置 x 到 y-m+1 为起点、且 b 完整落在 [x,y] 内的出现次数。
计算 flg[y-m] - flg[x-2]：

起点范围：因为 b 长度 m，若要完整落在 [x,y] 内，起点 p 必须满足 x ≤ p 且 p+m-1 ≤ y，即 x ≤ p ≤ y-m+1（用 0-based 数组下标则是 x-1 ≤ p ≤ y-m）。
前文 flg 定义中下标 i 对应 0-based 起点 i，且 flg 也是 0-based。
区间的出现次数 = flg[y-m] - flg[x-2]：
flg[y-m] = 起点 ≤ y-m 的总次数。
减去起点 < x-1 的，即 flg[x-2]（因为 0-based 起点 x-1，其前缀是 flg[x-2]）。
这个下标计算要仔细对齐：

位置参数 x、y 是 1-based。
0-based 起点 p 从 a[x-1] 开始，即 p ≥ x-1。
p 最大可到 y-m（0-based：a[y-m] 是能容纳 b 的最后起点）。
所以出现次数 = num[x-1] + ... + num[y-m] = flg[y-m] - flg[x-2]。✓
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1001;


int n, m, q, num[N], flg[N];
char a[N], b[N];
int main() {
    fast;
    cin >> n >> m >> q >> a >> b;
    for (int i = 0; i < n; i++) if (a[i] == b[0]) {
        int j = 0;
        for (; j < m; j++) if (a[i+j] != b[j]) break;
        if (j == m) num[i] = 1;
    }
    flg[0] = num[0];
    for (int i = 1; i < n; i++) flg[i] = flg[i-1] + num[i];
    while (q--) {
        int x, y; cin >> x >> y;
        if (n < m || y-x+1 < m) cout << "0\n";
        else cout << flg[y-m]-flg[x-2] << '\n';
    }
    return 0;
}