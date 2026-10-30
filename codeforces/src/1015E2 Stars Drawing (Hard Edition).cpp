//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
s：网格字符（* / .）。
q1[i][j]：(i,j) 这一行里，从它往左连续 * 的个数（横向连续段）。
q2[i][j]：(i,j) 这一列里，从它往上连续 * 的个数（纵向连续段）。
ans[i][j]：以 (i,j) 为中心的十字最终半径（0 表示没画十字）。
p1：横向差分数组，p2：纵向差分数组。
t1 / t2：行前缀和 / 列前缀和统计。
q：BFS 队列。
若该格为 .：q1=q2=0。
若为 *：
q1[i][j] = q1[i][j-1] + 1：横向连续 * 数（沿用上一格，左边连续+1）。
q2[i][j] = q2[i-1][j] + 1：纵向连续 * 数（沿上一行）。
若该点不是边缘(上下左右各留一格)，则作为潜在十字中心入队 q。
这一过程实际用 DP 递推 算出了每个点的横向、纵向连续 * 长度
每次从队列取出一个中心 (nx,ny)，尝试把半径从 ans 扩展到 nxt：

nxt = ans[nx][ny]+1：尝试把半径加 1。
检查能否扩展到半径 nxt：
q1[nx][ny+nxt] < 2*nxt+1：(nx, ny+nxt) 的横向连续 * 数若小于十字横向总长 2*nxt+1，说明横向无法容纳半径 nxt → 跳过。
q2[nx+nxt][ny] < 2*nxt+1：同理检查纵向。
二者都满足，才允许扩展。
若可扩展：更新 ans[nx][ny] = nxt，并通过差分记录该十字覆盖范围：
横向差分：p1[nx][ny-nxt]++ , p1[nx][ny+nxt+1]--（左端点+1，右端点后一格-1）。
纵向差分：p2[nx-nxt][ny]++, p2[nx+nxt+1][ny]--。
重新入队，继续尝试更大半径（因为每次扩展+1，等价于一层层 BFS 逼近该点的最大半径）。
差分技巧：一个十字横向跨越列 [ny-nxt, ny+nxt]，用 p1（行数组）在左端+1、右端之后-1，累计前缀和即得到"第 i 行每一列被多少十字横跨"。纵向同理用 p2
对每一行：

先清零 t1（行前缀数组）。
逐列计算：
t1[j] = t1[j-1] + p1[i][j]：该点被横向多少个十字覆盖（行前缀和累计差分）。
t2[i][j] = t2[i-1][j] + p2[i][j]：该点被纵向多少个十字覆盖（列前缀和）。
若 s[i][j]=='*' 且 t1[j]==0 && t2[i][j]==0：该 * 既没被横向也没被纵向覆盖 → 输出 -1 结束。
若 ans[i][j]!=0（该点有十字）→ cnt++。
这一步用 O(1) 的前缀和快速判断每个 * 是否被覆盖，避免二次暴力
第一行输出十字数量 cnt，之后输出每个非零 ans 的中心坐标和半径
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ii pair<int,int>
using namespace std;

constexpr int N = 1005;

int n, m, q1[N][N], q2[N][N], ans[N][N], p1[N][N], p2[N][N], t1[N], t2[N][N], cnt;
char s[N][N];
queue<ii> q;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) rep(j,m) {
        cin >> s[i][j];
        if (s[i][j] == '.') q1[i][j] = q2[i][j] = 0;
        else {
            q1[i][j] = q1[i][j-1] + 1, q2[i][j] = q2[i-1][j] + 1;
            if (i > 1 && j > 1 && i < n && j < m) q.emplace(i,j);
        }
    }
    while (!q.empty()) {
        int nx = q.front().first, ny = q.front().second;
        int nxt = ans[nx][ny] + 1; q.pop();
        if (q1[nx][ny+nxt] < 2*nxt+1 || q2[nx+nxt][ny] < 2*nxt+1) continue;
        ans[nx][ny] = nxt, p1[nx][ny-nxt]++, p1[nx][ny+nxt+1]--, p2[nx-nxt][ny]++, p2[nx+nxt+1][ny]--;
        q.emplace(nx, ny);
    }
    rep(i,n) {
        rep(j,m) t1[j] = 0;
        rep(j,m) {
            t1[j] = t1[j-1] + p1[i][j];
            t2[i][j] = t2[i-1][j] + p2[i][j];
            if (s[i][j] == '*' && !t1[j] && !t2[i][j]) { cout << -1; return 0; }
            if (ans[i][j]) cnt++;
        }
    }
    cout << cnt << '\n';
    rep(i,n) rep(j,m) if (ans[i][j]) cout << i << ' ' << j << ' ' << ans[i][j] << '\n';
    return 0;
}