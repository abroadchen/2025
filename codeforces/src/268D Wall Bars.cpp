//
// Created by Psy.C on 2025/12/21.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define rep(i,n) for(int i=0; i<=n; ++i)
#define mod 1000000009
using namespace std;


signed main() {
    fast;
    int n, h; cin >> n >> h;
    int pre[2][31][31][31], cur[2][31][31][31];
    if (h == 1) { cout << 4 << '\n'; return 0; }
    pre[1][2][2][2] = 4;
    for (int t = 2; t <= n; ++t) {
        memset(cur, 0, sizeof(cur));
        rep(i,1) {
            int ni = i + 1;//计算下一个状态
            if (ni == 1 || ni == h + 1) ni = 0;//如果 ni 是边界值，则设为 0（表示无效状态）
            rep(j,h) {
                int nj = j + 1;
                if (nj == 1 || nj == h + 1) nj = 0;
                rep(k,h) {
                    int nk = k + 1;
                    if (nk == 1 || nk == h + 1) nk = 0;
                    rep(l,h) {
                        const int x = pre[i][j][k][l];//获取当前状态值
                        if (x == 0) continue;
                        int nl = l + 1;
                        if (nl == 1 || nl == h + 1) nl = 0;
                        if (i) cur[1][nj][nk][nl]=(cur[1][nj][nk][nl]+x)%mod;
                        else cur[0][nj][nk][nl]=(cur[0][nj][nk][nl]+x)%mod;
                        if (j) cur[1][ni][nk][nl]=(cur[1][ni][nk][nl]+x)%mod;
                        else cur[0][ni][nk][nl]=(cur[0][ni][nk][nl]+x)%mod;
                        if (k) cur[1][ni][nj][nl]=(cur[1][ni][nj][nl]+x)%mod;
                        else cur[0][ni][nj][nl]=(cur[0][ni][nj][nl]+x)%mod;
                        if (l) cur[1][ni][nj][nk]=(cur[1][ni][nj][nk]+x)%mod;
                        else cur[0][ni][nj][nk]=(cur[0][ni][nj][nk]+x)%mod;
                    }
                }
            }
        }
        memcpy(pre, cur, sizeof(cur));//将当前状态复制到前一个状态数组中
    }
    int ans = 0;
    rep(i,1) rep(j,h) rep(k,h) rep(l,h) if (i||j||k||l) {
        ans = (ans + cur[i][j][k][l]) % mod;//累加有效状态值
    }
    cout << ans << '\n';
    return 0;
}