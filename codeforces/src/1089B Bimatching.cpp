//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
res[x]：存储匹配关系。
对每个未匹配的结点调用 get(st) 寻找增广路，若成功则匹配数 +1——这就是经典的最大匹配算法框架
c[x]：结点染色状态：0=偶（S 队）、1=奇（T 队）、-1=未访问。
pre[x]：记录增广路前驱。
vis + t：带时间戳的 LCA 判断 visited。
dsu：并查集，用于合并花（blossom）
两结点沿着匹配/前驱交替向上找，用时间戳标记，第一次重逢即是花上的 LCA（也就是花根）
将路径 x..z 上的点全部并入以 z 为根的并查集（收缩"花"），并调整前驱和染色，把花上奇点改为偶点重新入队扩展——这就是带花树处理奇环的标志动作
偶点 x 扩展相邻点 y。
y 未访问：标记为奇点，若 y 未匹配则执行增广翻转（标准增广路反转），返回 true；否则把 y 的匹配对象作为偶点入队。
y 为偶点且不在同一朵花：说明发现奇环 → 求 lca 并收缩花
图共 n*2 + m 个点：
每对 i,i+n 互相连边。
对每个 '1'：结点 i、i+n 都连向结点 j+2n。
在这样构造的图上跑一般图最大匹配，答案 最大匹配数 - n

!-x 等价于判断 x == -1
-lst 等价于 lst != -1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; ++i)
#define vi vector<int>
using namespace std;

struct DSU {
    vector<int> p; int n;
    DSU(int n) : n(n) {
        p.resize(n);
        rep(i,n) p[i] = i;
    }
    int find(int x) { while (x != p[x]) x = p[x] = p[p[x]]; return x; }
    bool uni(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return 0;
        p[x] = y;
        return 1;
    }
};

pair<int,vi> solve(int n, vector<vi> e) {
    vi res(n,-1);
    int ans = 0;
    auto get = [&](int st) {
        vi c(n,-1), pre(n,-1), vis(n);
        queue<int> q;
        int t = 0; DSU dsu(n); q.push(st); c[st] = 0;
        auto lca = [&](int x, int y) {
            ++t; x = dsu.find(x), y = dsu.find(y);
            while (1) {
                if (~x) {
                    if (vis[x] == t) return x;
                    vis[x] = t;
                    if (~res[x]) x = dsu.find(pre[res[x]]); else x = -1;
                }
                swap(x,y);
            }
        };
        auto bl = [&](int x, int y, int z) {
            while (dsu.find(x) != z) {
                pre[x] = y;
                if (c[res[x]] == 1) { q.push(res[x]); c[res[x]] = 0; }
                if (dsu.find(x) == x) dsu.uni(x, z);
                if (dsu.find(res[x]) == res[x]) dsu.uni(res[x], z);
                y = res[x]; x = pre[y];
            }
        };
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (auto y : e[x]) {
                if (!~c[y]) {
                    c[y] = 1; pre[y] = x;
                    if (!~res[y]) {
                        while (~x) {
                            int lst = res[x]; res[x] = y; res[y] = x;
                            if (~lst) { y = lst; x = pre[y]; } else break;
                        }
                        return true;
                    }
                    q.push(res[y]); c[res[y]] = 0;
                } else if (!c[y] && dsu.find(x) != dsu.find(y)) {
                    int z = lca(x, y); bl(x, y, z); bl(y, x, z);
                }
            }
        }
        return false;
    };
    rep(i,n) if (!~res[i] && get(i)) ++ans;
    return {ans, res};
}


int main() {
    fast;
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<vi> e(n*2+m);
        rep(i,n) {
            e[i].push_back(i+n); e[i+n].push_back(i);
            string s; cin >> s;
            rep(j,m) if (s[j] == '1') {
                e[i].push_back(j+n*2); e[j+n*2].push_back(i);
                e[i+n].push_back(j+n*2); e[j+n*2].push_back(i+n);
            }
        }
        cout << solve(n*2+m,e).first-n << '\n';
    }
    return 0;
}