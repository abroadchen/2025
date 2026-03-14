//
// Created by Psy.C on 2026/3/13.
//
/**
检查坐标(x,y)是否在网格范围内
检查两点之间的距离是否为1（相邻）
并且要求第一个点不能在第二个点的右下方
s：存储网格字符
dp：动态规划数组
dp2：临时数组
ans：最终答案
如果起点和终点字符相同，初始化dp[1][n]=1

遍历曼哈顿距离相同的对角线
对于每一对位置，尝试四种转移方式（两个点分别向右或向下移动）
如果字符匹配，更新dp2数组
更新dp数组，清空dp2数组
检查是否到达终点附近，如果是则计入答案

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;
constexpr int N = 505, mod = 1e9+7;

int n, m;
bool ok(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

bool check(int x1, int y1, int x2, int y2) {
    if (abs(x2 - x1) + abs(y2 - y1) > 1) return false;
    if (x1 > x2 || y1 > y2) return false;
    return true;
}

char s[N][N];
int dp[N][N], dp2[N][N], ans;
signed main() {
    fast;
    cin >> n >> m;
    rep(i,n) rep(j,m) cin >> s[i][j];
    if (s[1][1] == s[n][m]) dp[1][n] = 1;
    rep(a,n+m) {
        rep(i,n) rep(j,n) {
            int x = i, y = a - x + 1, x2 = j, y2 = m - (a - (n - x2)) + 1;
            if (!ok(x, y) || !ok(x2, y2)) continue;
            if (s[x][y+1] == s[x2][y2-1]) dp2[x][x2] += dp[x][x2];
            if (s[x][y+1] == s[x2-1][y2]) dp2[x][x2-1] += dp[x][x2];
            if (s[x+1][y] == s[x2][y2-1]) dp2[x+1][x2] += dp[x][x2];
            if (s[x+1][y] == s[x2-1][y2]) dp2[x+1][x2-1] += dp[x][x2];
        }
        rep(i,n) rep(j,n) {
            dp[i][j] = dp2[i][j] % mod; dp2[i][j] = 0;
            int x = i, y = a - x + 2, x2 = j, y2 = m - (a - (n - x2));
            if (!ok(x, y) || !ok(x2, y2)) continue;
            if (check(x, y, x2, y2)) { ans += dp[i][j]; ans %= mod; }
        }
    }
    cout << ans << '\n';
    return 0;
}