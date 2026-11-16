//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
dp[i][j][x][y]：状态 = 第一方总分 i、第二方总分 j、当前已有 x 局第一方赢、y 局第二方赢，值为 是否可达。
a[] / b[]：预定义若干"胜局数"组合，对应比赛可能是五局三胜（先赢 3 局）‍或三局两胜等情形，用来匹配查询。
ans[i][j][x][y]：若该状态可达，记录路径上的每一局比分（(一,二) 对）
0:0 开局，0 局已打，可达
四层循环枚举：当前总分 i、j、胜局数 x、y（x,y 只到 2，因为"先赢 3 局获胜"，到达 3 局就结束）。

本局阈值 mx：

若已是 2:2（双方各赢 2 局），本局为决胜局，需要 15 分胜（mx=15）；
否则本局通常为 25 分胜（mx=25）。
这就是乒乓球规则的体现：先得 25 分者胜，若 2:2 打满则第 5 局到 15 分（或者这里是"非决胜局 25、决胜局 15"的设定）
本局若一方得分到 mx（而对方只到 c，c < mx），直接判定该方赢本局。枚举输方得分 c = 0..mx-3（即不出现 mx-1 等直接获胜的分差，区分的注：因为只枚举到 mx-2，另一端的分差被控制，避免与"平分加时"重叠）。

两种方向都尝试（本方赢 / 对方赢），更新 DP 并保存路径
乒乓球"平分加时"规则：当比分到 mx-1 (24:24) 时，需净胜 2 分才赢。这里枚举 c≥mx-1，一方得 c 另一方得 c+2（差 2 分），判定高的一方赢本局
对每个查询的总比分 n:m：

遍历 6 种预设的胜局组合 (a[i], b[i]) = (3,0),(3,1),(3,2),(2,3),(1,3),(0,3)（即五局三胜的各类比分，从 3:0 到 3:2、再到 2:3、0:3、1:3）。
若 dp[n][m][a[i]][b[i]] 可达，说明"打了 a[i] 局第一方赢、b[i] 局第二方赢"是合法的，输出这一行胜局数，再按 ans 路径逐局打印每局比分。
找不到则输出 Impossible
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<=n; i++)
#define ii pair<int,int>
using namespace std;

constexpr int N = 205;

int dp[N][N][4][4], a[] = {3,3,3,2,1,0}, b[] = {0,1,2,3,3,3};
vector<ii> ans[N][N][4][4];
int main() {
    fast;
    dp[0][0][0][0] = 1;
    rep(i,N-5) rep(j,N-5) rep(x,2) rep(y,2) {
        if (!dp[i][j][x][y]) continue;
        int mx;
        if (x == 2 && y == 2) mx = 15; else mx = 25;
        rep(c,mx-2) {
            if (i+mx <= N-5 && j+c <= N-5 && !dp[i+mx][j+c][x+1][y]) {
                dp[i+mx][j+c][x+1][y] = 1, ans[i+mx][j+c][x+1][y] = ans[i][j][x][y];
                ans[i+mx][j+c][x+1][y].emplace_back(mx,c);
            }
            if (i+c <= N-5 && j+mx <= N-5 && !dp[i+c][j+mx][x][y+1]) {
                dp[i+c][j+mx][x][y+1] = 1, ans[i+c][j+mx][x][y+1] = ans[i][j][x][y];
                ans[i+c][j+mx][x][y+1].emplace_back(c, mx);
            }
        }
        for (int c = mx-1; c <= N-5; c++) {
            if (c+j+2 <= N-5 && i+c <= N-5 && !dp[i+c][j+c+2][x][y+1]) {
                dp[i+c][j+c+2][x][y+1] = 1, ans[i+c][j+c+2][x][y+1] = ans[i][j][x][y];
                ans[i+c][j+c+2][x][y+1].emplace_back(c, c+2);
            }
            if (c+i+2 <= N-5 && c+j <= N-5 && !dp[i+c+2][j+c][x+1][y]) {
                dp[i+c+2][j+c][x+1][y] = 1, ans[i+c+2][j+c][x+1][y] = ans[i][j][x][y];
                ans[i+c+2][j+c][x+1][y].emplace_back(c+2, c);
            }
        }
    }
    int T; cin >> T;
    while (T--) {
        int n, m, f = 0; cin >> n >> m;
        rep(i,5) if (dp[n][m][a[i]][b[i]]) {
            cout << a[i] << ':' << b[i] << '\n';
            rep(j,ans[n][m][a[i]][b[i]].size()-1)
                cout << ans[n][m][a[i]][b[i]][j].first << ':' << ans[n][m][a[i]][b[i]][j].second << ' ';
            cout << '\n'; f = 1;
            break;
        }
        if (!f) cout << "Impossible\n";
    }
    return 0;
}