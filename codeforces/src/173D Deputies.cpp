//
// Created by Psy.C on 2025/11/29.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 2e6, M = 2e5, inf = 1073741819;
int n, m, k,
d[M], s[2];

int ss, du[M], tail[N], nxt[N], to[N];
void add(const int x, const int y) {
    du[x]++, du[y]++;
    ++ss, nxt[tail[x]] = ss, tail[x] = ss, to[ss] = y;
    ++ss, nxt[tail[y]] = ss, tail[y] = ss, to[ss] = x;
}

int st[M], u[2][M];
void bfs(const int s1) {
    int r, ne, na; int h = r = 0;
    st[(r = 1)] = s1, d[s1] = 0;
    while (h < r) {
        ne = st[++h];
        for (int i = ne; nxt[i];) {
            i = nxt[i], na = to[i];
            if (d[na] > inf) {
                d[na] = d[ne] ^ 1;
                st[++r] = na;
            }
        }
    }
    rep(i,r) {
        ne = st[i];
        const int e = d[ne] & 1;
        u[e][++s[e]] = ne;
    }
}

int ans[M];
void out() {
    cout << "YES\n";
    for (int i = 1; i <= s[0]; i += 3, --k)
        for (int j = i; j <= i + 2; ++j) ans[u[0][j]] = k;
    for (int i = 1; i <= s[1]; i += 3, --k)
        for (int j = i; j <= i + 2; ++j) ans[u[1][j]] = k;
    cout << ans[1];
    for (int i = 2; i <= n; ++i) cout << ' ' << ans[i];
    cout << '\n';
}

int v[M];
void out(const int e, const int x) {
    cout << "YES\n";
    for (auto& i : v) i = 0;
    for (int i = x, ne; nxt[i];) { i = nxt[i], ne = to[i]; v[ne] = 1; }
    ans[x] = k;
    for (int i = 1, cnt = 1; i <= s[e^1] && cnt <= 2; ++i) {
        const int ne = u[e^1][i];
        if (!v[ne]) ans[ne] = k, cnt++;
    }
    k--;
    for (int i = 1, cnt = 1; i <= s[0]; ++i) {
        const int ne = u[0][i];
        if (ans[ne]) continue;
        ans[ne] = k;
        cnt++;
        if (cnt > 3) k--, cnt = 1;
    }
    for (int i = 1, cnt = 1; i <= s[1]; ++i) {
        const int ne = u[1][i];
        if (ans[ne]) continue;
        ans[ne] = k;
        cnt++;
        if (cnt > 3) k--, cnt = 1;
    }
    cout << ans[1];
    for (int i = 2; i <= n; ++i) cout << ' ' << ans[i];
    cout << '\n';
}

void out(const int e, int x, const int y) {
    cout << "YES\n";
    for (auto& i : v) i = 0;
    for (int i = x, ne; nxt[i];) { i = nxt[i], ne = to[i]; v[ne] = 1; }
    ans[x] = k;
    for (int i = 1, cnt = 1; i <= s[e^1] && cnt <= 2; ++i) {
        const int ne = u[e^1][i];
        if (!v[ne]) ans[ne] = k, cnt++;
    }
    k--;
    for (auto& i : v) i = 0;
    x = y;
    for (int i = x, ne; nxt[i];) { i = nxt[i], ne = to[i]; v[ne] = 1; }
    ans[x] = k;
    for (int i = 1, cnt = 1; i <= s[e^1] && cnt <= 2; ++i) {
        const int ne = u[e^1][i];
        if (!v[ne] && !ans[ne]) ans[ne] = k, cnt++;
    }
    k--;
    for (int i = 1, cnt = 1; i <= s[0]; ++i) {
        const int ne = u[0][i];
        if (ans[ne]) continue;
        ans[ne] = k;
        cnt++;
        if (cnt > 3) k--, cnt = 1;
    }
    for (int i = 1, cnt = 1; i <= s[1]; ++i) {
        const int ne = u[1][i];
        if (ans[ne]) continue;
        ans[ne] = k;
        cnt++;
        if (cnt > 3) k--, cnt = 1;
    }
    cout << ans[1];
    for (int i = 2; i <= n; ++i) cout << ' ' << ans[i];
    cout << '\n';
}

int main() {
    fast;
    cin >> n >> m; ss = n;
    rep(i,n) tail[i] = i;
    rep(i,m) {
        int x, y; cin >> x >> y;
        add(x, y);
    }
    for (auto& x : d) x = 127;
    s[0] = s[1] = 0;
    rep(i,n) if (d[i] > inf) bfs(i);
    k = n / 3;
    if ((s[0] % 3 == 0) && (s[1] % 3 == 0)) { out(); return 0; }
    int e;
    if (s[0] % 3 == 1) e = 0; else e = 1;
    int t = 0;
    rep(i,s[e]) {
        const int ne = u[e][i];
        if (s[e^1] - du[ne] >= 2) { t = ne; break; }
    }
    if (t) { out(e, t); return 0; }
    int p = 0; e ^= 1;
    rep(i,s[e]) {
        const int ne = u[e][i];
        if (s[e^1] - du[ne] >= 2) {
            if (!t) t = ne;
            else p = ne;
        }
    }
    if (t && p) { out(e, t, p); return 0; }
    cout << "NO\n";
    return 0;
}