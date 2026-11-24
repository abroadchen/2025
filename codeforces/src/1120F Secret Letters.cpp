//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
n：点数；c：某种单位代价（这里是"移动 1 单位坐标"的代价）；d：另一种固定代价（"更换/切换"一次）。
每个点给定坐标 a[i] 和颜色标记 op[i]。
a[n+1] 是终点（哨兵），标记强制设为 'A'
ans 初值 n*d：最坏情况——每个点都单独切换一次，代价 n×d。
lst 记录"下一个不同颜色点的坐标"（用于计算连续同色段不经切换的移动代价）。
sum 累计"从当前位置到最后，切换到不同颜色所需的后缀最小切换代价"
同色段内：op[i] == op[i+1]
若相邻两个点同色，则"从 i+1 走到 i"不必重新切换，可以只付"移动 i+1→i 这段的颜色保持"，代价取 min(d, (lst - a[i+1])*c)——即在"重新切换一次 d"和"从段尾 lst 按移动代价 c 一路同色走"之间取便宜者，累加入 sum。
异色处：else lst = a[i+1]
相邻不同色时更新"最近一个异色段的段尾坐标" lst，以便后续统计同色连续段。
更新答案：
(a[n+1]-a[i])*c：从 i 点把所有剩余（含终点）按移动代价走到位。
+ sum：加上后缀最省切换代价。
+ d*(i-1)：前面 i−1 个点每个都要至少切换一次，代价 d*(i-1)。
综合出"若在 i 处"一刀切"后各点处理"的最小代价，取 min 到 ans。
输出全局最小总代价
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 1e5+5;
int n, c, d, a[N], ans;
char op[N];
signed main() {
    fast;
    cin >> n >> c >> d;
    for (int i = 1; i <= n; i++) cin >> a[i] >> op[i];
    cin >> a[n+1]; op[n+1] = 'A'; ans = n*d;
    int lst = a[n+1], sum = 0;
    for (int i = n; i >= 1; i--) {
        if (op[i] == op[i+1]) sum += min(d, (lst-a[i+1])*c);
        else lst = a[i+1];
        ans = min(ans, (a[n+1]-a[i])*c+sum+d*(i-1));
    }
    cout << ans << '\n';
    return 0;
}