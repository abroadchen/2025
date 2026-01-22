//
// Created by Psy.C on 2026/1/22.
//

#include <iostream>
#include <cstring>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
#define ii pair<int, int>
using namespace std;

int dp[N][N], dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0}, n, m;
char s[N][N], ch[] = {'D', 'I', 'M', 'A'};
bool ed = false, vis[N][N];
int dfs(const int x, const int y, const int f) {
    if (ed) return -1;
    if (dp[x][y] != -1) return dp[x][y];
    if (x > n || x <= 0 || y > m || y <= 0) return 0;
    if (vis[x][y]) { ed = true; return -1; }
    vis[x][y] = true;
    int a[4]={}, res = 0;
    for (int i = 0; i < 4; ++i) {
        if (int nx = x + dx[i], ny = y + dy[i]; s[nx][ny] == ch[(f+1)%4]) {
            a[i] = dfs(nx, ny, (f+1)%4);
            vis[nx][ny] = false;
            if (a[i] == -1) return -1;
        }
    }
    res = *max_element(a, a + 4);
    if (ch[f%4] == 'A') res++;
    return dp[x][y] = res;
}

int main() {
    fast;
    cin >> n >> m;
    int i;
    for (i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    queue<ii> q;
    for (i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        if (s[i][j] == 'D') {
            ii p1(i, j);
            q.push(p1);
        }
    }
    if (q.empty()) { cout << "Poor Dima!\n"; return 0; }
    int ans = -1;
    memset(dp, -1, sizeof dp);
    while (!q.empty()) {
        auto [fst, snd] = q.front(); q.pop();
        const int x = fst, y = snd, f = 0;
        ans = max(ans, dfs(x, y, f));
        if (ed) { cout << "Poor Inna!\n"; return 0; }
        vis[x][y] = false;
    }
    if (ans == 0) cout << "Poor Dima!\n"; else cout << ans << '\n';
    return 0;
}