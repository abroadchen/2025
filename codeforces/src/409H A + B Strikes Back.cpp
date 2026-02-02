//
// Created by Psy.C on 2026/2/2.
//

#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 5000
#define inf 0x7fffffff
using namespace std;

struct node { int nxt, to, dist; } e[N];

int cnt = 0, head[N];
void add(const ll from, const ll to, const ll dist) {
    e[++cnt].nxt = head[from]; e[cnt].to = static_cast<int>(to);
    e[cnt].dist = static_cast<int>(dist);
    head[from] = cnt;
}

ll n, s;
int dist[N];
bool vis[N];
queue<ll> q;
void spfa() {
    for (ll i = 1; i <= n; ++i) {
        dist[i] = inf;
        vis[i] = false;
    }
    q.push(s); dist[s] = 0; vis[s] = true;
    while (!q.empty()) {
        const ll j = q.front(); q.pop(); vis[j] = false;
        for (ll i = head[j]; i; i = e[i].nxt) {
            if (const ll w = e[i].to; dist[w] > dist[j] + e[i].dist) {
                dist[w] = dist[j] + e[i].dist;
                if (vis[w] == false) {
                    vis[w] = true;
                    q.push(w);
                }
            }
        }
    }
}

ll m;
int main() {
    fast;
    n = 3; m = 2; s = 1;
    for (ll i = 1, a; i <= m; ++i) {
        cin >> a;
        add(i, i + 1, a);
    }
    spfa();
    cout << dist[3];
    return 0;
}