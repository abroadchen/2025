//
// Created by Psy.C on 2026/1/5.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1610
#define M 100010
using namespace std;

int h, w, dx[] = {
    0, 0, 1, -1, 1, 1, -1, -1
}, dy[] = {
    1, -1, 0, 0, 1, -1, 1, -1
};
void bs(int f[N][N], int g[N][N]) {
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
        g[i][j] = f[i][j];
        for (int d = 0; d < 4; ++d) {
            const int tx = i + dx[d], ty = j + dy[d];
            if (i <= tx && tx < h && 0 <= ty && ty < w) {
                if (f[tx][ty] == -1) g[i][j] = -1;
            }
        }
    }
}


void mbs(int f[N][N], const int tim) {
    static int g[N][N];
    for (int i = 1; i <= tim; ++i) {
        bs(f, g);
        memcpy(f, g, sizeof(g));
    }
}

int t[N][N];
void dfs(const int x, const int y, const int col) {
    t[x][y] = col;
    for (int d = 0; d < 4; ++d) {
        const int tx = x + dx[d], ty = y + dy[d];
        if (0 <= tx && tx < h && 0 <= ty && ty < w) {
            if (t[tx][ty] == 0) dfs(tx, ty, col);
        }
    }
}

int cnt;
void fc() {
    int tim = 0;
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
        if (t[i][j] == 0) dfs(i, j, ++tim);
    }
    cnt = tim;
}

int b[N][N];
void sr(int f[N][N], int g[N][N]) {
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
        g[i][j] = max(f[i][j], b[i][j]);
        for (int d = 0; d < 4; ++d) {
            const int tx = i + dx[d], ty = j + dy[d];
            if (0 <= tx && tx < h && 0 <= ty && ty < w) {
                if (b[i][j] >= 0 && f[tx][ty] > 0)
                    g[i][j] = f[tx][ty];
            }
        }
    }
}


void msr(int f[N][N], const int tim) {
    static int g[N][N];
    for (int i = 1; i <= tim; ++i) {
        sr(f, g);
        memcpy(f, g, sizeof(g));
    }
}

int s[N][N], tot = 0;

int dfs2(const int x, const int y) {
    s[x][y] = -1;
    tot++;
    int ans = 0;
    for (int d = 0; d < 4; ++d) {
        const int tx = x + dx[d], ty = y + dy[d];
        if (0 <= tx && tx < h && 0 <= ty && ty < w) {
            if (s[tx][ty] > 0) ans = s[tx][ty];
            else if (s[tx][ty] == 0) {
                const int tp = dfs2(tx, ty);
                if (tp) ans = tp;
            }
        }
    }
    return ans;
}

int num[M] = {};
void find() {
    for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
        if (s[i][j] == 0) {
            tot = 0;
            const int tp = dfs2(i, j);
            if (tot >= 5) num[tp]++;
        }
    }
}

int main() {
    fast;
    cin >> h >> w;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> b[i][j]; b[i][j]--;
        }
    }
    constexpr int width = 3;
    memcpy(t, b, sizeof(t)); mbs(t, width); fc();
    memcpy(s, t, sizeof(s)); msr(s, width); find();
    sort(num + 1, num + 1 + cnt);
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; ++i) { cout << num[i] << ' '; }
    cout << '\n';
    return 0;
}