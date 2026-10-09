//
// Created by Psy.C on 2026/10/9.
//
/**
a[i] 表示第
i
i 个位置能"覆盖"到一段区间。规则是：位置
i
i 覆盖从某个起点到
i
i 的一段区间，起点是
max
⁡
(
i
−
a
[
i
]
,
  
1
)
max(i−a[i],1)，终点是
i
i。

所以每个
i
i 对应一段区间
[
max
⁡
(
i
−
a
[
i
]
,
1
)
,

i
]
[max(i−a[i],1), i]
对每个
i
i，它的覆盖区间左端点是 L = max(i-a[i], 1)（不会小于 1，即不越界到数组左边之外），右端点是 i。
b[L] 记录"从位置 L 出发的所有区间中，能达到的最远右端点"。
用 max(b[L], i) 迭代：若多个位置
i
i 的左端点相同为
L
L，则 b[L] 保存其中最靠右的那个
i
i。
也就是说，b[L] = 左端点等于
L
L 的所有区间里右端点的最大值
维护 mx＝扫描到当前位置
i
i 时，所有已扫到区间连成的覆盖带的最远右端点。
每步 mx = max(mx, b[i])：用左端点恰好为
i
i 的区间（若有）扩展当前覆盖右边界。由于区间是连续的（左端点递增、右端点单调累积），mx 表示"从最左边（1）开始能一路连续覆盖到哪"。
if (i >= mx) 说明当前位置
i
i 不在当前连续覆盖带内（覆盖带已经断掉，最远只到 mx，而 i 超过或恰好等于它且其后是断裂点），于是这里新开一段，ans++。
关键点：因为所有左端点 L 被放进了 b[L]，从左到右扫描相当于把所有区间按左端点排序后做一次性的区间合并（贪心合并）‍，mx 就是贪心合并时当前的合并右边界。每当 i > mx 就说明出现了"洞"（一个无法被覆盖的缝隙），段数 ans 加一
输出一共分成多少段（即被覆盖区间之外，有多少个连续的"孤立/断裂"单位，等价于合并后区间的数量边界处计数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;

int a[N], b[N], mx, ans;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[max(i-a[i], 1)] = max(b[max(i-a[i], 1)], i);
    }
    for (int i = 1; i <= n; ++i) {
        mx = max(mx, b[i]);
        if (i >= mx) ans++;
    }
    cout << ans;
    return 0;
}