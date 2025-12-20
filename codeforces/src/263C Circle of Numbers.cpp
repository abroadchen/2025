//
// Created by Psy.C on 2025/12/20.
//

#include <iostream>
#include <map>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200010
using namespace std;


int main() {
    fast;
    int n; cin>>n;
    vector<int> e[N], ans; map<int, bool> vis[N];
    for (int i = 0, x, y; i < n<<1; ++i) {
        cin>>x>>y;
        e[x].push_back(y); e[y].push_back(x);
        vis[x][y] = true; vis[y][x] = true;
    }
    for (int i = 1; i <= n; ++i) if (e[i].size() != 4) {
        cout << "-1\n"; return 0;
    }
    for (int start = 1; start <= n; ++start) {
        bool tag[N] = {}; ans.clear();
        int x = start, y = start; bool ok = true;
        for (int i = 0; i < n; ++i) {
            tag[x] = true; ans.push_back(x);
            if (i + 1 == n) break;
            bool flag = false;
            for (int j = 0; j < 4; ++j) {
                int cur = e[x][j];
                if (tag[cur]) continue;
                if (vis[y][cur]) { y = x; x = cur; flag = true; break; }
            }
            if (!flag) { ok = false; break; }
        }
        if (ok) {
            for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
            cout << '\n';
            return 0;
        }
    }
    cout << "-1\n";
    return 0;
}