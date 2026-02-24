//
// Created by Psy.C on 2026/2/24.
//
/**
n, m：物品数量和查询数量
a[i], b[i], c[i]：第i个物品的重量、价值、出现时间
s[N], sn：栈s和栈顶指针
t[N], tn：栈t和栈顶指针
d[N][N]：动态规划数组（正向）
e[N][N]：动态规划数组（反向）
r[M]：结果数组
f[i]存储在时间i出现的物品编号
(时间, 容量, 查询编号)

正数表示物品出现
负数表示物品消失（时间偏移m）

按时间顺序处理每个时刻
处理在时刻i发生的所有事件
如果是物品出现事件（正数）
将物品加入栈s
复制前一状态的DP值
更新DP状态：考虑是否选择当前物品
如果是物品消失事件（负数）
如果栈t为空，需要重建
将栈s的物品转移到栈t
复制前一状态的DP值
更新反向DP状态
移除栈顶物品
移除已处理的事件

处理所有在时刻i的查询
枚举容量分配方案，取最大值

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 4001, M = 20000;
int n, m, a[N], b[N], c[N], s[N], sn, t[N], tn, d[N][N], e[N][N], r[M];
vector<int> f[M+1];
pair<ii,int> q[M];
int main() {
    fast;
    cin >> n >> m;
    int i, j;
    for (i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
        f[c[i]].push_back(i);
        f[c[i]+m].push_back(-i);
    }
    cin >> m;
    for (i = 0; i < m; ++i) {
        cin >> q[i].first.first >> q[i].first.second;
        q[i].second = i;
    }
    sort(q, q+m); n = 0;
    for (i = 1; i <= M; ++i) {
        while (f[i].size()) {
            if (f[i][f[i].size()-1] > 0) {
                s[++sn] = f[i][f[i].size()-1];//获取时间点i的最新事件
                for (j = 0; j <= N-1; ++j)
                    d[sn][j] = d[sn-1][j];
                for (j = a[s[sn]]; j <= N-1; ++j)
                    d[sn][j] = max(d[sn][j], d[sn-1][j-a[s[sn]]]+b[s[sn]]);
            } else {
                if (!tn) {
                    while (sn) {
                        t[++tn] = s[sn--];
                        for (j = 0; j <= N-1; ++j)
                            e[tn][j] = e[tn-1][j];
                        for (j = a[t[tn]]; j <= N-1; ++j)
                            e[tn][j] = max(e[tn][j], e[tn-1][j-a[t[tn]]]+b[t[tn]]);
                    }
                }
                tn--;
            }
            f[i].pop_back();
        }
        while (q[n].first.first == i) {
            for (j = 0; j <= q[n].first.second; ++j)
                r[q[n].second] = max(r[q[n].second], d[sn][j]+e[tn][q[n].first.second-j]);
            n++;
        }
    }
    for (i = 0; i < n; ++i) cout << r[i] << '\n';
    return 0;
}