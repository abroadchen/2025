//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 15e4+5, M = 26;

int n, q1[N], q2[N], p1[M+1][N], p2[M+1][N], ans, r1, r2, c1, c2;
int main() {
    fast;
    cin >> n;
    rep(i,n) {
        char c; cin >> c;
        if (c == '?') q1[++q1[0]] = i;
        else p1[c-'a'+1][++p1[c-'a'+1][0]] = i;
    }
    rep(i,n) {
        char c; cin >> c;
        if (c == '?') q2[++q2[0]] = i;
        else p2[c-'a'+1][++p2[c-'a'+1][0]] = i;
    }
    rep(i,M) {
        ans += min(p1[i][0],p2[i][0]);
        p1[i][0] > p2[i][0] ? r1 += p1[i][0]-p2[i][0] : r2 += p2[i][0]-p1[i][0];
    }
    ans += min(q1[0],r2) + min(q2[0],r1);
    int qa = max(q1[0]-r2,0), qb = max(q2[0]-r1,0);
    ans += min(qa,qb);
    cout << ans << '\n';
    rep(i,M) rep(j,min(p1[i][0],p2[i][0]))
        cout << p1[i][j] << ' ' << p2[i][j] << '\n';
    rep(i,M) {
        if (p1[i][0] == p2[i][0]) continue;
        if (p1[i][0] > p2[i][0]) {
            rep(j,p1[i][0]-p2[i][0]) {
                if (++c2 > q2[0]) break;
                cout << p1[i][p2[i][0] + j] << ' ' << q2[c2] << '\n';
            }
        } else {
            rep(j,p2[i][0]-p1[i][0]) {
                if (++c1 > q1[0]) break;
                cout << q1[c1] << ' ' << p2[i][p1[i][0]+j] << '\n';
            }
        }
    }
    while (++c2 <= q2[0] && ++c1 <= q1[0])
        cout << q1[c1] << ' ' << q2[c2] << '\n';
    return 0;
}