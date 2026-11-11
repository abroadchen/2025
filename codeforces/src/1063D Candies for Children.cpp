//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
第一块 { }，基准是 (k-L)
枚举 m（0..N）
这里把 k-L 写成 C*(n+m) + t，要求：

C >= 0；
余数 t 满足 0<=t<=L 且 t<=m；
n-L >= m-t（剩余约束）。
枚举 C（1..N）
把 k-L = C*n + m*C + t（对 C 取模），再解出 m、t，并做一次"调整"（若 n-L < m-t，则平移减少 m、增大 t 使满足约束）。同样检查可行性，取最大 m。
特判
第二块 { }，基准是 (k+1-L)

与第一块完全相同，只是把 k-L 换成 k+1-L，约束里 0<=t<=L 换成 1<=t<=L
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define ll long long
using namespace std;

constexpr int N = 1e6;

ll n, l, r, k, L, ans = -1;
int main() {
    fast;
    cin >> n >> l >> r >> k;
    L = r >= l ? r-l+1 : n-l+1+r;
    {
        rep(m,0,N) {
            if (n+m > N) break;
            ll C = (k-L)/(n+m), t = (k-L)%(n+m);
            if (C >= 0 && 0 <= t && t <= L && t <= m && n-L >= m-t)
                ans = max(ans, (ll)m);
        }
        rep(C,1,N) {
            ll m = (k-L-1ll*C*n)/C, t = (k-L-1ll*C*n)%C;
            if (n-L < m-t) {
                ll x = (m-(n-L)-t+C)/(C+1); m -= x;
                t += 1ll*x*C;
            }
            if (C >= 0 && 0 <= t && t <= L && t <= m && n-L >= m-t)
                ans = max(ans, (ll)m);
        }
        if (0 <= k-L && k-L <= L) ans = max(ans, k-L+n-L);
    }
    {
        rep(m,1,N) {
            if (n+m > N) break;
            ll C = (k+1-L)/(n+m), t = (k+1-L)%(n+m);
            if (C >= 0 && 1 <= t && t <= L && t <= m && n-L >= m-t)
                ans = max(ans, (ll)m);
        }
        rep(C,1,N) {
            ll m = (k+1-L-1ll*C*n)/C, t = (k+1-L-1ll*C*n)%C;
            if (n-L < m-t) {
                ll x = (m-(n-L)-t+C)/(C+1); m -= x;
                t += 1ll*x*C;
            }
            if (C >= 0 && 1 <= t && t <= L && t <= m && n-L >= m-t)
                ans = max(ans, (ll)m);
        }
        if (1 <= k+1-L && k+1-L <= L) ans = max(ans, k+1-L+n-L);
    }
    cout << ans << '\n';
    return 0;
}