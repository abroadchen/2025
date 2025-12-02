//
// Created by Psy.C on 2025/12/2.
//O(n²m²)，因为对每个点都要做一次DFS

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

constexpr int N = 55;
int n, m, vis[N][N], cnt = 0;
string s[N];//存储网格

void dfs(const int i, const int j) {
    vis[i][j] = 1; cnt++;
    if (i+1 < n && s[i+1][j] == '#' && vis[i+1][j] == 0) dfs(i+1, j);
    if (j+1 < m && s[i][j+1] == '#' && vis[i][j+1] == 0) dfs(i, j+1);
    if (i-1 >= 0 && s[i-1][j] == '#' && vis[i-1][j] == 0) dfs(i-1, j);
    if (j-1 >= 0 && s[i][j-1] == '#' && vis[i][j-1] == 0) dfs(i, j-1);
}

int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> s[i];
    rep(i,n) rep(j,m) vis[i][j] = 0;
    int ans = 2, tot = 0;
    rep(i,n) rep(j,m) if (s[i][j] == '#') tot++;//统计网格中'#'的总数
    if (tot <= 2) { cout << "-1"; return 0; }//移除任何一个都会使图不连通
    rep(i,n) rep(j,m) if (s[i][j] == '#') {//遍历网格中的每个'#'位置
        rep(k,n) rep(l,m) vis[k][l] = 0;//重置访问数组
        cnt = 0; s[i][j] = '.';//重置计数器，将当前位置标记为'.'（模拟移除）
        if (i+1 < n && s[i+1][j] == '#') dfs(i+1, j);
        else if (j+1 < m && s[i][j+1] == '#') dfs(i, j+1);
        else if (i-1 >= 0 && s[i-1][j] == '#') dfs(i-1, j);
        else if (j-1 >= 0 && s[i][j-1] == '#') dfs(i, j-1);
        if (cnt != tot - 1) ans = 1;//移除该点会使图不连通
        s[i][j] = '#';//恢复当前位置为'#'
    }
    cout << ans << '\n';
    return 0;
}