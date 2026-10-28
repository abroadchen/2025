//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
a[N]：存读入的数（12e5+5 ≈ 1200005，容量很大）。
m：map<int,int>，记录每个数值出现了几次（计数器哈希表）。
ans：最终答案，统计"孤独"（无配对数）的个数。
边读边把每个数放进 map 计数
(1) --m[a[i]]：先把 a[i] 自己的计数减 1。这是为了防止"自己和自己配对"时把同一个下标算进去——不过本题某些语义下其实允许自己配自己（比如 a[i]+a[i]=2^q）。这里暂时把它视为不参与（题目要求的是"与另一个数配对"，所以先排除自身）。等判断完再 ++ 恢复。

(2) 找起始幂指数 q
循环找最小的 q 使得 2^q > a[i]。这样保证从 q 开始，2^q - a[i] 是正数（因为 2^q > a[i]），可作为合法的补数去查找
(3) flg = true：先默认"没能配对"。

(4) 枚举所有可能的幂指数
对每个 q（从刚才找到的 q 一直到 30，即 2^q 最高枚举到 2^30，约 10.7 亿），计算补数 (1<<q)-a[i]，看它在 map 里的计数是否非零（存在这样的数）。只要存在任何一个 q 使补数存在于数组中，就把 flg 置为 false（说明 a[i] 能配对）。

上限 30 是为了覆盖 2 的幂到约 10 亿，匹配题目给出的数值范围（通常 ≤ 1e9）
(5) 若仍为 true：说明所有可能的 q 都找不到配对数，a[i] 是一个"孤独"的数，ans++。

(6) ++m[a[i]]：判断完一个数后，恢复它在 map 里的计数，继续处理下一个数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=(n); ++i)
using namespace std;

constexpr int N = 12e5+5;

int n, i, a[N], ans;
map<int, int> m;
int main() {
    fast;
    cin >> n;
    rep(i,n) { cin >> a[i]; ++m[a[i]]; }
    rep(i,n) {
        --m[a[i]];
        int q = 0;
        while (1<<q <= a[i]) ++q;
        bool flg = true;
        for (; q <= 30; ++q)
            if (m[(1<<q)-a[i]]) flg = false;
        if (flg) ++ans;
        ++m[a[i]];
    }
    cout << ans << '\n';
    return 0;
}