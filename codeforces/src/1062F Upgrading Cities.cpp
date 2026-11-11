//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
建图：读入边 u→v，统计入度 in[]
初始化：所有入度 0 的点入队，tot 表示"不在队列里的剩余点数"（初始为 n，入队一个减一）
统计 d[x] —— 每个节点 x 在"删掉某个点后图几乎有序/可达"中的贡献。

d[x] += tot 当 x 是当前队列唯一/最后一个点：表示拓扑过程中 x "独当最后"时的贡献。
q.size()==1 时，检查队首 y 的所有出边终点入度是否都 >1，若是则 d[x] += tot。
tot 在队列非空时表示"已经因为需要删点才提前入队的点数"——这是允许删 1 个点的容错机
统计满足 d[i] >= n-2 的节点个数。
n-2 表示"全图几乎可达"的阈值（n 个点中最多允许 2 个不可达）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 3e5+10;

int in[N], n, m, d[N];
vector<int> e[N];
void get(int *u, int *v) {
    memset(in, 0, sizeof(in));
    rep(i,n) e[i].clear();
    rep(i,m) {
        e[u[i]].push_back(v[i]);
        in[v[i]]++;
    }
    int tot = n;
    queue<int> q;
    rep(i,n) if (in[i] == 0) q.push(i), tot--;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        if (q.empty()) d[x] += tot;//队列空：x是最后一个，累加 tot
        if (q.size() == 1) {//队列只剩1个点 y
            int c = 1;
            for (int i = 0, y = q.front(); i < e[y].size(); i++)
                c &= in[e[y][i]] > 1;
            d[x] += c*tot;//若y所有出边终点入度>1，累加 c*tot
        }
        for (int i : e[x]) if (!--in[i]) q.push(i), tot--;
    }
}

int u[N], v[N], ans;
int main() {
    fast;
    cin >> n >> m;
    rep(i,m) cin >> u[i] >> v[i];
    get(u, v); get(v, u);
    rep(i,n) ans += d[i] >= n-2;
    cout << ans << '\n';
    return 0;
}