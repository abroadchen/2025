//
// Created by Psy.C on 2026/1/12.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10005
#define mod 1000000007
#define rep(i,n) for (int i=0; i<=(n); ++i)
using namespace std;

int f[N][10], m, n = 3;
char mp[10][N];
int dp() {
    memset(f, 0, sizeof(f)); f[0][7] = 1;
    for (int i = 1; i <= m; ++i) {
        int s = 0;
        for (int j = 1; j <= n; ++j) if (mp[j][i] == 'X') s ^= 1<<(j-1);
        rep(j,7) {
            if (s&j) continue;
            const int x = j^s;
            f[i][x] = (f[i][x] + f[i-1][7-j]) % mod;
            if (j == 3 || j == 6) f[i][x] = (f[i][x] + f[i-1][7]) % mod;
            if (j == 7) f[i][x] = (f[i][x] + f[i-1][3] + f[i-1][6]) % mod;
        }
    }
    return f[m][7];
}


int main() {
    fast;
    cin >> m;
    int x = 0, y = 0, ans = 0;
    for (int i = 1; i <= n; ++i) scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) if (mp[i][j] == 'O') {
        x = i, y = j;
    }
    mp[x][y] = 'X';
    rep(l,1) {
        if (l && (y<3||mp[x][y-1]=='X'||mp[x][y-2]=='X')) continue;
        rep(r,1) {
            if (r && (y>m-2||mp[x][y+1]=='X'||mp[x][y+2]=='X')) continue;
            rep(u,1) {
                if (u && (x<3||mp[x-1][y]=='X'||mp[x-2][y]=='X')) continue;
                rep(d,1) {
                    if (d &&(x>1||mp[x][y+1]=='X'||mp[x][y+2]=='X')) continue;
                    if (!l && !r && !u && !d) continue;
                    if (l) mp[x][y-1]='X', mp[x][y-2]='X';
                    if (r) mp[x][y+1]='X', mp[x][y+2]='X';
                    if (u) mp[x-1][y]='X', mp[x-2][y]='X';
                    if (d) mp[x+1][y]='X', mp[x+2][y]='X';
                    const int res = dp();
                    if ((l+r+u+d)&1) ans = (ans + res) % mod; else ans = (ans - res + mod) % mod;
                    if (l) mp[x][y-1]='.', mp[x][y-2]='.';
                    if (r) mp[x][y+1]='.', mp[x][y+2]='.';
                    if (u) mp[x-1][y]='.', mp[x-2][y]='.';
                    if (d) mp[x+1][y]='.', mp[x+2][y]='.';
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}