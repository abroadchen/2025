//
// Created by Psy.C on 2025/9/13.
//

#include <ios>
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#define N 500
#define pfs(s) printf("%s",s)
using namespace std;

int adj[N][N], dist[N][N];
bool vis[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int i = 110, j = 110, k, n, m, t;
    string s;
    cin >> s;
    n = s.length();

    memset(adj, 0, sizeof(adj));
    memset(vis, 0, sizeof(vis));

    for (k = 0; k < n; k++) {
        if (s[k] == 'R') j++;
        else if (s[k] == 'L') j--;
        else if (s[k] == 'U') i--;
        else i++;
        adj[i][j] = 1;
    }

    int ti = i, tj = j;
    i = 110, j = 110;

    queue<pair<int,int>> q;
    q.push({i, j});
    vis[i][j] = true;
    dist[i][j] = 0;


    int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
    while (!q.empty()) {
        pair<int,int> u = q.front();
        q.pop();

        for (k = 0; k < 4; k++) {
            int x = u.first + dx[k], y = u.second + dy[k];
            if (adj[x][y] && !vis[x][y]) {
                dist[x][y] = 1 + dist[u.first][u.second];
                vis[x][y] = true;
                q.push({x, y});
            }
        }
    }
    if (dist[ti][tj] == n) pfs("OK\n");
    else pfs("BUG\n");

    return 0;
}