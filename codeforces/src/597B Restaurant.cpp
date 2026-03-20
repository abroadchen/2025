//
// Created by Psy.C on 2026/3/20.
//
/**
st：开始时间
ed：结束时间
d[N]：存储所有区间
优先选择结束时间早的区间
p = 0：当前选择的区间索引，初始化为第0个（结束时间最早）
ans = 1：已选择的区间数，初始为1（选择了第0个区间）
for (int i = 1; i < n; ++i)：从第1个区间开始遍历
if (d[i].st > d[p].ed)：如果当前区间的开始时间 > 上一个选择区间的结束时间
说明这两个区间不重叠，可以选择当前区间
p = i：更新当前选择的区间为i
ans++：计数器加1
时间复杂度：O(n log n)（主要是排序） 空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+5;
struct node { int st, ed; } d[N];
int n;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> d[i].st >> d[i].ed;
    sort(d, d + n, [](node a, node b) {
        return a.ed < b.ed;
    });
    int p = 0, ans = 1;
    for (int i = 1; i < n; ++i)
        if (d[i].st > d[p].ed) { p = i; ans++; }
    cout << ans << '\n';
    return 0;
}