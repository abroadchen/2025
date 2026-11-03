//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
读入 n×n 网格，s[i][j] 存第 (i,j) 格的字符，k 是允许把非 'a' 改成 'a' 的最大次数
dp[i][j] = 从 (1,1) 走到 (i,j)，把路上所有非 'a' 改成 'a' 所需的最少次数。
转移：取从左边或上边进入的较小者，若当前格非 'a' 则 +1（需改为 'a'）
对于一个格子，如果走到它只需 ≤ k 次改动，那么从 (1,1) 到它的整条前缀路径都可以被改成全 'a'。
我们想要改动次数花在开头（让前缀全是 'a'），让字典序更小。所以取所有满足 dp≤k 的格子中 i+j（对角线位置）最大的那些，作为"能从开头全部变 a 的最远点"集合 v
若 k=0（不能改字符），则此前 dp[1][1] 若为 1 就 >k，mx 可能仍是最小值。这里强制从 (1,1) 出发，把首个字符直接作为答案首位，mx=2
用 BFS 式队列每层处理一条对角线（i+j 相同）。
从当前层的所有可达格子出发，各自尝试向右 (x,y+1) 和向下 (x+1,y)。
在所有新格子中只保留最小字符 mn 那类格子（若它们的字符更小则重开集合，相等则并入），并标记 f[] 避免重复。
每层取到的那个最小字符 mn 就是路径在该步的最优字符，存入 ans
最远对角线之前的 mx-1 个字符：因为可以用 k 次改动把它们全改成 'a'，且开头改 'a' 字典序最小，所以直接输出 'a' 若干次。
之后输出贪心跳出每一层的最小字符 ans，构成最终字典序最小的路径串
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; ++i)
#define ii pair<int, int>
using namespace std;

constexpr int N = 2e3+5;

int n, k, dp[N][N], mx, cnt;
string a;
char s[N][N], ans[N<<1], mn;
vector<ii> v;
bool f[N][N];
queue<ii> q;
int main() {
    fast;
    cin >> n >> k; int i, j;
    rep(i,n) {
        cin >> a;
        rep(j,n) s[i][j] = a[j-1];
    }
    if (s[1][1] != 'a') dp[1][1] = 1;
    rep(i,n) rep(j,n) {
        if (i == 1 && j == 1) continue;
        if (j-1 >= 1 && i-1 >= 1) dp[i][j] = min(dp[i][j-1], dp[i-1][j]);
        else if (j-1 >= 1) dp[i][j] = dp[i][j-1];
        else if (i-1 >= 1) dp[i][j] = dp[i-1][j];
        if (s[i][j] != 'a') dp[i][j]++;
    }
    rep(i,n) rep(j,n) if (dp[i][j] <= k) {
        if (mx < i+j) {
            v.clear(); v.emplace_back(i,j);
            mx = i+j;
        } else if (i+j == mx) v.emplace_back(i,j);
    }
    if (k == 0) {
        f[1][1] = 1; v.clear(); v.emplace_back(1,1);
        ans[++cnt] = s[1][1];
        mx = 2;
    }
    for (const auto &x : v) q.push(x);
    for (i = mx; i < 2*n; i++) {
        v.clear(); mn = 'z';
        while (!q.empty()) {
            int x = q.front().first, y = q.front().second; q.pop();
            if (x+1 <= n && !f[x+1][y]) {
                if (s[x+1][y] < mn) {
                    mn = s[x+1][y]; v.clear(); v.emplace_back(x+1,y);
                    f[x+1][y] = 1;
                } else if (s[x+1][y] == mn) {
                    v.emplace_back(x+1,y);
                    f[x+1][y] = 1;
                }
            }
            if (y+1 <= n && !f[x][y+1]) {
                if (s[x][y+1] < mn) {
                    mn = s[x][y+1]; v.clear(); v.emplace_back(x,y+1);
                    f[x][y+1] = 1;
                } else if (s[x][y+1] == mn) {
                    v.emplace_back(x,y+1);
                    f[x][y+1] = 1;
                }
            }
        }
        for (const auto &x : v) q.push(x);
        ans[++cnt] = mn;
    }
    if (k) rep(i,mx-1) cout << 'a';
    rep(i,cnt) cout << ans[i];
    return 0;
}