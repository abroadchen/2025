//
// Created by Psy.C on 2025/9/15.
//

#include <ios>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N=224;

int head[N], ne, maxdis, maxv;

struct Edge {
    int from, to, next, w;
    bool tag;
} edges[N << 1];

void add(int u, int v, int w) {
    edges[ne] = { u, v, head[u], w, true };
    head[u] = ne++;
}

void dfs(int u, int f, int d2s) {
    if (maxdis < d2s) {
        maxdis = d2s;
        maxv = u;
    }
    for (int e = head[u]; e != -1; e = edges[e].next) {
        int v = edges[e].to, w = edges[e].w;
        if (!edges[e].tag) continue;
        if (v == f) continue;
        dfs(v, u, d2s + w);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int ans = 0, n; cin >> n;

    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; ++i) {
        int u, v, w = 1; cin >> u >> v;
        add(u, v, w), add(v, u, w);
    }

    for (int i = 0; i < ne; i += 2) {
        edges[i].tag = edges[i ^ 1].tag = 0;
        int u = edges[i].from, v = edges[i].to;
        dfs(u, -1, 0);
        maxdis = 0;
        dfs(maxv, -1, 0);

        int mul1 = maxdis; maxv = maxdis = 0;
        dfs(v, - 1, 0);
        maxdis = 0;
        dfs(maxv, -1, 0);

        int mul2 = maxdis; maxv = maxdis = 0;
        ans = max(ans, mul1 * mul2);
        edges[i].tag = edges[i ^ 1].tag = 1;
    }

    cout << ans << endl;

    return 0;
}