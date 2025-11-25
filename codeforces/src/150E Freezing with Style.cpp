//
// Created by Psy.C on 2025/11/23.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

constexpr int N = 2e5+5, inf = 0x3f3f3f3f;
int n, L, R, val[N],
siz[N], mx[N], mxdep[N], dep1[N], vis[N], all, Mx, Rt, M;
struct edge { int v, w; };
vector<edge> vc[N];

void getrt(const int p, const int pre) {
    siz[p] = 1, mx[p] = 0, mxdep[p] = dep1[p];
    for (const auto v : vc[p]) {
        if (v.v == pre || vis[v.v]) continue;
        dep1[v.v] = dep1[p] + 1;
        getrt(v.v, p);
        siz[p] += siz[v.v];
        mx[p] = max(mx[p], siz[v.v]);
        mxdep[p] = max(mxdep[p], mxdep[v.v]);
    }
    mx[p] = max(mx[p], all - siz[p]);
    if (mx[p] < Mx) Rt = p, Mx = mx[p];
}



int buc[N], fa[N], Dep[N], dis[N];
int bfs(const int st) {
    int tot(0); buc[++tot] = st;
    queue<int> q;
    while (!q.empty()) q.pop(); q.push(st);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : vc[u]) if (v.v != fa[u] && !vis[v.v]) {
            fa[v.v] = u, Dep[v.v] = Dep[u] + 1;
            dis[v.v] = dis[u] + (v.w >= M ? 1 : -1);
            buc[++tot] = v.v;
            q.push(v.v);
        }
    }
    return tot;
}

int dmx[N], dp[N], Mdep, Dmx[N], q[N], Ansu, Ansv, Dp[N];
int calc(int p) {
    int Len = bfs(p);
    for (int i = 1; i <= Len; ++i) if (dmx[Dep[buc[i]]] < dis[buc[i]]) {
        dmx[Dep[buc[i]]] = dis[buc[i]];
        dp[Dep[buc[i]]] = buc[i];
    }
    int hd(1), tl(0), flag(0);
    for (int i = mxdep[p], j = 0; i; --i) {
        int ll = L - i, rr = R - i;
        if (ll > Mdep) break; j = max(j, ll);
        for (; j <= rr && j <= Mdep; ++j) {
            for (; hd <= tl && Dmx[q[tl]] <= Dmx[j]; --tl);
            q[++tl] = j;
        }
        for (; hd <= tl && q[hd] < ll; ++hd);
        if (hd <= tl && Dmx[q[hd]] + dmx[i] >= 0) {
            Ansu = dp[i], Ansv = Dp[q[hd]];
            flag = 1;
            break;
        }
    }
    Mdep = max(Mdep, mxdep[p]);
    for (int i = 1; i <= mxdep[p]; ++i) if (Dmx[i] < dmx[i]) {
        Dmx[i] = dmx[i]; Dp[i] = dp[i];
        dp[i] = 0, dmx[i] = -inf;
    }
    return flag;
}

int dfs(int p) {
    vis[p] = 1;
    sort(vc[p].begin(), vc[p].end(), [&](const edge& a, const edge& b) {
        return mxdep[a.v] < mxdep[b.v];
    });
    Dp[0] = p, Dmx[0] = 0;
    for (int i = 1; i <= mxdep[p]; ++i) Dmx[i] = dmx[i] = -inf, Dp[i] = dp[i] = 0;
    Mdep = 0;
    for (auto v : vc[p]) if (!vis[v.v]) {
        fa[v.v] = p;
        dis[v.v] = v.w >= M ? 1 : -1;
        Dep[v.v] = 1;
        if (calc(v.v)) return 1;
    }
    for (auto v : vc[p]) if (!vis[v.v]) {
        all = siz[v.v];
        Mx = 2e9, getrt(v.v, p);
        dep1[Rt] = 0;
        getrt(Rt, 0);
        if (dfs(Rt)) return 1;
    }
    return 0;
}

int main() {
    ostream::sync_with_stdio(false);
    cin >> n >> L >> R;
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        auto add = [&](int u, int v, int w) {
            vc[u].push_back({v, w});
        };
        add(u, v, w), add(v, u, w);
        val[i] = w;
    }
    sort(val + 1, val+n);
    int mid, l(1), r(n-1), ansu = 0, ansv = 0, ansmid;
    while (l <= r) {
        mid = (l + r) >> 1;
        memset(vis, 0, sizeof(vis));
        M = val[mid]; Mx = 2e9, all = n;
        getrt(1, 0); dep1[Rt] = 0;
        getrt(Rt, 0);
        if (dfs(Rt)) l = mid + 1, ansu = Ansu, ansv = Ansv, ansmid = mid;
        else r = mid - 1;
    }
    cout << ansu << ' ' << ansv << '\n';
    return 0;
}