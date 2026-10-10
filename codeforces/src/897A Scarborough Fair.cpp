//
// Created by Psy.C on 2026/10/10.
//
/**
n：字符串长度
m：操作次数
a：读入字符串（字符数组）
每次读入 4 个值：l, r, c1, c2，含义为「把区间 [l, r] 内所有等于 c1 的字符改为 c2」
l-- 把输入的1-based 下标转成 0-based 下标（因为 C++ 数组从 0 开始）
循环从 l 遍历到 r-1，即区间 [l, r]（闭区间）
对区间内每个字符，只有等于 c1 时才替换成 c2，其他字符保持不变
逐字符输出最终字符串

每次操作的暴力循环为
O
(
r
−
l
)
O(r−l)，最坏
O
(
n
)
O(n)
总复杂度
O
(
m
⋅
n
)
O(m⋅n)，在数据量小或区间短时可用
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5;

char a[N], c1, c2;
int main() {
    fast;
    int n, m; cin >> n >> m >> a;
    for (int i = 0, l, r; i < m; ++i) {
        cin >> l >> r >> c1 >> c2;
        for (l--; l < r; l++)
            if (a[l] == c1) a[l] = c2;
    }
    for (int i = 0; i < n; ++i) cout << a[i];
    return 0;
}