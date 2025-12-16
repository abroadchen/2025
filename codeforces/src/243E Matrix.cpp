//
// Created by Psy.C on 2025/12/16.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
#define M 30
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;


int ans[N<<1], n, m, c[N][N], d[N][N], a[N][N], b[N][N], vis[N<<1];
vector<int> g[N<<1];
void add(const int u, const int v) {
    if (u >= 1 && u <= n + m && v >= 1 && v <= n + m) {
        g[u].push_back(v);
    }
}

bool check() {
    queue<int> q;
    for (int i = 1; i <= n + m; ++i) {
        if (!ans[i]) continue;
        memset(vis, 0, sizeof(vis));
        q.push(i); vis[i] = 1;
        while (!q.empty()) {
            const int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (v == i) return false;
                if (v >= 1 && v <= n + m && !vis[v])
                    q.push(v), vis[v] = 1;
            }
        }
    }
    return true;
}

bool ok(const int x) {
    memset(ans,0,sizeof(ans));
    for (int i = 0; i <= n + m; ++i) g[i].clear();
    rep(i,n) rep(j,m) c[i][j] = a[i][j]>>x&1;
    rep(i,n) rep(j,m) d[i][j] = b[i][j]>>x&1;
    rep(i,n) rep(j,m) {
        if (d[i][j] == 0) {
            add(n + j, i);
            if (c[i][j] == 1) ans[i] = 1;
        }
        if (d[i][j] == 1) {
            add(i, n + j);
            if (c[i][j] == 0) ans[n + j] = 1;
        }
    }
    return check();
}



int main() {
    fast;
    cin>>n>>m;
    rep(i,n) {
        string s; cin>>s;
        for (int j = 0; j < m; ++j)
            a[i][j+1] = s[j] - '0';
    }
    rep(i,n) {
        string s; cin>>s;
        for (int j = 0; j < m; ++j)
            b[i][j+1] = s[j] - '0';
    }
    bool flag = true;
    for (int i = 0; i < M; ++i) flag &= ok(i);
    flag ? cout << "Yes\n" : cout << "No\n";
    return 0;
}