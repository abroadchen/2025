//
// Created by Psy.C on 2025/11/29.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
#define N 2009
#define M 1002009
#define K 26
using namespace std;

int n, m;
int now[K], len[N], pos[N], last[M][K],
id[N], sum[N], L, go[N][K], dp[M][2], ans;
char a[M], s[N];

int main() {
    fast;
    cin >> n;
    rep(i,n) {
        for (auto& x : now) x = 0;
        scanf("%s", a + 1); len[i] = static_cast<int>(strlen(a + 1));
        pos[i + 1] = pos[i] + len[i] + 1;
        for (int j = len[i]; j >= 0; --j) {
            for (int k = 0; k < K; ++k) last[pos[i]+j][k] = now[k];
            if (j) now[a[j] - 'a'] = j;
        }
    }
    cin >> m;
    rep(i,m) { cin >> id[i]; sum[i] = sum[i-1] + len[id[i]]; }
    scanf("%s", s + 1); L = static_cast<int>(strlen(s + 1));
    for (auto& x : now) x = 0;
    for (int i = m; i; --i) {
        for (int k = 0; k < K; ++k) go[i][k] = now[k];
        for (int k = 0; k < K; ++k) if (last[pos[id[i]]][k]) now[k] = i;
    }
    dp[0][0] = 1, dp[0][1] = 0;
    rep(i,L) {
        for (int j = ans; j >= 0; --j) {
            int t = 0, p = 0;
            const int c = s[i] - 'a';
            if (last[pos[id[dp[j][0]]] + dp[j][1]][c]) {
                t = dp[j][0], p = last[pos[id[dp[j][0]]] + dp[j][1]][c];
            } else {
                t = go[dp[j][0]][c], p = last[pos[id[t]]][c];
            }
            if (t && (dp[j+1][0] == 0 ||
                sum[t-1] + p < sum[dp[j+1][0]-1] + dp[j+1][1])) {
                dp[j+1][0] = t, dp[j+1][1] = p;
            }
        }
        if (dp[ans + 1][0]) ans++;
    }
    cout << ans << '\n';
    return 0;
}