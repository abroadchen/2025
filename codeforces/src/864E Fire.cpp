//
// Created by Psy.C on 2026/10/4.
//
/**
t[i]：完成所需时长
d[i]：截止时间（该任务必须在时间 d 之前开始/完成）
p[i]：完成所得价值
把所有任务按截止时间 d 升序排序。这是 01 背包附加"截止时间"约束的标准处理方式——按截止时间排序后，DP 的状态可以表示"在时间 j 内能拿到多少价值"
dp[i][j]：考虑前 i 个任务，总用时为 j 时能获得的最大价值。这是标准的 01 背包：

不选第 i 个任务：dp[i-1][j]
选第 i 个任务：dp[i-1][j - t[i]] + p[i]
但这里有个关键约束：截止时间。第 i 个任务要求"在它自己的截止时间 d[i] 之前完成"，所以枚举时间 j 时，只枚举到 j < a[i].d（即 j 严格小于该任务的截止时间，保证这个任务能在截止前被安排进去）。

转移逻辑：若 j < t[i]（时间不够完成任务）或"不选"价值 ≥ "选"价值，就维持 dp[i-1][j]（不选）；否则选它：dp[i-1][j-t[i]]+p[i]，并标记 vis[i][j]=1 表示"在状态 (i,j) 选了第 i 个任务"（用于回溯）
在所有可能的用时 j（0 到 sum）里，找出使 dp[n][j] 最大的那个时间 t，dp[n][t] 就是最大总价值
从 (n, t) 往回走到 (1, ...)：如果 vis[i][j]==1 说明取了第 i 个任务，就把它编号压栈、用时减去 t[i]（j -= a[i].t，回到选它之前的状态）。同时计数器 len 记录选了几个任务。

由于用了栈，输出时任务编号是倒序（实际被选中的任务集合），按 do 顺序输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 107, M = 2007;
struct node { int t, d, p, id; } a[N];
bool cmp(node x, node y) { return x.d < y.d; }
int sum, ans, dp[N][M];
bool vis[N][M];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].t >> a[i].d >> a[i].p; a[i].id = i;
    }
    sort(a+1, a+n+1, cmp);
    sum = a[n].d;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < a[i].d; ++j) {
            if (j < a[i].t || dp[i-1][j] >= dp[i-1][j-a[i].t]+a[i].p)
                dp[i][j] = dp[i-1][j];
            else {
                dp[i][j] = dp[i-1][j-a[i].t] + a[i].p;
                vis[i][j] = 1;
            }
        }
    }
    int t = 0, len = 0;
    for (int i = 1; i <= sum; ++i)
        if (dp[n][i] > dp[n][t]) t = i;
    cout << dp[n][t] << '\n';
    stack<int> s;
    for (int i = n, j = t; i >= 1; --i) {
        if (vis[i][j]) {
            s.push(a[i].id); len++;
            j -= a[i].t;
        }
    }
    cout << len << '\n';
    while (!s.empty()) { cout << s.top() << ' '; s.pop(); }
    cout << '\n';
    return 0;
}