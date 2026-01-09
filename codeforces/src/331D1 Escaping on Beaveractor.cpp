//
// Created by Psy.C on 2026/1/9.
//

#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1005
using namespace std;

int g[N][N], dx[] = {
    0, 1, 0, -1, 0
}, dy[] = {
    0, 0, 1, 0, -1
};
void add(int x1, int y1, const int x2, const int y2) {
    int dis = 0;
    if (x1 == x2) y1 < y2 ? dis = 2 : dis = 4; else {
        x1 < x2 ? dis = 1 : dis = 3;
    }
    g[x2][y2] = dis;
    while (x1 != x2 || y1 != y2) {
        g[x1][y1] = dis;
        x1 += dx[dis];
        y1 += dy[dis];
    }
}

struct node { int x, y; } a[N*N];

int main() {
    fast;
    int n, b, q; cin >> n >> b;
    for (int i = 1, x1, y1, x2, y2; i <= n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        add(x1, y1, x2, y2);
    }
    cin >> q; char s; ll t;
    map<char, int> m; m['R'] = 1; m['U'] = 2; m['L'] = 3; m['D'] = 4;
    for (int i = 1, x, y, tx, ty, vis[N][N], sum[N][N]; i <= q; ++i) {
        ll cnt = 0;
        cin >> x >> y >> s >> t;
        tx = dx[m[s]]; ty = dy[m[s]];
        while (x >= 0 && x <= b && y >= 0 && y <= b && t > 0) {
            if (g[x][y]) tx = dx[g[x][y]], ty = dy[g[x][y]];
            if (g[x][y] && vis[x][y] == i) {
                const ll ss = sum[x][y], d = cnt - ss; t %= d;
                x = a[ss + t].x, y = a[ss + t].y;
                break;
            }
            sum[x][y] = static_cast<int>(cnt);
            a[cnt].x = x, a[cnt++].y = y;
            vis[x][y] = i;
            t--;
            x += tx, y += ty;
        }
        if (x < 0) x = 0;
        if (x > b) x = b;
        if (y < 0) y = 0;
        if (y > b) y = b;
        cout << x << ' ' << y << '\n';
    }
    return 0;
}