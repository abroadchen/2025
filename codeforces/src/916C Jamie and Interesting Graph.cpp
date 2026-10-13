//
// Created by Psy.C on 2026/10/13.
//
/**
从 n+1 开始向上枚举，试除法判断是否为质数，找到第一个质数并记为 p。这个 p 将作为最短路的长度
先输出 n m 所在行的头两个数——这里输出 p p，分别是图的边数声明和后面的参数（不同题目略有差异，但这里把它作为"要用的边数上限/总长度"信息
构造一条从 1 到 n 的简单路径（链）‍作为最短路树：

边 (i, i+1)（i=1..n-2）权值为 1，共 n-2 条，长度累计 n-2；
最后边 (n-1, n) 权值为 p-n+2，使整条链长度 = (n-2) + (p-n+2) = p，恰好是质数【注：保证 p ≥ n，故 p-n+2 ≥ 2 为正】。
这条链就是从 1 到 n 的最短路，其长度 = 质数 p。

m -= n-1：从需要的总边数中扣掉链上的 n-1 条边，剩下的 m 条边用来"加边"填充图
在剩下的点对 (i, j)（j ≥ i+2，即不相邻的顶点对）上加边，每条权值设为很大的 999999999。这样这些边不会影响 1 到 n 的最短路（因为最短路已经是长度 p 的链，走这些大权边只会更长）。

循环持续到累计输出 m 条额外边为止（m 在循环中递减）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, m, p;
int main() {
    fast;
    cin >> n >> m;
    for (int i = n+1; 1; ++i) {
        bool flg = 1;
        for (int j = 2; j*j <= i; ++j)
            if (i%j == 0) { flg = 0; break; }
        if (flg) { p = i; break; }
    }
    cout << p << ' ' << p << '\n';
    for (int i = 1; i < n-1; ++i) cout << i << ' ' << i+1 << " 1\n";
    cout << n-1 << ' ' << n << ' ' << p-n+2 << '\n';
    m -= n-1;
    for (int i = 1; i <= n; ++i)
        for (int j = i+2; j <= n && m; ++j, --m)
            cout << i << ' ' << j << " 999999999\n";
    return 0;
}