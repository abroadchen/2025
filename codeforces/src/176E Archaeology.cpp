//
// Created by Psy.C on 2025/11/29.
//
/*
*n: 节点数
cnt: DFS序计数器
vis[N]: 节点的DFS访问顺序
fv[N]: DFS序到节点的映射
to[N][30]: 倍增表，用于LCA计算 to[x][i]: 节点x的2^i级祖先（倍增表）
m: 操作数
a[N]: 邻接表，存储树的边
len[N]: 边的权重
st[N]: 节点到根的距离
ans: 当前答案
s: 存储活跃节点的DFS序的集合
 *
*使用倍增法计算两个节点的最近公共祖先：
确保u的DFS序不大于v
通过倍增表向上跳跃，使v尽可能接近u的深度
返回v的父节点即为LCA
 *
*插入节点x到活跃集合：
找到集合中DFS序大于vis[x]的第一个元素ta
找到集合中最大的元素tb
如果ta不存在，则指向第一个元素
计算相邻节点a和b
更新答案：移除原来a-b的距离，添加a-x和b-x的距离
将vis[x]插入集合
 *
*从活跃集合中删除节点x：
找到等于vis[x]的元素ta
找到集合中最大的元素tb
计算相邻节点a和b
更新答案：添加原来a-b的距离，移除a-x和b-x的距离
从集合中删除vis[x]
 */
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
using namespace std;

int n, cnt, vis[N], fv[N], to[N][30], m;
vector<int> a[N], len[N];
ll st[N], ans;
set<int> s;
set<int>::iterator ta, tb;


void dfs(const int x, const int fa, const int ln) {
    st[x] = st[fa] + ln;
    cnt += 1; vis[x] = cnt; fv[cnt] = x; to[x][0] = fa;
    for (int i = 1; i <= 20; ++i) to[x][i] = to[to[x][i-1]][i-1];
    const int l = static_cast<int>(a[x].size());
    for (int i = 0; i <= l - 1; ++i) if (a[x][i] != fa) {
        dfs(a[x][i], x, len[x][i]);
    }
}

int lca(int u, int v) {
    if (u == v) return u;
    if (vis[u] > vis[v]) swap(u, v);
    for (int i = 20; i >= 0; --i) if (vis[to[v][i]] > vis[u]) {
        v = to[v][i];
    }
    return to[v][0];
}

int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y, z; i <= n - 1; ++i) {
        cin >> x >> y >> z;
        a[x].push_back(y); len[x].push_back(z);
        a[y].push_back(x); len[y].push_back(z);
    }
    dfs(1, 0, 0);
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        char c; cin.get(c);
        while (c != '+' && c != '-' && c != '?') cin.get(c);
        if (c == '+') {
            int x; cin >> x;
            if (s.size() >= 1) {
                ta = s.upper_bound(vis[x]), tb = s.end();
                --tb;
                if (ta == s.end()) ta = s.begin();
                int a = fv[*ta], b;
                if (ta == s.begin()) b = fv[*tb];
                else {
                    --ta;
                    b = fv[*ta];
                    ++ta;
                }
                int t = lca(a, b);
                ans -= st[a] + st[b] - 2 * st[t];
                t = lca(a, x);
                ans += st[a] + st[x] - 2 * st[t];
                t = lca(b, x);
                ans += st[b] + st[x] - 2 * st[t];
            }
            s.insert(vis[x]);
        }
        if (c == '-') {
            int x; cin >> x;
            if (s.size() >= 2) {
                ta = s.lower_bound(vis[x]), tb = s.end();
                --tb;
                int a, b;
                if (ta == tb) a = fv[*s.begin()];
                else {
                    ++ta;
                    a = fv[*ta];
                    --ta;
                }
                if (ta == s.begin()) b = fv[*tb];
                else {
                    --ta;
                    b = fv[*ta];
                    ++ta;
                }
                int t = lca(a, b);
                ans += st[a] + st[b] - 2 * st[t];
                t = lca(a, x);
                ans -= st[a] + st[x] - 2 * st[t];
                t = lca(b, x);
                ans -= st[b] + st[x] - 2 * st[t];
            }
            s.erase(vis[x]);
        }
        if (c == '?') cout << ans / 2 << '\n';
    }
    return 0;
}