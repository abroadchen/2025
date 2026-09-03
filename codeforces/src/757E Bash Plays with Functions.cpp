//
// Created by Psy.C on 2026/9/3.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+7, M = 21, mod = 1e9+7;

int mp[N], p[N], cp;
inline void sieve() {
    for (int i = 2; i < N; ++i) {
        !mp[i] && (p[++cp] = mp[i] = i);
        for (int j = 1; i*p[j] < N; ++j) {
            mp[i*p[j]] = p[j];
            if (mp[i] == p[j]) break;
        }
    }
}

inline int add(const int& x) {
    return x >= mod ? x - mod : x;
}

int pf[M], f[N][M];
inline void prework() {
    sieve(), pf[0] = 1;
    for (int i = 1; i < N; ++i) f[i][0] = 1;
    for (int i = 1; i < M; ++i)
        f[0][i] = 2, pf[i] = pf[i-1] + 2;
    for (int i = 1; i < N; ++i)
        for (int j = 1; j < M; ++j)
            f[i][j] = pf[j], pf[j] = add(pf[j-1] + f[i][j]);
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int m, n, ans;
inline void solve() {
    rd(m), rd(n), ans = 1;
    for (int c = 0, pr; n != 1; ans = 1ll*ans*f[m][c]%mod, c = 0)
        for (pr = mp[n]; n % pr == 0; n /= pr)
            ++c;
    cout << ans << '\n';
}

int T;
int main() {
    fast;
    for (prework(), rd(T); T; --T) solve();
    return 0;
}