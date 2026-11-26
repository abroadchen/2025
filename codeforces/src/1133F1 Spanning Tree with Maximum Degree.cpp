//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
cnt: 已选边数, mx: 最大度
生成树总共需 n-1 条边。前面已把最大度点 ans 的 mx 条邻边全部输出并合并（见下面 main），所以这里只需再补 (n-1) - mx = n-mx-1 条。
按边序尝试，若 find(u) != find(v)（不构成环）则合并并输出这条边。
cnt == n-mx-1 时结束
初始化并查集，读边并建无向邻接表。
遍历找度数最大的顶点 ans（度 = v[i].size()），mx 记其度数
把最大度点 ans 的所有邻边先作为树边输出，并把 ans 与邻居合并（同一连通分量，fa[find(neighbor)] = ans，相当于以 ans 为根）。
再用 kruskal() 补足其余边，直到凑够 n-1 条
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 2e5+5;
struct node { int u, v; } s[N];//存边

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int m, n, cnt, mx;
void kruskal() {
    rep(i,m) {
        if (cnt == n-mx-1) break;
        int x = s[i].u, y = s[i].v; x = find(x); y = find(y);
        if (x != y) {
            cnt++; fa[x] = y;
            cout << s[i].u << ' ' << s[i].v << '\n';
        }
    }
}

vector<int> v[N];//邻接表
int ans;//最大度顶点(根)
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) fa[i] = i;
    rep(i,m) {
        cin >> s [i].u >> s [i].v;
        v[s[i].u].push_back(s[i].v); v[s[i].v].push_back(s[i].u);
    }
    rep(i,n) if (v[i].size() > mx) { mx = v[i].size(); ans = i; }
    for (int i = 0; i < v[ans].size(); i++) {
        fa[find(v[ans][i])] = ans;//把 ans 的邻居并入以 ans 为代表
        cout << ans << ' ' << v[ans][i] << '\n';//输出最大度点的所有邻边
    }
    kruskal();
    return 0;
}