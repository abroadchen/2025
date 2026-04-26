//
// Created by Psy.C on 2026/4/25.
//
/**
c：位置/节点编号
k：数量
p：价格
重载小于运算符，按价格p升序排列
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e3+7;

struct node {
    int c; ll k, p;
    bool operator<(const node &o) const {
        return p < o.p;
    }
} s[N];

int v[N];///访问标记数组，用于BFS
vector<int> h[N];///邻接表，存储图的边关系
void bfs(int x, int u) {//x为最大距离限制，u为起始节点
    queue<int> q; q.push(u); v[u] = 0;
    while (!q.empty()) {
        int cur = q.front(); q.pop();//取出队列前端元素
        if (v[cur] == x) continue;//当前距离已达最大限制
        for (auto &it : h[cur]) {
            if (v[it] != -1) continue;//邻居已被访问过
            q.push(it);
            v[it] = v[cur] + 1;//更新其距离为当前节点距离+1
        }
    }
}

int n, w;
bool f(int x, int g, ll c, ll a) {//在距离x内，从节点g出发，是否能用预算a购买至少c单位物品
    fill_n(v + 1, n, -1);//初始化为-1（未访问）
    bfs(x, g);
    for (int i = 1; i <= w; ++i) {
        if (v[s[i].c] != -1) {//当前位置在可达范围内（距离不是-1），则尝试购买
            a -= min(c, s[i].k) * s[i].p;//花费金额减少
            c -= min(c, s[i].k);//需求数量减少
        }
        if (a < 0) break;//预算不足
    }
    if (c) return false;//仍有需求未能满足
    return a >= 0;
}
int F(int g, ll c, ll a) {//找到最小的距离，使得在给定条件下可以满足需求
    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        f(mid, g, c, a) ? r = mid : l = mid + 1;
    }
    return !f(l, g, c, a) ? -1 : l;//最短距离无法满足条件，返回-1；否则返回最短距离
}

int g, r, a;
void out() {
    cin >> g >> r >> a;//读取起始点、需求数量和预算，输出最短距离
    cout << F(g, r, a) << '\n';
}

int m, q;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        h[x].push_back(y); h[y].push_back(x);
    }
    cin >> w;//商品数量
    for (int i = 1; i <= w; ++i)
        cin >> s[i].c >> s[i].k >> s[i].p;//位置、数量、价格
    sort(s + 1, s + 1 + w);
    cin >> q;
    while (q--) out();
    return 0;
}